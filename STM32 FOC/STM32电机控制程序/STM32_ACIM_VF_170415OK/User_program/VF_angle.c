//############################################################
// FILE: VF_angle.h
// Created on: 2017��1��15��
// Author: XQ
// summary: VF_angle
// VF�Ƕ�
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
#include "VF_angle.h"
#include "Tim1_PWM.h"
#include "Timer.h"

extern   VF_Angle   VF_AnglePare;
extern   TaskTime   TaskTimePare;  
extern   int32_t    PWM_udq[3];
extern   uint16_t   Speed_Ref;
uint16_t VFp=25; // ��ѹ��Ƶ�ʵı��� ����ѹ����0---60000����

void  VFAngle_init(void )
{
 VF_AnglePare.BASE_FREQ=135;   // 2000RPM  = n=60f/P= 135*60/4   ���������135      0---85MAX_angele
 VF_AnglePare.step_anglemax= (VF_AnglePare.BASE_FREQ<<16)/PWM_FREQ; //12500/VF_AnglePare.BASE_FREQ=92.5  1/92.5*2^16 IQ��ʽ
 VF_AnglePare.step_Speed=3;  //Ƶ�ʵĻ��������ٶ�=3 
}

void VFAngle_cale(void)
{
   VF_AnglePare.Angle_theta+=VF_AnglePare.step_angle; //�Ƕȸ��ݲ����Ƕ��ۼӳ����ǲ�
   if( VF_AnglePare.Angle_theta>65536) // ���ƽǶ� 0--360 2pi    0---65536  
	 VF_AnglePare.Angle_theta-=65536;    //  
   else if( VF_AnglePare.Angle_theta<0)
   VF_AnglePare.Angle_theta+=65536; 
}

void VF_start_control(void)
{
    //VF �����ѹ��Ƶ��	
		VF_AnglePare.SpeedRef= Speed_Ref ; //  
		VF_AnglePare.VF_Vq= VFp*VF_AnglePare.Speed_target ; // VFp��ѹ��Ƶ�ʱ�ֵ
	  if( VF_AnglePare.VF_Vq>=32000   )
    VF_AnglePare.VF_Vq=32000 ;
		
  	VF_AnglePare.Speederror= VF_AnglePare.SpeedRef-VF_AnglePare.Speed_target;

	    if(Abs(VF_AnglePare.Speederror)>= VF_AnglePare.step_Speed ) // VF ��б�ʣ�ת�ٵ���������
	     {
			  if ( VF_AnglePare.SpeedRef>VF_AnglePare.Speed_target  )
			  VF_AnglePare.Speed_target+= VF_AnglePare.step_Speed ;
			  else if	( VF_AnglePare.SpeedRef<VF_AnglePare.Speed_target)
			  VF_AnglePare.Speed_target-= VF_AnglePare.step_Speed ;
			  else  
			  VF_AnglePare.Speed_target=VF_AnglePare.SpeedRef;
	     }
       else
       {
        VF_AnglePare.Speed_target=VF_AnglePare.SpeedRef;  
       }
	  VF_AnglePare.step_angle= (VF_AnglePare.step_anglemax*VF_AnglePare.Speed_target)/(VF_AnglePare.BASE_FREQ*60/4) ;  //��ʵ���ٶ�/���ת�٣�*����ٶȵĲ����Ƕ� 771
}


//===========================================================================
// No more.
//===========================================================================
