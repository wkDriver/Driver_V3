//############################################################
// FILE: Tim4_Encoder_PWMDAC.c
// Created on: 2016��1��15��
// Author: XQ
// summary: Tim4_Encoder_PWMDAC
//   �����������Ķ�ʱ��4   
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

#include "Tim4_Encoder_PWMDAC.h"
#include "stm32f10x_exti.h" 
 
extern  EQEP   EQEPPare; 
  
void TIM4_Encoder_Config(void)//��ʱ��4��ʼ���ı���������
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef        TIM_ICInitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ʹ��TIM4
	
	TIM_DeInit(TIM4);
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
  TIM_TimeBaseStructure.TIM_Period =(uint16_t) (SystemCoreClock / 18000) - 1;   // 5000���� 
  TIM_TimeBaseStructure.TIM_Prescaler =0;	    //����Ԥ��Ƶ��
  TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;	//����ʱ�ӷ�Ƶϵ��������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ
	/*��ʼ��TIM4��ʱ�� */
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
	/*-----------------------------------------------------------------*/
	//��������                        ����ģʽ
	TIM_EncoderInterfaceConfig(TIM4,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //TIM_ICPolarity_Rising�����ز���
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 6;         //�Ƚ��˲���
  TIM_ICInit(TIM4, &TIM_ICInitStructure);
  
	TIM_Cmd(TIM4, ENABLE);   //ʹ�ܶ�ʱ��4
}
/*
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
*/
void  QEPEncoder_Cale(void)
{ 
  EQEPPare.MechTheta = TIM_GetCounter(TIM4);  // ����������еλ���ź�
  EQEPPare.ElecThetaYS = EQEPPare.MechTheta %1000; // ����4�Լ��ĵ����Ƕ�
  EQEPPare.ElecTheta = EQEPPare.ElecThetaYS<<6;
  EQEPPare.JZElecTheta= EQEPPare.ElecTheta+ EQEPPare.initial_angle; // �������λ��
	
	 if(   EQEPPare.JZElecTheta> 65536)
     EQEPPare.JZElecTheta-=65536;
   else if( EQEPPare.JZElecTheta<0)
     EQEPPare.JZElecTheta+=65536;	
}

void QEPEncoder_Speedcale(void)  // 2msִ��һ�� �ٶȼ���
{  
 	 EQEPPare.Speed_ele_angleIQ =EQEPPare.Oid_JZElecTheta -EQEPPare.JZElecTheta;
   if( EQEPPare.Speed_ele_angleIQ < 0)
   EQEPPare.Speed_ele_angleIQ+=65536; 	 
 
 	 EQEPPare.Speed_ele_angleIQFitter= _IQ10mpy(EQEPPare.SpeedK1, EQEPPare.Speed_ele_angleIQFitter)+_IQ10mpy(EQEPPare.SpeedK2,  EQEPPare.Speed_ele_angleIQ);
   EQEPPare.Speed_RPM = (EQEPPare.Speed_ele_angleIQ*EQEPPare.speed_coeff)>>16; // ���Ƕ� 2pi��һȦ 65536
	 EQEPPare.Oid_JZElecTheta = EQEPPare.JZElecTheta ;
}

void  EQEP_Pare_init( void )
{
	// ��ʼ�Ƕ��������������������ĸ�ߵ������󣬿��Խ�����ͱ���������λ��һ���Ķ�������
	// ��ʼ�Ƕ��������������������ĸ�ߵ�������Ҳ���Ըı�һ���initial_angleֵ����1000Ϊ��λ���ߵ��Լӻ��߼�
	EQEPPare.initial_angle=22180;   //��ʼλ�ýǶȣ���Ҫ����������������
	EQEPPare.SpeedK1=355;   //�˲���ϵ��������ֵ
	EQEPPare.SpeedK2=669;	
	EQEPPare.Poles=4;
	EQEPPare.speed_coeff=(1000*60)/(2*EQEPPare.Poles ); // 2�������һ�νǶȲ�ֵ 1000/2ms=500   =7500	 
}


void EXTIX_Init(void)
{
 	  EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//�ⲿ�жϣ���Ҫʹ��AFIOʱ��
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource5);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line5;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//�Ͻ��ش���
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
 
		NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  
}

void EXTI9_5_IRQHandler(void) // Z�ź��ⲿ�ж����������
{	
  TIM4->CNT = 0; // 0---4000  �������
  TIM_Cmd(TIM4, ENABLE);  
	EXTI_ClearITPendingBit(EXTI_Line5);  //���EXTI0��·����λ
}


//===========================================================================
// No more.
//===========================================================================
