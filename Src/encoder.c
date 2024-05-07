#include "tim.h"//包含tim头文件
#include "encoder.h"
int Tim5Encoder;//	上左
int Tim8Encoder;//  上右

int iTim5Encoder;//存放从TIM5定时器读出来的编码器脉冲		上左
int iTim8Encoder;//存放从TIM8定时器读出来的编码器脉冲		上右

int GetTim5Encoder(void)//获取TIM5定时器读出来的编码器脉冲
{
	iTim5Encoder = (short)(__HAL_TIM_GET_COUNTER(&htim5));//先读取脉冲数
	__HAL_TIM_SET_COUNTER(&htim5,0);//再计数器清零
	return iTim5Encoder;//返回脉冲数
}

int GetTim8Encoder(void)//获取TIM8定时器读出来的编码器脉冲
{
	iTim8Encoder = (short)(__HAL_TIM_GET_COUNTER(&htim8));//先读取脉冲数
	__HAL_TIM_SET_COUNTER(&htim8,0);//再计数器清零
	return iTim8Encoder;//返回脉冲数
}




/************************************
函数名:SetMotorVoltageAndDirection()
重要转换的常量：int Tem3Encoder_R;  
								int Tem2Encoder_L;
作用：将反转的数据转换为正数。再通过PID
传进占空比调节。因为占空比只能是正数
************************************/
void SetMotorVoltageAndDirection_SL(int nMotorPwm)//设置电机电压和方向
{
	
	if(nMotorPwm < 0)//反转
	{
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_RESET);//初始化BIN1引脚为低电平
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_SET);//初始化BIN2引脚为高电平
		nMotorPwm = (-nMotorPwm);//如果计算值是负值，先取负得正，因为PWM寄存器只能是正值
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, nMotorPwm);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_RESET);//初始化BIN1引脚为低电平
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_SET);//初始化BIN2引脚为高电平
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, nMotorPwm);
	}

}

void SetMotorVoltageAndDirection_SR(int nMotorPwm)//设置电机电压和方向
{
	
	if(nMotorPwm < 0)//反转
	{
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_SET);//初始化BIN1引脚为低电平
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_RESET);//初始化BIN2引脚为高电
		nMotorPwm = (-nMotorPwm);//如果计算值是负值，先取负得正，因为PWM寄存器只能是正值
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, nMotorPwm);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_SET);//初始化BIN1引脚为低电平
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_RESET);//初始化BIN2引脚为高电?
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, nMotorPwm);
	}

}
//函数名：ALL_Encoder();
//作用：对编码器函数的整合

//**************************************************************/
void ALL_Encoder()
{
//		Tim1Encoder=GetTim1Encoder();
//		Tim4Encoder=GetTim4Encoder();
		Tim5Encoder=-GetTim5Encoder();
		Tim8Encoder=GetTim8Encoder();
}
