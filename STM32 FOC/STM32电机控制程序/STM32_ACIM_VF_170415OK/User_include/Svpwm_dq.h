//############################################################
// FILE:    Svpwm_dq.h
// Created on: 2017��1��15��
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

#ifndef  Svpwm_dq_H
#define  Svpwm_dq_H

#include "stm32f10x.h"
#include "IQ_math.h"

typedef struct 	{ 
	        int32_t  Ualpha; 		//  ���ྲֹ����ϵalpha-��
				  int32_t  Ubeta;	//  ���ྲֹ����ϵbeta-�� 
				  int32_t  Ta;		//  ����ʸ��ռ�ձ�Ta
				  int32_t  Tb;		//  ����ʸ��ռ�ձ�Tb
				  int32_t  Tc;		//  ����ʸ��ռ�ձ�Tc
				  int32_t  tmp1;	//  ���ྲֹ����ϵ�ĵ�ѹtemp1   
				  int32_t  tmp2;	//  ���ྲֹ����ϵ�ĵ�ѹtemp2
				  int32_t  tmp3;	//  ���ྲֹ����ϵ�ĵ�ѹtemp3
				  uint16_t VecSector;	// ʸ���ռ�������
				} SVPWM , *p_SVPWM ;

#define SVPWM_DEFAULTS  { 0,0,0,0,0,0,0,0,0}  // ��ʼ������

void  SVPWM_Cale(p_SVPWM pV);

#endif /* Svpwm_dq*/
