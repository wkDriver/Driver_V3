//############################################################
// FILE: VF_angle.h
// Created on: 2017��1��19��
// Author: XQ
// summary:  Header file  and definition
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

#ifndef  VF_angle_H
#define  VF_angle_H
 
#include "IQ_math.h"
#include "stm32f10x.h"

typedef struct {
	uint16_t      Freq_T_Ref;    //�������ݹ̶�����״̬����Ƶ��
	uint16_t      Voilage_Ref;   //���������ο���ѹ
	uint16_t      VF_huanxCount; //�������
	uint16_t      VF_Count;      //VF����
	uint16_t      VF_state;      //VF����״̬
	uint16_t      VF_num[6];     //VF��������˳��
	uint16_t      OldVF_State;   //��ʷVF����״̬ 
	uint16_t      initial_state;  //VF��ʼ״̬��λ
	  }VF_start;

#define  VF_start_DEFAULTS   {0,0,0,0,0,0,0,0} // ��ʼ������


void  VF_start_control(void); //�޸�������VF�̶�����
void  VF_start_init(void );   // VF�̶�����������ʼ��

#endif /* VF_angle_H*/
