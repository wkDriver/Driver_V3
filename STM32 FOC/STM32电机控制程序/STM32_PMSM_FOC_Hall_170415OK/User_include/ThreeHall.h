//############################################################
// FILE:  ThreeHall.h
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

#ifndef ThreeHall_H
#define ThreeHall_H
#include "stm32f10x.h"
#include "IQ_math.h"

typedef struct {
	    uint8_t       HallUVW[3];   // ��ȡ���������Ķ�Ӧ״̬
	    uint8_t       Hall_State;   // ��ǰ����״̬
	    uint8_t       OldHall_State; // ��ʷ����״̬
	    uint8_t       HallLX_State;  // ��ǰ����ʷ����״̬����һ���ֽ�����
	    uint8_t       Hall_num[8];    // ���ֻ���״̬
	    int32_t       Hall_angle[8];  // �˸������Ƕȸ��ݲ�ͬ״̬
			int32_t       step_angle_error; //�����Ƕ����
	    int32_t       step_angle ;      //�����Ƕ� 
			int32_t       step_angleFitter ;//�����Ƕ� �˲�ֵ
	    uint16_t      Speed_count;      //�ٶȼ���ֵ
	    uint16_t      Speed_countFitter; //�ٶȼ����˲�ֵ
      uint16_t      Speed_count_old;   //�ٶȼ�����ʷֵ
			uint32_t      speed_coeff;       //�ٶ�ϵ��
	    uint8_t       Poles;             //���������
	    uint8_t       Move_State;        //�����ת״̬
      int32_t       initial_angle;     //�����ʼ�Ƕ�
      int32_t       angleIQ;           //�����������Ƕ�
      uint16_t      Speed_RPM;         //�����ת�ٶ� 
      int32_t       Speed_ele_angleIQ; //�ٶȵ�Ƕ�ֵ�������ٶȣ�
      int32_t       Speed_ele_angleIQFitter; //�ٶȵ�Ƕ�ֵ�������ٶȣ�
      int32_t       old_ele_angleIQ;   // �����ʷ��Ƕ�
      int32_t       ele_angleIQ;       // �����Ƕ�
	   } Hall;

#define  Hall_DEFAULTS {0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0} // ��ʼ������

void ThreeHallPara_init(void);  //����������ǶȲ�����ʼ��
void ThreeHallanglecale(void);  //����������ǶȺ���
void Hall_Three_Speedcale(void); //�������Ƕȼ����ٶȺ���
#endif /* ThreeHall_H_*/
//===========================================================================
// End of file.
//===========================================================================
