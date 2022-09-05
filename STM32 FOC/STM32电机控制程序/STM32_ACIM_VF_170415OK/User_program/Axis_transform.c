//############################################################
// FILE:  Axis_transform.c
// Created on: 2017��1��11��
// Author: XQ
// summary:Axis_transform
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//��Ȩ���У�����ؾ�
//DSP/STM32������ƿ�����
//˶������  
//��ַ: https://shuolidianzi.taobao.com
//�޸�����:2017/3/24  
//�汾��V17.3-1   
//Author-QQ: 616264123  
//�������QQȺ��314306105  
//############################################################

#include "Axis_transform.h"
    
//Alpha = Iu
//Beta = (��3/3*2^15*Iu + 2*��3/3*2^15*Iw)/(2^15)
void  CLARKE_Cale(p_CLARKE  pV)
{
	pV->Alpha = pV->As;
	pV->Beta = _IQmpy((pV->As +_IQmpy2(pV->Bs)),18918);  //  _IQ(0.57735026918963)
}

// Parking Id,Iq
// Id = Ialpha*cos+Ibeta*sin
// Iq = Ibeta*cos-Ialpha*sin
void  PARK_Cale(p_PARK pV)
{
	pV->Ds = _IQmpy(pV->Alpha,pV->Cosine) + _IQmpy(pV->Beta,pV->Sine);
  pV->Qs = _IQmpy(pV->Beta,pV->Cosine) - _IQmpy(pV->Alpha,pV->Sine);
}

//IParking Ia,Ib
// Ialpha = Id*cos-Iq*sin
// Ibeta = Iq*cos+Id*sin
void  IPARK_Cale(p_IPARK pV)    
{
	pV->Alpha = _IQmpy(pV->Ds,pV->Cosine) - _IQmpy( pV->Qs,pV->Sine);
	pV->Beta  = _IQmpy(pV->Qs,pV->Cosine) + _IQmpy(pV->Ds,pV->Sine);
}

//===========================================================================
// No more.
//===========================================================================

