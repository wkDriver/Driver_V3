//############################################################
// FILE: Timer.h
// Created on: 2017��1��18��
// Author: XQ
// summary: Timer_ 
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
   
#ifndef _TIMER_H
#define _TIMER_H 

#include "stm32f10x.h"

typedef struct {	
	      uint8_t   PWMZD_count;	  // ��PWM�м���  1/12.5K *25=2ms
        uint8_t   IntClock_10ms; 	// 10msʱ�ӱ�־
        uint8_t   Tim10ms_flag;   // 10ms��־
        uint8_t   Tim100ms_count; //100ms����
        uint8_t   Tim100ms_flag;  //100ms�¼���־λ
        uint8_t   Tim500ms_count; //500ms����
        uint8_t   Tim500ms_flag; //500ms�¼���־λ
        uint8_t   Tim1s_count;  //1s����
        uint8_t   Tim1s_flag ;  //1s�¼���־λ
        uint8_t   Tim10s_count; //10s����
        uint8_t   Tim10s_flag ; //10s�¼���־λ
        uint8_t   Tim1min_count; //1����
        uint8_t   Tim1min_flag ; //1�����¼���־λ
	   }TaskTime;

#define  TaskTime_DEFAULTS  {0,0,0,0,0,0,0,0,0,0,0,0,0}  // ��ʼ������
   
void SysTickConfig(void);  // �δ�ʱ��
void RunSystimer(void);    // ���м����¼���־
void CLEAR_flag(void);     // ����¼���־λ

#endif /* __TIMER_H */

//===========================================================================
// No more.
//===========================================================================
