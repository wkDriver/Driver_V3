//############################################################
// FILE:  Sensorless_SMO.h
// Created on: 2017��1��18��
// Author: XQ
// summary: Sensorless_SMO
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

#ifndef  Sensorless_SMO_H
#define  Sensorless_SMO_H

#include "IQ_math.h"
#include "stm32f10x.h" 
#include "math.h"
 

typedef struct {
	     int32_t  Valpha;       //���ྲֹ����ϵalpha-���ѹ	
	     int32_t  Ealpha;       //���ྲֹ����ϵalpha-�ᷴ�綯��
	     int32_t  Zalpha;       //alfa�ỬĤ�۲�����zƽ��
	     int32_t  Gsmopos;      //��Ĥ����1
	     int32_t  EstIalpha;    //��Ĥ����alpha-�����
	     int32_t  Fsmopos;      //��Ĥ����2
	     int32_t  Vbeta;        //���ྲֹ����ϵbeta-���ѹ	 
	     int32_t  Ebeta;  	    //���ྲֹ����ϵbeta-�ᷴ�綯��
	     int32_t  Zbeta;        //beta�ỬĤ�۲�����zƽ��	 
	     int32_t  EstIbeta;     //��Ĥ����beta-����� 
	     int32_t  Ialpha;  	    //���ྲֹ����ϵalpha-�����
	     int32_t  IalphaError;  //���ྲֹ����ϵbeta-��������
	     int32_t  Kslide;       //�˲���ϵ��	 
	     int32_t  Ibeta;  	    //���ྲֹ����ϵbeta-����� 
	     int32_t  IbetaError;   //���ྲֹ����ϵbeta-��������
	     int32_t  Kslf;         //�˲���ϵ��
	     int32_t  E0;	          //��Ĥ�ĵ��������޷�ֵ 0.5
	   } Angle_SMO, *p_Angle_SMO;

#define Angle_SMO_DEFAULTS {0,0,0,0,0,0,0,0,0,0,0,0} // ��ʼ������

typedef struct {
	    int32_t  Speed_ele_angleIQ;  //�ٶȵ�Ƕ�ֵ�������ٶȣ�  
	    int32_t  old_ele_angleIQ;   // �����ʷ��Ƕ�
	    int32_t  ele_angleIQ;      // �����Ƕ�
	    int32_t  Speed_ele_angleIQFitter;  //�ٶȵ�Ƕ�ֵ�������ٶȣ�    	 
	    uint16_t Speed_RPM;       	 //�����ת�ٶ� 	 
	    uint32_t speed_coeff;       //�����ٶȵ�ϵ��
    	    uint16_t SpeedK1;           // �ٶ��˲�ϵ��K1
	    uint16_t SpeedK2;         // �ٶ��˲�ϵ��K2
	   }Speed_est;

#define Speed_est_DEFAULTS {0,0,0,0,0,0,0,0} // ��ʼ������

typedef struct{
	  float  Rs; 			//����������	 
	  float  Ls;			//���������	  
    float  Ib; 			//����������Ļ�������� 	  
	  float  Vb;			//����������Ļ������ѹ	 
    float  Ts;			 //��������	 
    uint32_t   POLES; // ����ļ�����
    uint32_t   BASE_FREQ; // ����������Ļ���Ƶ��
	  float  Fsmopos;		   //��Ĥ����1
    float  Gsmopos;			 //��Ĥ����2
  }SMO_Motor;

#define SMO_Motor_DEFAULTS {0.0,0.0,0.0,0.0,0.0,0,0,0.0,0.0} // ��ʼ������

void  Angle_Cale(p_Angle_SMO  pV); //��Ĥ���λ�õ�Ƕȼ���
void  SMO_Pare_init (void );   // ��Ĥ�۲����Ĳ�����ʼ��
void SMO_Speedcale(void) ;    //  ��Ĥ�ĽǶȼ����ٶȺ���
#endif /* Sensorless_SMO*/
