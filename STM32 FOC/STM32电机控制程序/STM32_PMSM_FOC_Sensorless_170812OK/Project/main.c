   //############################################################
// FILE:  main.c
// Created on: 2017��1��15��
// Author: XQ
// summary: main �������MCU�ײ��ʼ����ͨѶ����
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

#include "stm32f10x.h"
#include "GPIO_int.h"
#include "Timer.h"
#include "ADC_int.h"
#include "Tim1_PWM.h"
#include "Axis_transform.h"  
#include "Svpwm_dq.h"
#include "IQ_math.h"
#include "Tim4_Encoder_PWMDAC.h"
#include "PI_Cale.h"
#include "Task_function.h"
#include "Usart_RS232.h"
#include "CAN.h"
#include "Sensorless_SMO.h"
 
PI_Control   pi_spd = PI_Control_DEFAULTS;
PI_Control   pi_id  = PI_Control_DEFAULTS;
PI_Control   pi_iq  = PI_Control_DEFAULTS;
 
Test         TestPare=Test_DEFAULTS;
TaskTime     TaskTimePare=TaskTime_DEFAULTS;
logic        logicContr=logic_DEFAULTS;
ADCSamp      ADCSampPare=ADCSamp_DEFAULTS;
CLARKE       ClarkeI= CLARKE_DEFAULTS;
PARK         ParkI=PARK_DEFAULTS;
IPARK        IparkU=IPARK_DEFAULTS;
SVPWM        Svpwmdq=SVPWM_DEFAULTS;
IQSin_Cos    AngleSin_Cos=IQSin_Cos_DEFAULTS ;
Angle_SMO    Angle_SMOPare = Angle_SMO_DEFAULTS ;
SMO_Motor    SMO_MotorPare=SMO_Motor_DEFAULTS ;
Speed_est    Speed_estPare=Speed_est_DEFAULTS;
IQAtan       IQAtan_Pare=IQAtan_DEFAULTS;
CANSR      CANSRPare=CANSR_DEFAULTS;
 
int main(void)
{
   Delay(10000);
   SysTickConfig();      // ϵͳ�δ�ʱ�� 10msһ��	 
	 logicContr.Run_mode=0;	    // �����ջ�����תģʽ
   GPIO_LED485RE_int( ); // RS485 ������LE
   Init_Gpio_ADC( );     // ADC�����ų�ʼ��
   InitUSART3_Gpio( );   //����3��IO��ʼ��
   InitCAN_Gpio( );      //CANͨѶ��IO��ʼ��
	 Init_Gpio_TIM1_PWM( );// �߼���ʱ��1��6��IO��ʼ��
	 InitThreeHallGpio( ); // ������IO��ʼ��
	 Init_PWMDAC_Gpio( );  // PWM4��IO��ΪDAC��ʼ�� 
	 Usart3_RS232_init( ); // ����3�ĵײ��ʼ��
	 CAN_Config( );        // CANͨѶ�ĵײ��ʼ��
	 DMA_Configuration( ); //ADC����DMA��ȡ���ݳ�ʼ��
	 Delay(10000);
   ADC1_Configuration( );    //ADCģʽ��ʼ��
	 Delay(10000);
   Tim1_PWM_Init( );         //�߼���ʱ��1��ʼ��
   Delay(10000);
	 TIM4PWMDAC_Config( );    //TIM4�� ��ΪDAC��ʼ��
	 Delay(10000);
	 Offset_CurrentReading( ); // �����ĸ�ߵ�������ƫִ��ѹ
	 Delay(10000);
	 PI_Pare_init( );           // ����˫PID������ʼ��		
	 SMO_Pare_init( );         // �޸�����ͬ��������ʼ��
	 	 
	 while(1)
	 {
		RunSystimer( );       // ʱ�������־��ʼ��
    CAN_Sendlen( );       //CAN��ʱ���͵������
	 	Uart3_RS232TX_sen( ); //����3ͨѶ�Ķ�ʱ����
	 	ReceiveData_chuli( ); //�����жϽ������ݴ� ��
	  CAN_Receivechuli( );  //CANͨѶ�жϽ������ݴ���	 
		CLEAR_flag( );        // ���ʱ�������־ 
	 }
}
//===========================================================================
// No more.
//===========================================================================













