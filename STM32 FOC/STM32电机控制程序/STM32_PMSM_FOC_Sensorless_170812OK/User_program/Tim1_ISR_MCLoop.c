//############################################################
// FILE: Tim1_ISR_MCLoop.c
// Created on: 2017��1��15��
// Author: XQ
// summary: Tim1_ISR_MCLoop
// ��ʱ��1������ƣ� �жϻ�·�ջ�����  
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//��Ȩ���У�����ؾ�
//DSP/STM32������ƿ�����
//˶������
//��ַ: https://shuolidianzi.taobao.com
//�޸�����:2017/1/24
//�汾��V17.3-1
//Author-QQ: 616264123
//�������QQȺ��314306105
//############################################################
#include "Tim1_ISR_MCLoop.h"
#include "ADC_int.h"
#include "Tim1_PWM.h"
#include "GPIO_int.h"
#include "Axis_transform.h"
#include "Svpwm_dq.h"
#include "Task_function.h"
#include "PI_Cale.h"
#include "Timer.h"
#include "Usart_RS232.h"
#include "Sensorless_SMO.h" 
#include "Tim4_Encoder_PWMDAC.h"
 
extern  PI_Control   pi_spd ;
extern  PI_Control   pi_id  ;
extern  PI_Control   pi_iq  ;
extern   ADCSamp    ADCSampPare;
extern   uint16_t   PWM_DUTY[3] ;
extern   logic      logicContr;
extern   TaskTime   TaskTimePare;  
extern   CLARKE     ClarkeI;
extern   PARK       ParkI;
extern   IPARK      IparkU;
extern   SVPWM      Svpwmdq;
extern   IQSin_Cos  AngleSin_Cos;
extern   Test       TestPare;
extern   IQAtan     IQAtan_Pare;
extern   Angle_SMO   Angle_SMOPare ;
extern   Speed_est   Speed_estPare ;
extern   SMO_Motor   SMO_MotorPare ;

uint16_t   detha1=0,detha2=0 ;
uint16_t   FilK1=328;  
uint16_t   FilK2=696;

void TIM1_UP_IRQHandler(void)// ����ADC�жϲ����͵����·����
{
	//�˳�������ж�һֱִ��
	 TIM_ClearFlag(TIM1, TIM_FLAG_Update); //�����־λ
   
   
	 TaskTimePare.PWMZD_count++;
	
   if(TaskTimePare.PWMZD_count==25 ) // 2ms���¼�����
	 {
	   TaskTimePare.PWMZD_count=0;
	   
		 SMO_Speedcale();	  // �����޸нǶȼ����ٶ�  
     knob_control();    //ת�ѵ�λ�����ٵĿ���
 	
		 TestPare.id_test=  (pi_id.Fbk>>3 ); //ͨѶ���Բ������
	   TestPare.iq_test=  (pi_iq.Fbk>>3 );
	   TestPare.ud_test=  (IparkU.Ds>>3 );
	   TestPare.uq_test=  (IparkU.Qs>>3 );
// ���Բ������  
     TestPare.fact_BUS_Voil= ADCSampPare.BUS_Voltage;
	   TestPare.fact_BUS_Curr= ADCSampPare.BUS_Curr;
	   TestPare.Speed_fact= ( pi_spd.Fbk>>3);
	   TestPare.Speed_target=( pi_spd.Ref>>3);	
  
	   if(( logicContr.Start_order==1)||( logicContr.Start_order==2))
	   {  
		    pi_spd.Fbk = Speed_estPare.Speed_RPM ;  //   0---4096RPM
	      PI_Controller((p_PI_Control)&pi_spd);   // �ٶȻ�PI���� 
	      pi_spd.OutF= _IQ10mpy(FilK1,pi_spd.OutF)+_IQ10mpy(FilK2,pi_spd.Out);			
     } 
   }
	
	  ADC_Sample( );  //�����ĸ�ߵ�����ѹ�ɼ�
 
  	ClarkeI.As=ADCSampPare.PhaseU_Curr;
	  ClarkeI.Bs=ADCSampPare.PhaseV_Curr;

	  CLARKE_Cale((p_CLARKE)&ClarkeI ); // CLARKE�任

	  ParkI.Alpha=ClarkeI.Alpha;
	  ParkI.Beta=ClarkeI.Beta;
 
	  if(logicContr.Start_order)  // �����޸нǶȿ��Ƶ��ٶ����ǶȲ���
	  {
			 detha2= 15* pi_spd.Ref;		 
			 if(detha1>= detha2)
			 detha1-=12; 
			 if(detha1<= detha2)
			 detha1+=12; 
			 if( Abs( detha1-detha2 )<=8 )
			 detha1= detha2; 
    	IQAtan_Pare.JZIQAngle= IQAtan_Pare.IQAngle + detha1; //�����޸нǶ���λƫ��
			if( IQAtan_Pare.JZIQAngle >=65536)
		  IQAtan_Pare.JZIQAngle-=65536;
		  AngleSin_Cos.IQAngle = IQAtan_Pare.JZIQAngle;
	  }
 
	  IQSin_Cos_Cale((p_IQSin_Cos)&AngleSin_Cos);  //�ż�λ�ýǶȣ������Ҽ��㺯��

		ParkI.Sine = AngleSin_Cos.IQSin;  
	  ParkI.Cosine =AngleSin_Cos.IQCos;   

	  PARK_Cale((p_PARK)&ParkI);   // PARK�任
	
    pi_id.Ref = 0;
	  pi_iq.Ref= pi_spd.OutF;

	  pi_id.Fbk = ParkI.Ds;
	  PI_Controller((p_PI_Control)&pi_id); // id�� PI����
	  pi_id.OutF= _IQ10mpy(FilK1,pi_id.OutF)+_IQ10mpy(FilK2,pi_id.Out);

	  pi_iq.Fbk = ParkI.Qs;
	  PI_Controller((p_PI_Control)&pi_iq); // iq�� PI����
	  pi_iq.OutF= _IQ10mpy(FilK1,pi_iq.OutF)+_IQ10mpy(FilK2,pi_iq.Out);
  
		if(logicContr.Start_order==1)   //   �ջ����� �ٶ� ����
	 {
		IparkU.Ds=  pi_id.OutF ;    //    
	  IparkU.Qs= 19* pi_spd.Ref;  //
		 if( Speed_estPare.Speed_RPM>300)
		 {
		  logicContr.Start_order=2;			 		  
		 }
		 pi_spd.ui =19* pi_spd.Ref ;
	 }
	  if(logicContr.Start_order==2)   //  �ջ����� �ٶȻ�·�ջ�
	 {
		IparkU.Ds= pi_id.OutF;    //     	 
		IparkU.Qs= pi_spd.OutF + 16*pi_spd.Ref ;   	 
	 }
     if(logicContr.Start_order==3)   //  ����˫�ջ�  
	 {
		IparkU.Ds= pi_id.OutF;    //     
	  IparkU.Qs= pi_iq.OutF;  //   	 
	 }   
	 
   IparkU.Sine=AngleSin_Cos.IQSin;
   IparkU.Cosine=AngleSin_Cos.IQCos;
	 IPARK_Cale((p_IPARK)&IparkU);      // ��park�任

	  Angle_SMOPare.Ialpha = ClarkeI.Alpha; //��Ĥ�۲�����Ҫ���ĸ�����ab��ĵ�ѹ��������
	  Angle_SMOPare.Ibeta  = ClarkeI.Beta;
	  Angle_SMOPare.Valpha = Svpwmdq.Ualpha;
	  Angle_SMOPare.Vbeta  = Svpwmdq.Ubeta;

	  Angle_Cale((p_Angle_SMO)&Angle_SMOPare); //��Ĥ�۲��� ���㷴�綯��
    IQAtan_Pare.Alpha =-Angle_SMOPare.Ealpha ;
		IQAtan_Pare.Beta  =Angle_SMOPare.Ebeta;
	  IQAtan_Cale((p_IQAtan)&IQAtan_Pare); 	 //��Ĥ�۲��� ����Ƕ�
			
	 Svpwmdq.Ualpha =IparkU.Alpha;
	 Svpwmdq.Ubeta = IparkU.Beta;

   SVPWM_Cale((p_SVPWM)&Svpwmdq);     //SVPWM����ռ�ձ�
 
	 Svpwm_Outpwm( );  //PWM���
		 
   TIM_SetCompare3(TIM4 ,   PWM_DUTY[0]); // DACͨ��1   
	 TIM_SetCompare4(TIM4 , (IQAtan_Pare.IQAngle)>>5); // DACͨ��2  
} 


//===========================================================================
// No more.
//===========================================================================
