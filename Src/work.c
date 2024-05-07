#include "work.h"
#include "tim.h"
#include "bsp_uasrt.h"
#include "pid.h"
#include "jy901.h"
#include "oled.h"
#include "stdio.h"
uint32_t yuntai_uwTick;
_Bool yuntai_flag =0;

uint32_t fine_uwTick;

uint32_t numbwr_count=1500;
uint32_t key_uwTick;
_Bool shut_flag =0;
_Bool shut_flag2 =0;
_Bool yuntai_state=0;
uint32_t shut_uwTick=0;
extern struct MV mv;
extern struct Angle angles;
extern struct Angle_y angles_y;
extern struct MV_3 mv3;
int c=0;
int d=0;

uint8_t shut_stste=0;
uint8_t shut_stste2=0;
uint8_t fine_zhuan_stste=1;
////MV
//int MOTO_X;
//int MOTO_Y=1500;


//shou
int MOTO_X=1500;
int MOTO_Y=1500;


//led
uint8_t Led_Disp_String[22];
uint32_t uwTick_Lcd_Set_Point=0;
uint8_t mv_count=0;













//电赛
float text_pwm_x=1500;
float text_pwm_y=1500;
float x_aim=1500;
float	y_aim =1500;
uint32_t uwTick_Set_Point;
//基础1-1
uint8_t T1_state=0;

uint32_t T1_uwTick;
_Bool T1_flag=0;
//基础题3-4.
int pwm_3_x;
int pwm_2_x;
int pwm_1_x;
int pwm_4_x;

int pwm_3_y;
int pwm_2_y;
int pwm_1_y;
int pwm_4_y;

float pwmx_step;
float pwmy_step;

void fine(void)
{
	 
	
	if((uwTick-fine_uwTick)<9) return; //2秒半圈，2秒，222个脉冲
	fine_uwTick=uwTick;
	
	if(fine_zhuan_stste==1)
	{
		
		numbwr_count++;
		if((numbwr_count)<=1722)
		{
			
			 __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, numbwr_count);
			
		}
		else
		{
			fine_zhuan_stste=2;
		}
	}
	if(fine_zhuan_stste==2)
	{
		numbwr_count--;
		if((numbwr_count)>=1500)
		{
			
			 __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, numbwr_count);
			
		}
		else
		{
			fine_zhuan_stste=3;
		}
	}
	if(fine_zhuan_stste==3)
	{
		numbwr_count--;
		if((numbwr_count)>=1277)
		{
			
			 __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, numbwr_count);
			
		}
		else
		{
			fine_zhuan_stste=4;
		}
	}
	
	if(fine_zhuan_stste==4)
	{
		numbwr_count++;
		if((numbwr_count)<=1500)
		{
			
			 __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, numbwr_count);
			
		}
		else
		{
			fine_zhuan_stste=1;
		}
	}
}

void yuntai_follow()
{
	if(mv.flag==0)
	{
//	 fine();		 
	}
	else if(mv.flag==1)
	 {
		 if(yuntai_state==0)
		 {
			 MOTO_X=numbwr_count;
			 yuntai_state=1;
		 }
		 if(yuntai_state==1)
		 {
			
			 if(yuntai_flag==0)
			 {
				 
				 yuntai_flag=1;
			 }
			 if(yuntai_flag==1)
			 {
				 
				 {
					  yuntai_flag=0;
			      MOTO_X=MOTO_X+Balance_angle(mv.MV_error);
					  MOTO_Y=MOTO_Y+Balance_angle_y(mv.MV_error_y);
			      xianfu_x();
					  xianfu_y();
				 }
			 }
			  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, MOTO_X);
			  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, MOTO_Y);
		 }
	 }
}

void handle_yuntai(void)
{

	
	MOTO_X=1500+JY901_data.angle.angle[2]*7.407;
	MOTO_Y=1500+JY901_data.angle.angle[0]*3.7;
	xianfu_x();
	xianfu_y();
	
//	 __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, MOTO_X);
	 __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, MOTO_Y);
	
}






void xianfu_x(void)
{
	if(MOTO_X<=MOTOX_1)
	{
		MOTO_X=MOTOX_1;
	}
	if(MOTO_X>=MOTOX_2)
	{
		MOTO_X=MOTOX_1;
	}
}

void xianfu_y(void)
{
	if(MOTO_Y<=MOTOX_3)
	{
		MOTO_Y=MOTOX_3;
	}
	if(MOTO_Y>=MOTOX_4)
	{
		MOTO_Y=MOTOX_4;
	}
}



void Lcd_Proc(void)
{

//	if((uwTick-uwTick_Lcd_Set_Point)<200) return ;
//	uwTick_Lcd_Set_Point=uwTick;
//	sprintf((char*)Led_Disp_String,"%d",mv_count);
//	OLED_ShowString(0,2,Led_Disp_String,16);
//	sprintf((char*)Led_Disp_String,"%d,%d,%d,%d,%d",mv3.g_1,mv3.g_2,mv3.g_3,mv3.g_4,mv3.g_5);
//	OLED_ShowString(0,6,Led_Disp_String,16);
//	sprintf((char*)Led_Disp_String,"Yoll:%5.1f",JY901_data.angle.angle[2]);
//	OLED_ShowString(0,4,Led_Disp_String,16);
}



//按键
void key_proc(void)
{
	if((uwTick-uwTick_Set_Point)<200) return ;
	uwTick_Set_Point=uwTick;
	
	if(sw3==0)
	{
		T1_state=1;
	}
	if(basic_key_34==1)
	{
		T1_state=6;
	}
}

void basic_1(void)
{
//	if(T1_state==0)
//	{
//		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 1500);
//	  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 1441);

//	}	
//	if(T1_state==1)
//	{
//		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 1400);
//	  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 1527);
//		if(T1_flag==0)
//		{
//			T1_uwTick=uwTick;
//			T1_flag=1;
//		}
//		if(T1_flag==1)
//		{
//			if((uwTick-T1_uwTick)>1000)
//			{
//				T1_flag=0;
//				T1_state=2;
//			}
//		}

//	}	
//	else if(T1_state==2)
//	{
//		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 1400);
//	  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 1355);
//		if(T1_flag==0)
//		{
//			T1_uwTick=uwTick;
//			T1_flag=1;
//		}
//		if(T1_flag==1)
//		{
//			if((uwTick-T1_uwTick)>1000)
//			{
//				T1_flag=0;
//				T1_state=3;
//			}
//		}

//	}	
//	else if(T1_state==3)
//	{
//		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 1589);
//	  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 1355);
//		if(T1_flag==0)
//		{
//			T1_uwTick=uwTick;
//			T1_flag=1;
//		}
//		if(T1_flag==1)
//		{
//			if((uwTick-T1_uwTick)>1000)
//			{
//				T1_flag=0;
//				T1_state=4;
//			}
//		}

//	}	
//	else if(T1_state==4)
//	{
//		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 1580);
//	  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 1526);
//		if(T1_flag==0)
//		{
//			T1_uwTick=uwTick;
//			T1_flag=1;
//		}
//		if(T1_flag==1)
//		{
//			if((uwTick-T1_uwTick)>1000)
//			{
//				T1_flag=0;
//				T1_state=5;
//			}
//		}

//	}	
//	
//	else if(T1_state==5)
//	{
//		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 1400);
//	  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 1527);
//		if(T1_flag==0)
//		{
//			T1_uwTick=uwTick;
//			T1_flag=1;
//		}
//		if(T1_flag==1)
//		{
//			if((uwTick-T1_uwTick)>1000)
//			{
//				T1_flag=0;
//				T1_state=0;
//			}
//		}

//	}	
  if(x_aim>text_pwm_x)
	{
		x_aim-=0.2;
	}	
  if(x_aim<text_pwm_x)
	{
		x_aim+=0.2;
	}	
	
	if(y_aim>text_pwm_y)
	{
		y_aim-=0.2;
	}	
  if(y_aim<text_pwm_y)
	{
		y_aim+=0.2;
	}	
  
	 
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, x_aim);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, y_aim);
}

void basic_34(void)
{
	
	if(T1_state==0)
	{
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 1500);
	  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 1441);

	}	
	if(T1_state==6)
	{
		pwm_3_x=(mv3.g_3_x*-2.28+1676.8);
		pwm_2_x=(mv3.g_2_x*-2.28+1676.8);
		pwm_1_x=(mv3.g_1_x*-2.28+1678.8);
		pwm_4_x=(mv3.g_4_x*-2.28+1678.8);
		
		pwm_3_y=(mv3.g_3_y*-2.273+1580.17);
		pwm_2_y=(mv3.g_2_y*-2.273+1580.17);
		pwm_1_y=(mv3.g_1_y*-2.273+1580.17);
		pwm_4_y=(mv3.g_4_y*-2.273+1580.17);
		
		
		
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, pwm_3_x);
	  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, pwm_3_y);
		if(T1_flag==0)
		{
			T1_uwTick=uwTick;
			T1_flag=1;
		}
		if(T1_flag==1)
		{
			if((uwTick-T1_uwTick)>1000)
			{
				T1_flag=0;
				T1_state=7;
			}
		}

	}	
	else if(T1_state==7)
	{
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, pwm_2_x);
	  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, pwm_2_y);
		if(T1_flag==0)
		{
			T1_uwTick=uwTick;
			T1_flag=1;
		}
		if(T1_flag==1)
		{
			if((uwTick-T1_uwTick)>1000)
			{
				T1_flag=0;
				T1_state=8;
			}
		}

	}	
	else if(T1_state==8)
	{
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, pwm_1_x);
	  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, pwm_1_y);
		if(T1_flag==0)
		{
			T1_uwTick=uwTick;
			T1_flag=1;
		}
		if(T1_flag==1)
		{
			if((uwTick-T1_uwTick)>1000)
			{
				T1_flag=0;
				T1_state=9;
			}
		}

	}	
	else if(T1_state==9)
	{
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, pwm_4_x);
	  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, pwm_4_y);
		if(T1_flag==0)
		{
			T1_uwTick=uwTick;
			T1_flag=1;
		}
		if(T1_flag==1)
		{
			if((uwTick-T1_uwTick)>1000)
			{
				T1_flag=0;
				T1_state=10;
			}
		}

	}	
	
	else if(T1_state==10)
	{
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, pwm_3_x);
	  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, pwm_3_y);
		if(T1_flag==0)
		{
			T1_uwTick=uwTick;
			T1_flag=1;
		}
		if(T1_flag==1)
		{
			if((uwTick-T1_uwTick)>1000)
			{
				T1_flag=0;
				T1_state=0;
			}
		}

	}	
	
//  	if(T1_state==6)
//		{
//			pwm_3_x=(mv3.g_3_x*-2.28+1678.8);
//			pwm_2_x=(mv3.g_2_x*-2.28+1678.8);
//			pwm_1_x=(mv3.g_1_x*-2.28+1678.8);
//			pwm_4_x=(mv3.g_4_x*-2.28+1678.8);
//			
//			pwm_3_y=(mv3.g_3_y*-2.27+1580.17);
//			pwm_2_y=(mv3.g_2_y*-2.27+1580.17);
//			pwm_1_y=(mv3.g_1_y*-2.27+1580.17);
//			pwm_4_y=(mv3.g_4_y*-2.27+1580.17);
//			
//			if(T1_flag==0)
//		  {
//			 T1_uwTick=uwTick;
//			 T1_flag=1;
//	  	}
//		  if(T1_flag==1)
//			{
//				if((uwTick-T1_uwTick)>1000)
//				{
//					T1_flag=0;
//					T1_state=7;
//					pwmx_step=((text_pwm_x-pwm_3_x)/60);
//					pwmy_step=((text_pwm_y-pwm_3_y)/60);
//				}
//			}
//		}
//		if(T1_state==7)
//		{
//			  text_pwm_x-=pwmx_step;
//        text_pwm_y-=pwmy_step;

//			  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, text_pwm_x);
//	      __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, text_pwm_y);
//				if(((text_pwm_y-pwm_3_y)<=0.2)&&(text_pwm_y-pwm_3_y)>=-0.2)
//				{
//					
//					 T1_state=8;
//					pwmx_step=((text_pwm_x-pwm_2_x)/60);
//					pwmy_step=((text_pwm_y-pwm_2_y)/60);
//				}
//			  
//		 
//		}
//		if(T1_state==8)
//			{
//				
//				if(T1_flag==0)
//		    {
//					T1_uwTick=uwTick;
//			    T1_flag=1;
//				}	
//				if(T1_flag==1)
//				{
//					if((uwTick-T1_uwTick)>1000)
//					{
//						T1_flag=0;
//						T1_state=9;
//						
//					}
//				}	
//			 
//	  	}
//		  
//				
//		
//		
//		if(T1_state==9)
//		{
//			text_pwm_x-=pwmx_step;
//        text_pwm_y-=pwmy_step;
//			
//			  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, text_pwm_x);
//	      __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, text_pwm_y);
//				if(((text_pwm_y-pwm_2_y)<=0.2&&(text_pwm_y-pwm_2_y)>=-0.2))
//				{
//					 T1_state=10;
//					 pwmx_step=((text_pwm_x-pwm_1_x)/60);
//					pwmy_step=((text_pwm_y-pwm_1_y)/60);
//				}
//			  
//		  
//		}
//		if(T1_state==10)
//			{
//				
//				if(T1_flag==0)
//		    {
//					T1_uwTick=uwTick;
//			    T1_flag=1;
//				}	
//				if(T1_flag==1)
//				{
//					if((uwTick-T1_uwTick)>1000)
//					{
//						T1_flag=0;
//						T1_state=11;
//						
//					}
//				}	
//			 
//	  	}
//		
//		
//		if(T1_state==11)
//		{
//			text_pwm_x-=pwmx_step;
//        text_pwm_y-=pwmy_step;
//			  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, text_pwm_x);
//	      __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, text_pwm_y);
//				if(((text_pwm_y-pwm_1_y)<=0.2)&&(text_pwm_y-pwm_1_y)>=-0.2)
//				{
//					 T1_state=12;
//					pwmx_step=((text_pwm_x-pwm_4_x)/60);
//					pwmy_step=((text_pwm_y-pwm_4_y)/60);
//				}
//			  
//		  
//			
//		}
//		if(T1_state==12)
//			{
//				
//				if(T1_flag==0)
//		    {
//					T1_uwTick=uwTick;
//			    T1_flag=1;
//				}	
//				if(T1_flag==1)
//				{
//					if((uwTick-T1_uwTick)>1000)
//					{
//						T1_flag=0;
//						T1_state=13;
//						
//					}
//				}	
//			 
//	  	}
//		if(T1_state==13)
//		{
//			text_pwm_x-=pwmx_step;
//        text_pwm_y-=pwmy_step;
//			  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, text_pwm_x);
//	      __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, text_pwm_y);
//				if(((text_pwm_y-pwm_4_y)<=0.2)&&(text_pwm_y-pwm_4_y)>=-0.2)
//				{
//					 T1_state=14;
//					pwmx_step=((text_pwm_x-pwm_3_x)/60);
//					pwmy_step=((text_pwm_y-pwm_3_y)/60);
//				}
//			  
//		  
//			
//		}
//		if(T1_state==14)
//			{
//				
//				if(T1_flag==0)
//		    {
//					T1_uwTick=uwTick;
//			    T1_flag=1;
//				}	
//				if(T1_flag==1)
//				{
//					if((uwTick-T1_uwTick)>1000)
//					{
//						T1_flag=0;
//						T1_state=15;
//						
//					}
//				}	
//			 
//	  	}
//		if(T1_state==15)
//		{
//			text_pwm_x-=pwmx_step;
//        text_pwm_y-=pwmy_step;
//			  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, text_pwm_x);
//	      __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, text_pwm_y);
//				if(((text_pwm_y-pwm_3_y)<=0.2)&&(text_pwm_y-pwm_3_y)>=-0.2)
//				{
//					 T1_state=0;
//				
//				}
//			  
//		  
//			
//		}
//		
//		
//	
		
}






