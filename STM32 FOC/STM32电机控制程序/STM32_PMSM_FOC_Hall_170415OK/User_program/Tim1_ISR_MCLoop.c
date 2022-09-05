
#include "Tim1_ISR_MCLoop.h"
#include "ADC_int.h"
#include "Tim1_PWM.h"
#include "GPIO_int.h"
#include "ThreeHall.h"
#include "Axis_transform.h"
#include "Svpwm_dq.h"
#include "Task_function.h"
#include "PI_Cale.h"
#include "Timer.h"
#include "Usart_RS232.h"
#include "Tim4_Encoder_PWMDAC.h"
 
extern  PI_Control   pi_spd ;
extern  PI_Control   pi_id  ;
extern  PI_Control   pi_iq  ;
extern   ADCSamp    ADCSampPare;
extern   uint16_t   PWM_DUTY[3] ;
extern   Hall       Hall_Three;
extern   logic      logicContr;
extern   TaskTime   TaskTimePare;  
extern   CLARKE     ClarkeI;
extern   PARK       ParkI;
extern   IPARK      IparkU;
extern   SVPWM      Svpwmdq;
extern   IQSin_Cos  AngleSin_Cos;
extern   Test       TestPare;
extern   IQAtan     IQAtan_Pare;
 
uint16_t  FilK1=328;
uint16_t  FilK2=696;

void TIM1_UP_IRQHandler(void)// ����ADC�жϲ����͵����·����
{
	//�˳�������ж�һֱִ��
	 TIM_ClearFlag(TIM1, TIM_FLAG_Update); // �����־λ
	 
   ThreeHallanglecale( );  //����״̬�ͼ���λ�ýǶ�
	 TaskTimePare.PWMZD_count++;
   
	 if(TaskTimePare.PWMZD_count==25 ) // 2ms���¼�����
	 {
	   TaskTimePare.PWMZD_count=0;
	   Hall_Three_Speedcale( );  //���ݻ����Ƕȼ����ٶ�
		                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
     knob_control( );   //ת�ѵ�λ�����ٵĿ���
 	
		 TestPare.id_test=  (pi_id.Fbk>>3 );   //ͨѶ���Բ������
	   TestPare.iq_test=  (pi_iq.Fbk>>3 );
	   TestPare.ud_test=  (IparkU.Ds>>3 );
	   TestPare.uq_test=  (IparkU.Qs>>3 );
     // ���Բ������	
     TestPare.fact_BUS_Voil= ADCSampPare.BUS_Voltage;
	   TestPare.fact_BUS_Curr= ADCSampPare.BUS_Curr;
	   TestPare.Speed_fact= ( pi_spd.Fbk>>3);
	   TestPare.Speed_target=( pi_spd.Ref>>3);	
 	 
	   pi_spd.Fbk = Hall_Three.Speed_RPM ;  //   0---4096RPM
	   PI_Controller((p_PI_Control)&pi_spd); // �ٶȻ�PI���� 
	   pi_spd.OutF= _IQ10mpy(FilK1,pi_spd.OutF)+_IQ10mpy(FilK2,pi_spd.Out); //һ�׵�ͨ�˲���	 
   }
	
	  ADC_Sample( );  // �����ĸ�ߵ�����ѹ�ɼ�
	 
  	ClarkeI.As=ADCSampPare.PhaseU_Curr;
	  ClarkeI.Bs=ADCSampPare.PhaseV_Curr;

	  CLARKE_Cale((p_CLARKE)&ClarkeI ); // CLARKE�任

	  ParkI.Alpha=ClarkeI.Alpha;
	  ParkI.Beta=ClarkeI.Beta;
 	  
	  AngleSin_Cos.IQAngle= Hall_Three.ele_angleIQ;
 
	  IQSin_Cos_Cale((p_IQSin_Cos)&AngleSin_Cos); //�ż�λ�ýǶȣ������Ҽ��㺯��

		ParkI.Sine =AngleSin_Cos.IQSin;  
	  ParkI.Cosine =AngleSin_Cos.IQCos;   

	  PARK_Cale((p_PARK)&ParkI);  // park�任
	
    pi_id.Ref = 0;
	  pi_iq.Ref= pi_spd.OutF;

	  pi_id.Fbk = ParkI.Ds;
	  PI_Controller((p_PI_Control)&pi_id);  // id�� PI����
	  pi_id.OutF= _IQ10mpy(FilK1,pi_id.OutF)+_IQ10mpy(FilK2,pi_id.Out);

	  pi_iq.Fbk = ParkI.Qs;
	  PI_Controller((p_PI_Control)&pi_iq);  // iq�� PI����
	  pi_iq.OutF= _IQ10mpy(FilK1,pi_iq.OutF)+_IQ10mpy(FilK2,pi_iq.Out);
 
	  if(logicContr.Run_mode==1)
	  {
	    IparkU.Ds=0;   // ���ÿ���
	    IparkU.Qs= 10*pi_spd.Ref;  //
	  }

	  if(logicContr.Run_mode==2)
	  {
	  	IparkU.Ds= pi_id.OutF;   // ����id�����ջ�
	  	IparkU.Qs= pi_spd.OutF;  // �����ٶȱջ�   
	  }
    if(logicContr.Run_mode==3)
	  {
       IparkU.Ds= -pi_id.OutF;   //��ת���� ��id�����ջ�
       IparkU.Qs= -pi_spd.OutF;  // �����ٶȱջ� 
    }
    if(logicContr.Run_mode==4)
    {
			 IparkU.Ds= pi_id.OutF;   // �����ٶȱջ�  id�����ջ�
			 IparkU.Qs= pi_iq.OutF;   // 1=2^15=32768 ���ֵ
    }
        
    IparkU.Sine=AngleSin_Cos.IQSin;
    IparkU.Cosine=AngleSin_Cos.IQCos;
	  IPARK_Cale((p_IPARK)&IparkU);      // ��park�任
 	
	  Svpwmdq.Ualpha =IparkU.Alpha;
	  Svpwmdq.Ubeta = IparkU.Beta;

    SVPWM_Cale((p_SVPWM)&Svpwmdq);    // SVPWM����ռ�ձ�
 
	  Svpwm_Outpwm( );  // PWM���  
		 
    TIM_SetCompare3(TIM4 , (Hall_Three.ele_angleIQ>>5));  //DACͨ��1    
	  TIM_SetCompare4(TIM4 , PWM_DUTY[0]);                  //DACͨ��2 
} 


//===========================================================================
// No more.
//===========================================================================
