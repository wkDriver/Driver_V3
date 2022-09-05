//############################################################
// FILE: VF_angle.c
// Created on: 2017��1��29��
// Author: XQ
// summary:  VF_angle
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

#include "VF_angle.h"
#include "PI_Cale.h"
#include "Timer.h"
#include "Task_function.h"
#include "Tim1_PWM.h"
#include "BEF_Hall.h"

extern   TaskTime    TaskTimePare;
extern   PI_Control   pi_spd ;
extern   VF_start   VF_startPare;
extern   logic  logicContr;
extern   uint16_t  DUTY;

 
void  VF_start_init(void )
{
  //VF_AnglePare.BASE_FREQ*T _IQ(0.02);  12500/VF_AnglePare.BASE_FREQ=50
	VF_startPare.VF_num[0]=5;   
	VF_startPare.VF_num[1]=1;  
	VF_startPare.VF_num[2]=3;  
	VF_startPare.VF_num[3]=2;   
	VF_startPare.VF_num[4]=6;   
	VF_startPare.VF_num[5]=4;   
	VF_startPare.initial_state=4;
	VF_startPare.Freq_T_Ref=25; // 15*2ms=30ms һ��״̬  180 msһ�������� 4 �Լ�  720ms/R 90 RPM
	VF_startPare.OldVF_State=0;
	VF_startPare.VF_state=0;

}
void VF_start_control(void)
{
	 if( logicContr.Start_order==1)   //��������1����λ�� 4   25*2ms=50ms
	{
		VF_startPare.VF_state=VF_startPare.initial_state;
		VF_startPare.Voilage_Ref=560;
	    VF_startPare.Freq_T_Ref--;
	    if( VF_startPare.Freq_T_Ref==0)
		{
	    	VF_startPare.Freq_T_Ref=20;
			  VF_startPare.VF_Count=VF_startPare.Freq_T_Ref;
	    	VF_startPare.Voilage_Ref=480;
	    	logicContr.Start_order=2;
		}
	}

	  if (logicContr.Start_order==2 ) //��������2�������̶�����˳��(VF����)
	{
	  VF_startPare.VF_Count--;
		if( VF_startPare.VF_Count==0)		
     {
			VF_startPare.VF_Count=VF_startPare.Freq_T_Ref;
			VF_startPare.VF_state=VF_startPare.VF_num[VF_startPare.VF_huanxCount];
      VF_startPare.VF_huanxCount++;				 
		 if(VF_startPare.VF_huanxCount>5 )
			{	 	
    	VF_startPare.VF_huanxCount=0;
    	VF_startPare.Voilage_Ref+=30;   // ��ѹ����
			if( VF_startPare.Voilage_Ref>=1000  )
			VF_startPare.Voilage_Ref=1000;			 
    	VF_startPare.Freq_T_Ref--;
			VF_startPare.VF_Count=VF_startPare.Freq_T_Ref;
    	if( VF_startPare.Freq_T_Ref==1)
    	{
    	  logicContr.Start_order=3;  //�л���������3
    	 pi_spd.ui = VF_startPare.Voilage_Ref;
    	 VF_startPare.initial_state=4;
    	 VF_startPare.Freq_T_Ref=25;
			 VF_startPare.VF_Count=VF_startPare.Freq_T_Ref;
    	 VF_startPare.VF_huanxCount=0;
    	}
		  }
     }
	 }

   if( (logicContr.Start_order==1)||(logicContr.Start_order==2) )
      {	  
       DUTY = VF_startPare.Voilage_Ref;
    	  switch (VF_startPare.VF_state )
		      {
		    	   case  Hall_num1:     // 0x5
		    	     {
		    	    	if( logicContr.Run_mode==1)
		    	      MOS_Q63PWM();
		    	    	if( logicContr.Run_mode==2)
		    	    	MOS_Q54PWM();
		    	     }
		    	   break;
						 case  Hall_num2:      // 0x1
							{
							if( logicContr.Run_mode==1)
								MOS_Q32PWM();
							if( logicContr.Run_mode==2)
								MOS_Q41PWM();
							}
							break;
							case  Hall_num3:     //0x3
							{
								if( logicContr.Run_mode==1)
								MOS_Q25PWM();
								if( logicContr.Run_mode==2)
								MOS_Q16PWM();
							}
							break;
						 case Hall_num4:    // 0x2
							 {
								 if( logicContr.Run_mode==1)
								MOS_Q54PWM();
								 if( logicContr.Run_mode==2)
									MOS_Q63PWM();
								}
							break;
						 case Hall_num5:    // 0x6
							 {
								 if( logicContr.Run_mode==1)
								MOS_Q41PWM();
								 if( logicContr.Run_mode==2)
									MOS_Q32PWM();
							 }
							 break;
						 case Hall_num6:   // 0x4
								{
								if( logicContr.Run_mode==1)
									MOS_Q16PWM();
								if( logicContr.Run_mode==2)
									MOS_Q25PWM();
							 }
						 break;
		     }
	VF_startPare.OldVF_State=VF_startPare.VF_state;
  }
}







//===========================================================================
// No more.
//===========================================================================
