//############################################################
// FILE: stm32f10x_it.c
// Created on: 2017��1��15��
// Author: XQ
// summary: �����жϿ���
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

#include "stm32f10x_it.h"
#include "stm32f10x.h"
#include "GPIO_int.h"
#include "Timer.h"
#include "ADC_int.h"
#include "Tim1_PWM.h"

extern  TaskTime       TaskTimePare;   
 
void SysTick_Handler(void)
{
 TaskTimePare.IntClock_10ms=1;
}
 void TIM1_BRK_IRQHandler(void)
{
	Stop_Motor( );
  TIM_ClearITPendingBit(TIM1, TIM_IT_Break);
   
}
 

//===========================================================================
// No more.
//===========================================================================
