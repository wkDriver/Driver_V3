//############################################################
// FILE:  Sensorless_SMO.c
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

#include "Sensorless_SMO.h"
#include "IQ_math.h"
#define PI 3.14159265358979

extern  Angle_SMO   Angle_SMOPare ;
extern  Speed_est   Speed_estPare ;
extern  SMO_Motor   SMO_MotorPare ;
extern  IQAtan     IQAtan_Pare; 

void  Angle_Cale(p_Angle_SMO  pV)
{
    /*	Sliding mode current observer	*/
    pV->EstIalpha = _IQmpy(pV->Fsmopos,pV->EstIalpha) + _IQmpy(pV->Gsmopos,(pV->Valpha-pV->Ealpha-pV->Zalpha));
    pV->EstIbeta  = _IQmpy(pV->Fsmopos,pV->EstIbeta)  + _IQmpy(pV->Gsmopos,(pV->Vbeta -pV->Ebeta -pV->Zbeta ));

	/*	Current errors	*/
    pV->IalphaError = pV->EstIalpha - pV->Ialpha;
    pV->IbetaError  = pV->EstIbeta  - pV->Ibeta;

	/*  Sliding control calculator	*/
	/* pV->Zalpha=pV->IalphaError*pV->Kslide/pV->E0) where E0=0.5 here*/
	 pV->Zalpha = _IQmpy(IQsat(pV->IalphaError,pV->E0,-pV->E0),_IQmpy2(pV->Kslide));
	 pV->Zbeta  = _IQmpy(IQsat(pV->IbetaError ,pV->E0,-pV->E0),_IQmpy2(pV->Kslide));

	/*	Sliding control filter -> back EMF calculator	*/
    pV->Ealpha = pV->Ealpha + _IQmpy(pV->Kslf,(pV->Zalpha-pV->Ealpha));
    pV->Ebeta  = pV->Ebeta  + _IQmpy(pV->Kslf,(pV->Zbeta -pV->Ebeta));
 
}

void  SMO_Pare_init(void )  // ���������ʼ��
{
	SMO_MotorPare.Rs = 0.121;    
	SMO_MotorPare.Ls = 0.00258; 
	SMO_MotorPare.Ib = 6 ;   
	SMO_MotorPare.Vb = 14 ;
	SMO_MotorPare.Ts = 0.00008;
	SMO_MotorPare.POLES=4;
	SMO_MotorPare.BASE_FREQ=135;  
	SMO_MotorPare.Fsmopos = exp((-SMO_MotorPare.Rs/SMO_MotorPare.Ls)*(SMO_MotorPare.Ts));
	SMO_MotorPare.Gsmopos = (SMO_MotorPare.Vb/SMO_MotorPare.Ib)*(1/SMO_MotorPare.Rs)*(1-SMO_MotorPare.Fsmopos);

	Angle_SMOPare.Fsmopos = (int32_t)( SMO_MotorPare.Fsmopos*32768);
	Angle_SMOPare.Gsmopos = (int32_t)( SMO_MotorPare.Gsmopos*32768);
	Angle_SMOPare.Kslide = 2000 ;  //     
	Angle_SMOPare.Kslf =5000;      //      
	Angle_SMOPare.E0= 32670 ;      //    
	Speed_estPare.SpeedK1=355;
	Speed_estPare.SpeedK2=669;
	Speed_estPare.speed_coeff=(1000*60)/(2*SMO_MotorPare.POLES ); // 2�������һ�νǶȲ�ֵ 1000/2ms=500   =7500	
}

void SMO_Speedcale(void)  // 2msִ��һ��
{
   Speed_estPare.ele_angleIQ= IQAtan_Pare.JZIQAngle; 
 	 Speed_estPare.Speed_ele_angleIQ =Speed_estPare.ele_angleIQ- Speed_estPare.old_ele_angleIQ ;
   if( Speed_estPare.Speed_ele_angleIQ <0)
   Speed_estPare.Speed_ele_angleIQ+=65536; 	 
  
 	 Speed_estPare.Speed_ele_angleIQFitter= _IQ10mpy(Speed_estPare.SpeedK2, Speed_estPare.Speed_ele_angleIQFitter)+_IQ10mpy(Speed_estPare.SpeedK1,  Speed_estPare.Speed_ele_angleIQ);
   Speed_estPare.Speed_RPM = (Speed_estPare.Speed_ele_angleIQ*Speed_estPare.speed_coeff)>>16; // ���Ƕ� 2pi��һȦ 65536
	 
	 if( Speed_estPare.Speed_RPM>=2000)
	  Speed_estPare.Speed_RPM=0;
	 Speed_estPare.old_ele_angleIQ = Speed_estPare.ele_angleIQ ;
}
 

//===========================================================================
// No more.
//===========================================================================

