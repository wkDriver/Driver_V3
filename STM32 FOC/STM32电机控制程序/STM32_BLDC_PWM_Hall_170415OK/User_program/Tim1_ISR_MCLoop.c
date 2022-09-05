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
#include "ThreeHall.h"
#include "Task_function.h"
#include "PI_Cale.h"
#include "Timer.h"
#include "Usart_RS232.h"
#include "Tim4_Encoder_PWMDAC.h"
 
extern  PI_Control   pi_spd ;
extern   ADCSamp    ADCSampPare;
extern   uint16_t   PWM_DUTY[3] ;
extern   Hall       Hall_Three;
extern   logic      logicContr;
extern   TaskTime   TaskTimePare;  
extern   Test       TestPare;

extern  uint16_t  DUTY;

uint16_t  FilK1=328;
uint16_t  FilK2=696;
 
void TIM1_UP_IRQHandler(void)// ����ADC�жϲ����͵����·����
{
	//�˳�������ж�һֱִ��
	 TIM_ClearFlag(TIM1, TIM_FLAG_Update); 
 
   ThreeHall_huanxkz( ); // �����������л�PWM����MOS
	 
	 TaskTimePare.PWMZD_count++;
	
   if(TaskTimePare.PWMZD_count==25 ) //2MSʱ������
	 {
	   TaskTimePare.PWMZD_count=0;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
    	 
		  knob_control( );  //ת�ѵ�λ�����ٵĿ���

      //ͨѶ���Բ������ 
      // ���Բ������
      TestPare.fact_BUS_Voil= ADCSampPare.BUS_Voltage;
	    TestPare.fact_BUS_Curr= ADCSampPare.BUS_Curr;
	    TestPare.Speed_fact= ( pi_spd.Fbk>>3);
	    TestPare.Speed_target=( pi_spd.Ref>>3);	 	   
   
		  pi_spd.Fbk = Hall_Three.Speed_RPMF ;  //   0---4096RPM	   	 
	    PI_Controller((p_PI_Control)&pi_spd);  // �ٶȻ�PI���� 
	    pi_spd.OutF= _IQ10mpy(FilK1,pi_spd.OutF)+_IQ10mpy(FilK2,pi_spd.Out); 
 
		  if(logicContr.Control_Mode==1)
	    {
         DUTY = 2*pi_spd.Ref;  // �ջ�  PWM���
	    } 
	    else if(logicContr.Control_Mode==2)
	    {
         DUTY = pi_spd.OutF;  // �ջ� PWM���
	    }  
 	 
   }
	 
   ADC_Sample( ); // ����ĸ�ߵ�����ѹ�ɼ�
 	 
   TIM_SetCompare3(TIM4 , Hall_Three.Speed_RPMF); // DACͨ��1    
	 TIM_SetCompare4(TIM4 , DUTY);                  // DACͨ��2 
} 


//===========================================================================
// No more.
//===========================================================================
