//############################################################
// FILE: Tim4_Encoder_PWMDAC.h
// Created on: 2017��1��18��
// Author: XQ
// summary: Tim4_Encoder_PWMDAC
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
   
#ifndef _Tim4_Encoder_PWMDAC_H
#define _Tim4_Encoder_PWMDAC_H 

#include "IQ_math.h"
#include "stm32f10x.h"

typedef struct {	    
	    int32_t  ElecThetaYS;      // ���������λ�ýǶȵ�Ƕ� 0---1024 0--360
	    int32_t  ElecTheta;        // ����Ĵż���Ƕ� 0---65536 0--360   Electrical angle
	    int32_t  MechTheta;        // ���������λ�û�е�Ƕ� 0--4096   Mechanical Angle	   
	    int32_t  JZElecTheta;      // ��������ż�λ�ýǶ� 
	    uint16_t Poles;            //   Number of pole pairs  	  
	    int32_t  initial_angle;    //  �����ʼλ�ýǶ�   
      int32_t  Oid_JZElecTheta;  //  ��������ʷ����ż�λ�ýǶ� 
      int32_t	 Speed_ele_angleIQ;//�����ٶȼ���ĵ�Ƕ�
	    int32_t  Speed_ele_angleIQFitter;// �˲����ٶȵ�Ƕ�
		  uint16_t Speed_RPM;     // ����ٶ�RPM  		 
	    uint32_t speed_coeff;  // �����ٶȵ�ϵ�� 
    	uint16_t SpeedK1;    // �ٶȼ���һ�׵�ͨ�˲���ϵ��1
	    uint16_t SpeedK2;    // �ٶȼ���һ�׵�ͨ�˲���ϵ��2
   } EQEP;

#define  EQEP_DEFAULTS  { 0,0,0,0,4,0,0,0,0,0,0,364,660} // ��ʼ������
 
void TIM4_Encoder_Config(void); //��ʱ��4��ʼ���ı���������
void EXTIX_Init(void);          // Z�źű����������ⲿ�ж�
void QEPEncoder_Cale(void);     //����������Ƕȼ���
void EQEP_Pare_init(void );     //������������ʼ��
void QEPEncoder_Speedcale(void);//�������ٶȼ���
#endif /* __Tim4_Encoder_PWMDAC_H */

//===========================================================================
// No more.
//===========================================================================
