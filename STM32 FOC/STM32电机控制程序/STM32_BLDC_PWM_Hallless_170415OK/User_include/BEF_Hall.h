//############################################################
// FILE:  BEF_Hall.h
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

#ifndef  BEF_Hall_H
#define  BEF_Hall_H
#include "stm32f10x.h"
#include "IQ_math.h"
 
typedef struct {
	    uint8_t       HallUVW[3];  // ��ȡ�������綯�ƻ����Ķ�Ӧ״̬
	    uint8_t       Hall_State;  //��ǰ���綯�ƻ���״̬ 
	    uint8_t       OldHall_State;  //��ʷ���綯�ƻ���״̬
			int32_t       step_angle_error; //�����Ƕ����
	    int32_t       step_angle ;   //�����Ƕ� 
			int32_t       step_angleFitter ;  //�����Ƕ� �˲�ֵ
	    uint16_t      Speed_count;  //�ٶȼ���ֵ
	    uint16_t      Speed_countFitter;  //�ٶȼ����˲�ֵ
      uint16_t      Speed_count_old;  //�ٶȼ�����ʷֵ
			uint32_t      speed_coeff;  //�ٶ�ϵ��
	    uint8_t       Poles;   //���������
	    uint8_t       Move_State;   //�����ת״̬
      uint16_t      Speed_RPM;    //�����ת�ٶ� 
      uint16_t      Speed_RPMF;	  //�����ת�˲��ٶ� 
	   } Hall;

#define  Hall_DEFAULTS {0,0,0,0,0,0,0,0,0,0,4,0,0,0}  // ��ʼ������


#define   Hall_num1   0x5  // VF���ݹ̶�����״̬����˳��״̬
#define   Hall_num2   0x1
#define   Hall_num3   0x3
#define   Hall_num4   0x2
#define   Hall_num5   0x6
#define   Hall_num6   0x4

#define   BEFCAP_numZ1  0x2    // 0x4  ���ݷ��綯��״̬��ת����˳��״̬
#define   BEFCAP_numZ2  0x6    // 0x5
#define   BEFCAP_numZ3  0x4     //0x1
#define   BEFCAP_numZ4  0x5    // 0x3
#define   BEFCAP_numZ5  0x1    // 0x2
#define   BEFCAP_numZ6  0x3     //0x6

#define   BEFCAP_numF1  0x4    // 0x4  ���ݷ��綯��״̬��ת����˳��״̬
#define   BEFCAP_numF2  0x5    // 0x5
#define   BEFCAP_numF3  0x1    // 0x1
#define   BEFCAP_numF4  0x3    // 0x3
#define   BEFCAP_numF5  0x2    // 0x2
#define   BEFCAP_numF6  0x6    // 0x6	
 
void BEF_ThreeCAPPara_init(void );  //���ݷ��綯��״̬������ʼ��
void BEFHall_huanxkz(void);   //���ݷ��綯��״̬���� 
#endif /* ThreeHall_H_*/
//===========================================================================
// End of file.
//===========================================================================
