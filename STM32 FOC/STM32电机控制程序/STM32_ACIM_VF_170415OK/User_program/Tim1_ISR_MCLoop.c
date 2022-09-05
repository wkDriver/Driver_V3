//############################################################
// FILE: Tim1_ISR_MCLoop.c
// Created on: 2017��1��15��
// Author: XQ
// summary: Tim1_ISR_MCLoop
//  ��ʱ��1������ƣ� �жϻ�·�ջ�����  
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
#include "VF_angle.h"
#include "Task_function.h"
#include "Timer.h"
#include "Usart_RS232.h"
#include "Tim4_Encoder_PWMDAC.h"
 
extern   ADCSamp    ADCSampPare;
extern   uint16_t   PWM_DUTY[3];
extern   logic      logicContr;
extern   TaskTime   TaskTimePare;  
extern   CLARKE     ClarkeI;
extern   PARK       ParkI;
extern   IPARK      IparkU;
extern   SVPWM      Svpwmdq;
extern   VF_Angle   VF_AnglePare;
extern   IQSin_Cos  AngleSin_Cos;
extern   Test       TestPare;
 
 
uint16_t  FilK1=328;
uint16_t  FilK2=696;

void TIM1_UP_IRQHandler(void)// ����ADC�жϲ����͵����·����
{
	//�˳�������ж�һֱִ��
	 TIM_ClearFlag(TIM1, TIM_FLAG_Update); //�����־λ

	 VFAngle_cale( ); // VF�ǶȺ���

	 TaskTimePare.PWMZD_count++;
   if(TaskTimePare.PWMZD_count==25 ) // 2ms���¼�����
	 {
	   TaskTimePare.PWMZD_count=0;
     VF_start_control( );   // VF���߿��ƺ���                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
     knob_control( );       //ת�ѵ�λ�����ٵĿ���

// ���Բ������		 
     TestPare.fact_BUS_Voil= ADCSampPare.BUS_Voltage;
	   TestPare.fact_BUS_Curr= ADCSampPare.BUS_Curr;
	   TestPare.Speed_fact= 1 ;       
	   TestPare.Speed_target= 1;	
   }
	
	  ADC_Sample( );   // �����ĸ�ߵ�����ѹ�ɼ�
  
  	ClarkeI.As=ADCSampPare.PhaseU_Curr;
	  ClarkeI.Bs=ADCSampPare.PhaseV_Curr;

	  CLARKE_Cale((p_CLARKE)&ClarkeI );  // CLARKE�任

	  ParkI.Alpha=ClarkeI.Alpha;
	  ParkI.Beta=ClarkeI.Beta;
 	 	
	  AngleSin_Cos.IQAngle=VF_AnglePare.Angle_theta;
 
	  IQSin_Cos_Cale((p_IQSin_Cos)&AngleSin_Cos); //�ż�λ�ýǶȣ������Ҽ��㺯��

		ParkI.Sine =AngleSin_Cos.IQSin;  
	  ParkI.Cosine =AngleSin_Cos.IQCos;   

	  PARK_Cale((p_PARK)&ParkI); // park�任
 
	  IparkU.Ds=0;   // �����ٶ� 
	  IparkU.Qs= VF_AnglePare.VF_Vq  ; //VF�ĵ�ѹʸ��ֵ
      
    IparkU.Sine=AngleSin_Cos.IQSin;
    IparkU.Cosine=AngleSin_Cos.IQCos;
	  IPARK_Cale((p_IPARK)&IparkU);   //��park�任
 	
	  Svpwmdq.Ualpha =IparkU.Alpha;
	  Svpwmdq.Ubeta = IparkU.Beta;

    SVPWM_Cale((p_SVPWM)&Svpwmdq); //SVPWM����ռ�ձ�

    Svpwm_Outpwm( );  // PWM���  
		
    TIM_SetCompare3(TIM4 , (VF_AnglePare.Angle_theta>>5)); // DACͨ��1 Ӳ����·RC�˲����ֱ������
	  TIM_SetCompare4(TIM4 , ( IparkU.Qs )>>5); // DACͨ��2 Ӳ����·RC�˲����ֱ������
} 


//===========================================================================
// No more.
//===========================================================================
