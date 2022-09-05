//############################################################
// FILE: BEF_Hall.c
// Created on: 2017��1��18��
// Author: XQ
// summary: ThreeHall
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

#include "BEF_Hall.h"
#include "Tim1_PWM.h"
#include "Task_function.h"

extern  Hall   BEF_ThreeCAP;
extern  logic   logicContr;

  uint16_t   BEFHallK1=355; 		//Offset filter coefficient K1: 0.05/(T+0.05);
  uint16_t   BEFHallK2=669 ;  	//Offset filter coefficient K2: T/(T+0.05);
 
void  BEF_ThreeCAPPara_init(void )
{
   BEF_ThreeCAP.Poles=4;
	 BEF_ThreeCAP.speed_coeff= 65536/BEF_ThreeCAP.Poles; // 2�������һ�νǶȲ�ֵ 1000/2ms=500   =7500
	
}


void  BEFHall_huanxkz(void)  // һ��PWM����ִ��һ��
{
	   if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)==1) 
     BEF_ThreeCAP.HallUVW[0]=1;
			
						 else
						 BEF_ThreeCAP.HallUVW[0]=0; 
						 if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3)==1) 
						 BEF_ThreeCAP.HallUVW[1]=1;
		 else
		 BEF_ThreeCAP.HallUVW[1]=0; 
		 if (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)==1) 
     BEF_ThreeCAP.HallUVW[2]=1;
		  else
		 BEF_ThreeCAP.HallUVW[2]=0;  
	  BEF_ThreeCAP.Hall_State = BEF_ThreeCAP.HallUVW[0] +(BEF_ThreeCAP.HallUVW[1]<<1) +(BEF_ThreeCAP.HallUVW[2]<<2);
   if(( logicContr.drive_car==1)&&(logicContr.Start_order==3 ))
 {
  if ( BEF_ThreeCAP.Hall_State!=BEF_ThreeCAP.OldHall_State )
    {     
	if(  logicContr.Run_mode==2 )    
 		 {
    	switch (BEF_ThreeCAP.Hall_State )
	      {
	     	 case  BEFCAP_numZ1 :   // 0x3
	    	      MOS_Q63PWM();
	    	      break;
	    	 case BEFCAP_numZ2:   //0x2
	    	      MOS_Q32PWM();
	    	  break;
	    	  case BEFCAP_numZ3:  // 0x6
	    	      MOS_Q25PWM();
	    	      break;
	    	  case BEFCAP_numZ4:  //0x4
	    	      MOS_Q54PWM();
	    	      break;
	    	  case BEFCAP_numZ5 :   //   0x5
	    	      MOS_Q41PWM();
	    	       break;
	    	  case BEFCAP_numZ6:   // 0x1
	    	       MOS_Q16PWM();
	    	     break;
               default:
	    	  	  {
	    	  	   //Stop_Motor();
	    	  	    BEF_ThreeCAP.Speed_RPM=0;
	    	  	   }
	    	       break;
	    	 }
      }
      else if ( logicContr.Run_mode==1 )
      {
    	switch (BEF_ThreeCAP.Hall_State )
    	  {
								case  BEFCAP_numF1 :   // 0x3
										MOS_Q54PWM();
											break;
								case BEFCAP_numF2:   //0x2
										MOS_Q41PWM();
									break;
								case BEFCAP_numF3:  // 0x6
										MOS_Q16PWM();
											break;
								case BEFCAP_numF4:  //0x4
										MOS_Q63PWM();
											break;
								case BEFCAP_numF5 :   //   0x5
										MOS_Q32PWM();
											 break;
								case BEFCAP_numF6:   // 0x1
										MOS_Q25PWM();
										 break;
									default:
    		    	  {
    		    	  	 //Stop_Motor();
    		    	  	 BEF_ThreeCAP.Speed_RPM=0;
    		    	  }
    		    	  break;
    		   }
         } 
    //����ת�٣����ݻ�������֮���ʱ�� */				 
		  BEF_ThreeCAP.Speed_countFitter= _IQ10mpy(BEFHallK2, BEF_ThreeCAP.Speed_countFitter)+_IQ10mpy(BEFHallK1,  BEF_ThreeCAP.Speed_count);								  	 
      BEF_ThreeCAP.Speed_RPM = BEF_ThreeCAP.speed_coeff/BEF_ThreeCAP.Speed_countFitter;
		  BEF_ThreeCAP.Speed_RPMF= _IQ10mpy(BEFHallK2, BEF_ThreeCAP.Speed_RPMF)+_IQ10mpy(BEFHallK1,  BEF_ThreeCAP.Speed_RPM);	
  		BEF_ThreeCAP.Speed_count= 0;        
    }

     else  if ( BEF_ThreeCAP.Hall_State==BEF_ThreeCAP.OldHall_State )
     {
    	 BEF_ThreeCAP.Speed_count++;   
       if( BEF_ThreeCAP.Speed_count>=2000 )
    	 {
    		 BEF_ThreeCAP.Speed_count=0;
    		 BEF_ThreeCAP.Speed_RPMF= 0 ;
				 //	Stop_Motor();
    		 BEF_ThreeCAP.step_angleFitter=0;	
				 BEF_ThreeCAP.Move_State=0;		
      
       }
     }
	 }		 
   BEF_ThreeCAP.OldHall_State=BEF_ThreeCAP.Hall_State ;
}

 
//===========================================================================
// No more.
//===========================================================================
