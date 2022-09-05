 //############################################################
// FILE:  PI_Cale.c
// Created on: 2017��1��4��
// Author: XQ
// summary: PI_Cale
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

#include "PI_Cale.h"

extern  PI_Control   pi_spd ;
extern  PI_Control   pi_id  ;
extern  PI_Control   pi_iq  ;


void  PI_Controller(p_PI_Control  pV)
{
    /* proportional term */
	pV->up = pV->Ref - pV->Fbk;

	/* integral term */
	pV->ui = (pV->Out == pV->v1)?(_IQmpy(pV->Ki, pV->up)+ pV->i1) : pV->i1;
	pV->i1 = pV->ui;

	/* control output */
	pV->v1 = _IQmpy(pV->Kp, (pV->up )) + pV->ui;	 
	pV->Out=IQsat( pV->v1, pV->Umax,  pV->Umin);
}

void  PI_Pare_init(void )
{
  pi_spd.Kp=18000;     // _ 
  pi_spd.Ki=260;  //    T* ��·���� /0.2
  pi_spd.Umax =2000;  //  
  pi_spd.Umin =0;

  pi_id.Kp=22;   // 
  pi_id.Ki=880;     // 
  pi_id.Umax =5000;//  
  pi_id.Umin =-5000;    // 

  pi_iq.Kp=2680  ;
  pi_iq.Ki=236 ;
  pi_iq.Umax =30000 ;
  pi_iq.Umin =0 ;
 }

//===========================================================================
// No more.
//===========================================================================

