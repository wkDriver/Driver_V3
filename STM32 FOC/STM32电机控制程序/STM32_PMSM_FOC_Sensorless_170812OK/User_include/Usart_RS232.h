//############################################################
// FILE:   Usart_RS232.h
// Created on: 2017��1��21��
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
 
#ifndef Usart_RS232_H
#define Usart_RS232_H
#include "IQ_math.h"
#include "stm32f10x.h"

typedef struct {		     
        uint8_t   Uart_txdr[8];  //���ڷ�������
        uint8_t   Uart_rxdr[8];  //���ڽ�������
	      uint16_t  fact_BUS_Curr; // ʵ��ĸ�ߵ���
	      uint16_t  fact_BUS_Voil; // ʵ��ĸ�ߵ�ѹ
		    uint16_t  iq_test;       // q����Ե���
	      uint16_t  id_test;       // d����Ե���
	      uint16_t  uq_test;       // q����Ե�ѹ
	      uint16_t  ud_test;       // d����Ե�ѹ
	      int16_t   IqRef_test;    // d�������������
	      uint16_t  Speed_target;  // Ŀ��ת��
	      uint16_t  Speed_fact;    // ʵ��ת��
        uint8_t   Rece_flag;     // ���ձ�־  
	      uint8_t   Rxdr_byte;     // �����ֽ���
        uint8_t   chaoshi_jishu;  //��ʱ�жϼ���
        uint8_t   chaoshi_pand;   //��ʱ�ж�ʱ��
        uint8_t   chaoshi_pandold;//��ʷ��ʱ�ж�ʱ��
        uint8_t   chaoshi_shu;    //��ʱ�ж���
	   }Test;

#define  Test_DEFAULTS  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}  // ��ʼ������
 
void Uart3_RS232TX_sen(void); //RS232���ͺ���
void Usart3_RS232_init(void); //RS232���ڳ�ʼ������
void Uart2_Sendlen(uint8_t *data,u8 len); //����һ���ֽں���
void USART3_IRQHandler(void);   //�жϽ��պ���
void  ReceiveData_chuli(void);  //�������ݴ�����
#endif  // end of SCI_RS232.h definition

//===========================================================================
// End of file.
//===========================================================================
