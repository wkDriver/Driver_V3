//############################################################
// FILE:  Svpwm_dq.c
// Created on: 2017��1��18��
// Author: XQ
// summary: Svpwm_dq
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

#include "Svpwm_dq.h"


void  SVPWM_Cale(p_SVPWM  pV)
{
  pV->tmp1= pV->Ubeta;   // �൱�ڶ��ྲֹ����--�����ྲֹ�任��Uabc
	pV->tmp2= _IQdiv2(pV->Ubeta) + _IQmpy(28377,pV->Ualpha); //0.866*32768=sqrt(3)/2*2^15
  pV->tmp3= pV->tmp2 - pV->tmp1;

	pV->VecSector=3;   // ���������ѹ���ż���ʸ������
	pV->VecSector=(pV->tmp2> 0)?( pV->VecSector-1):pV->VecSector;
	pV->VecSector=(pV->tmp3> 0)?( pV->VecSector-1):pV->VecSector;
	pV->VecSector=(pV->tmp1< 0)?(7-pV->VecSector) :pV->VecSector;

	 if  (pV->VecSector==1 || pV->VecSector==4)  // ����ʸ����������ʸ��ռ�ձ�Tabc
      {  
				pV->Ta= pV->tmp2;
      	pV->Tb= pV->tmp1-pV->tmp3;
      	pV->Tc=-pV->tmp2;
      }

   else if(pV->VecSector==2 || pV->VecSector==5)
      {  
				pV->Ta= pV->tmp3+pV->tmp2;
      	pV->Tb= pV->tmp1;
      	pV->Tc=-pV->tmp1;
      }

    else
      {   
				pV->Ta= pV->tmp3;
      	pV->Tb=-pV->tmp3;
      	pV->Tc=-(pV->tmp1+pV->tmp2);
      }
}

//===========================================================================
// No more.
//===========================================================================
