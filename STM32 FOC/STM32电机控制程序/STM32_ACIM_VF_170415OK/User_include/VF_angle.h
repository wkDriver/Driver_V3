//############################################################
// FILE: VF_angle.h
// Created on: 2017��1��15��
// Author: XQ
// summary: VF_angle
// VF  
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
#ifndef  VF_angle_H
#define  VF_angle_H
 
#include "IQ_math.h"
#include "stm32f10x.h"

typedef struct {
	    int32_t      SpeedRef ;    // �����ο��ٶ�
	    int32_t      Speed_target ; // ʵ��Ŀ���ٶ�
	    int32_t      Speederror ;   // ʵ��Ŀ���ٶȺͲο��ٶȲ�
	    int32_t      step_Speed ;   // �����ٶ�
	    int32_t      step_angle ;   // �����Ƕ�
	    int32_t      step_anglemax ;// ��󲽽���
	    uint16_t     BASE_FREQ ;    //����Ļ���Ƶ��
	    int32_t      Angle_theta ;  //�Ƕ�ֵ
	    int32_t      Delta_theta ;   //�Ƕȱ仯
	    int32_t      Delta_thetaF;   //�Ƕȱ仯�˲�ֵ
	    uint16_t     Poles ;         //���������
	    int32_t      VF_Vd;          // VF����ʸ��d���ѹ
	    int32_t      VF_Vq;          // VF����ʸ��q���ѹ
	   }VF_Angle;

#define  VF_angle_DEFAULTS   {0,0,0,10,0,0,240,0,0,4,0,0}  // ��ʼ������

void  VF_start_control(void); // VF�ı仯����
void  VFAngle_init(void );  // VF�ĳ�ʼ������
void  VFAngle_cale(void );  // VF�ĸ���Ƶ���ԼӼ��Ƕ�

#endif /* VF_angle_H*/
