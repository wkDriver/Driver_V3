//############################################################
// FILE:  PI_Cale.h
// Created on: 2017��1��11��
// Author: XQ
// summary: Header file  and definition
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

#ifndef  PI_Cale_H
#define  PI_Cale_H

#include "IQ_math.h"
#include "stm32f10x.h"

typedef struct {
	     int32_t  Ref;   // PI���Ƶĸ�������
			 int32_t  Fbk;   // PI���Ƶķ������� 			 
			 int32_t  Out;   // PI���Ƶ�������� 		 
			 int32_t  OutF;  // PI���Ƶ��˲���������� 	
			 int32_t  Kp;		 // PI���Ƶı������� 	 
			 int32_t  Ki;		 // PI���ƵĻ��ֲ��� 	  
			 int32_t  Umax;	 // PI���Ƶ������������ֵ���� 	  	 
			 int32_t  Umin;	 // PI���Ƶ����������С��ֵ���� 	 
			 int32_t  up;		 // PI���Ƶı������������ 
			 int32_t  ui;		 // PI���ƵĻ������������ 	 
			 int32_t  v1;		 // PI���Ƶ���ʷ�������� 	 	 
			 int32_t  i1;		 // PI���Ƶ���ʷ������������� 	 		 
	   } PI_Control, *p_PI_Control ;

#define PI_Control_DEFAULTS {0,0,0,0,0,0,32000,0,0,0,0,0}  // ��ʼ������

void  PI_Controller(p_PI_Control  pV);  //PI�����㷨����
void  PI_Pare_init(void );    //PI���Ʋ�����ʼ��
#endif /* PI_Cale*/
