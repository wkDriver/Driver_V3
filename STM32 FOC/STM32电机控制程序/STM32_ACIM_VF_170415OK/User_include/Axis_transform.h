//############################################################
// FILE:  Axis_transform.h
// Created on: 2017��1��5��
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

#ifndef Axis_transform_H
#define Axis_transform_H

#include "stm32f10x.h"
#include "IQ_math.h"

typedef struct {  
	        int32_t  As;  		//  �������A
				  int32_t  Bs;			//  �������B
				  int32_t  Cs;			//  �������C
				  int32_t  Alpha;		//  ���ྲֹ����ϵ Alpha ��
				  int32_t  Beta;		//  ���ྲֹ����ϵ Beta ��
		 	 	} CLARKE ,*p_CLARKE ;

#define  CLARKE_DEFAULTS {0,0,0,0,0}  // ��ʼ������

typedef struct {  
	        int32_t  Alpha;  	//  ���ྲֹ����ϵ Alpha ��
		 		  int32_t  Beta;	 	//  ���ྲֹ����ϵ Beta ��
		 	 	  int32_t  Angle;		//  ����ż�λ�ýǶ�0---65536����0---360�� 
		 	 	  int32_t  Ds;			//  ���������ת����ϵ�µ�d�����
		 	 	  int32_t  Qs;			//  ���������ת����ϵ�µ�q�����
		 	 	  int32_t  Sine;    //  ���Ҳ�����-32768---32767  -1��1 
		 	 	  int32_t  Cosine;  //  ���Ҳ�����-32768---32767  -1��1
		 	 	} PARK , *p_PARK ;

#define  PARK_DEFAULTS {0,0,0,0,0,0,0}  // ��ʼ������

typedef struct {  
	        int32_t  Alpha;  		// ���ྲֹ����ϵ Alpha ��
		 	 	  int32_t  Beta;		  // ���ྲֹ����ϵ Beta ��
		 	 	  int32_t  Angle;		  // ����ż�λ�ýǶ�0---65536����0---360��  
		 	 	  int32_t  Ds;			  //  ���������ת����ϵ�µ�d�����
		 	 	  int32_t  Qs;			  //  ���������ת����ϵ�µ�q�����
		 	    int32_t  Sine;		  //  ���Ҳ�����-32768---32767  -1��1 
		 	    int32_t  Cosine;		//  ���Ҳ�����-32768---32767  -1��1
		 	    } IPARK , *p_IPARK;

#define  IPARK_DEFAULTS {0,0,0,0,0,0,0}  // ��ʼ������

void  CLARKE_Cale(p_CLARKE  pV); // ���ൽ����任 �����˱任
void  PARK_Cale(p_PARK pV)	 ;   // ���ൽ����任 �¿˱任
void  IPARK_Cale(p_IPARK pV) ;   // ���ൽ����任���¿˱任

#endif /* Axis_transform*/
//===========================================================================
// End of file.
//===========================================================================
