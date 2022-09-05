//############################################################
// FILE: Task_function.c
// Created on: 2017��1��18��
// Author: XQ
// summary: Task_function
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//��Ȩ���У�����ؾ�
//DSP/STM32������ƿ�����
//˶������
//��ַ: https://shuolidianzi.taobao.com
//�޸�����:2017/1/23
//�汾��V17.3-1
//Author-QQ: 616264123
//�������QQȺ��314306105
//############################################################

#include "Task_function.h"
#include "Timer.h"
#include "ADC_int.h"
#include "Axis_transform.h"
#include "Tim1_PWM.h"

extern  IPARK          IparkU;
extern  ADCSamp        ADCSampPare;
extern  TaskTime       TaskTimePare;
extern  logic          logicContr;
uint16_t Speed_Ref=0;
 
 
void knob_control(void)
{
	 if( ADCSampPare.RP_speed_Voltage<= 200)
     {
		 logicContr.drive_car=0;
		 logicContr.Start_order=0;
		 logicContr.Qiehuan_count=0;
		 IparkU.Qs=0;
		 IparkU.Qs=0;  
     Speed_Ref=0;			 
	   } 
	   else
	   {
	    logicContr.drive_car=1;
 	    Speed_Ref = (ADCSampPare.RP_speed_Voltage>>1);   // ��λ��ת���ź�
 	    if(Speed_Ref>=2000)
 	    Speed_Ref =2000;
	   }
     if ((logicContr.olddrive_car==0) &&( logicContr.drive_car==1 ))
     {
   	  Start_Motor( );
     }
     else if ((logicContr.olddrive_car==1) &&( logicContr.drive_car==1 ))
	   {
		  logicContr.Start_order=1;
	   }
     else
   	 {
		  Stop_Motor();
		  logicContr.Start_order=0;
	   }
	  logicContr.olddrive_car=logicContr.drive_car;
}


//===========================================================================
// No more.
//===========================================================================
