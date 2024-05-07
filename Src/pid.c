#include "pid.h"
#include "encoder.h"
#include "jy901.h"

int g_n_S_LeftMotorOutput=0;//左上电机输出
int g_n_S_RightMotorOutput=0;//右上电机


/************角度环*************

	float KP_angle;
  float KD_angle;
  int balance_angle;
  float error;
  int back_pwm;
	**************/
float Last_Bias,D_Bias;//PID相关变量
float Last_Bias_y,D_Bias_y;	
//色块参数
//struct Angle angle={0.08,0.25,143,0,0};
//struct Angle_Y angle_y={0.05,0,91,0,0};
//激光参数
struct Angle angle={0.12,1,143,0,0};
struct Angle_Y angle_y={0.11,-1,91,0,0};


////手势云台
//float Last_Bias_handx,D_Bias_handx;//PID相关变量
//float Last_Bias_handy,D_Bias_handy;	

//struct Hand_X hand_x={0,0,0,0,0};
//struct Hand_Y hand_y={0,0,0,0,0};

//限幅
int PWM_MAX=800,PWM_MIN=-800;	// PWM限幅变量

//转向环
float yaw_err,yaw_err_difference,last_yaw_err;
float Turn_Kp=14;
float Turn_Kd=10;
float yaw_calcu;
int Turn_out; //转向环输出
//速度环
float fP_SL =3.8, fI_SL= 0.005;//这里只用到PI，参数由电机的种类和负载决定
//float fP_SR=0 ,fI_SR=0; //这里只用到PI，参数由电机的种类和负载决定
int sudu_Targe =0;
int Velocity_out;//速度?
int MOTO_L;
int MOTO_R;



//舵机云台环
int Balance_angle(int angle_ADC)
{
	angle.error=angle.balance_angle-angle_ADC;
	D_Bias=angle.error-Last_Bias;
	angle.back_pwm=-angle.KP_angle*angle.error-angle.KD_angle*D_Bias;
	Last_Bias=angle.error;//保持上一次的偏差
  return angle.back_pwm;
}

int Balance_angle_y(int angle_ADC)
{
	angle_y.error_y=angle_y.balance_angle_y-angle_ADC;
	D_Bias_y=angle_y.error_y-Last_Bias_y;
	angle_y.back_pwm_y=angle_y.KP_angle_y*angle_y.error_y-angle_y.KD_angle_y*D_Bias_y;
	

	Last_Bias_y=angle_y.error_y;//保持上一次的偏差
  return angle_y.back_pwm_y;
}



//手势云台环
//int Balance_angle_handx(int angle_ADC)
//{
//	hand_x.error_handx=hand_x.balance_angle_handx-angle_ADC;
//	D_Bias_handx=hand_x.error_handx-Last_Bias_handx;
//	hand_x.back_pwm_handx=-hand_x.KP_angle_handx*hand_x.error_handx+hand_x.KD_angle_handx*D_Bias_handx;
//	Last_Bias_handx=hand_x.error_handx;//保持上一次的偏差
//  return hand_x.back_pwm_handx;
//}

//int Balance_angle_handy(int angle_ADC)
//{
//	hand_y.error_handy=hand_y.balance_angle_handy-angle_ADC;
//	D_Bias_handy=hand_y.error_handy-Last_Bias_handy;
//	hand_y.back_pwm_handy=hand_y.KP_angle_handy*hand_y.error_handy-hand_y.KD_angle_handy*D_Bias_handy;
//	

//	Last_Bias_handy=hand_y.error_handy;//保持上一次的偏差
//  return hand_y.back_pwm_handy;
//}


/*****************  
转向环：作者|：小黑
******************/
int yaw_PD_value(float yaw_measure)
{
	yaw_err = yaw_calcu-yaw_measure;
	if(yaw_err > 180) yaw_err = yaw_err - 360.0;
	else if(yaw_err < -180) yaw_err = 360.0 + yaw_err;
	
	yaw_err_difference=yaw_err-last_yaw_err;
	last_yaw_err=yaw_err;
	
	return Turn_Kp*yaw_err+Turn_Kd*yaw_err_difference;
	
}



/*****************  
速度环PI控制器：Kp*Ek+Ki*Ek_S(Ek_S：偏差的积分)
******************/



int Velocity(int Target,int encoder_left,int encoder_right)
{
  // 定义成静态变量，保存在静态存储器，使得变量不丢掉
  static int PWM_out,Encoder_Err,Encoder_S,EnC_Err_Lowout,EnC_Err_Lowout_last;
  float a=0.7;
  
  // 1.计算速度偏差
  // 舍去误差--我的理解：能够让速度为"0"的角度，就是机械中值。
  Encoder_Err = ((encoder_left+encoder_right)+Target);
  // 2.对速度偏差进行低通滤波
  // low_out = (1-a)*Ek+a*low_out_last
  EnC_Err_Lowout = (1-a)*Encoder_Err + a*EnC_Err_Lowout_last; // 使得波形更加平滑，滤除高频干扰，放置速度突变
  EnC_Err_Lowout_last = EnC_Err_Lowout;   // 防止速度过大影响直立环的正常工作
  // 3.对速度偏差积分出位移
  Encoder_S+=EnC_Err_Lowout;
  // 4.积分限幅
  Encoder_S=Encoder_S>1000?1000:(Encoder_S<(-1000)?(-1000):Encoder_S);
  
  // 5.速度环控制输出
  PWM_out = fP_SL*EnC_Err_Lowout+fI_SL*Encoder_S;
  
  return PWM_out;
}

void new_multiply_pid(void)
{
	// 2.将数据压入闭环控制中，计算出控制输出量
			Velocity_out=Velocity(sudu_Targe,Tim5Encoder,Tim8Encoder); // 速度环
//      Vertical_out=Vertical(Velocity_out+Med_Angle,Roll,gyrox);			  // 直立环
			Turn_out=yaw_PD_value(JY901_data.angle.angle[2]);	
	
	    MOTO_L = Velocity_out-Turn_out; // 左电机
      MOTO_R= Velocity_out+Turn_out; // 右电机
      Limit(&MOTO_L,&MOTO_R);     // PWM限幅
      SetMotorVoltageAndDirection_SL(MOTO_L);       // 加载到电机上
			SetMotorVoltageAndDirection_SR(MOTO_R); 
}

//输出限幅
void Limit(int *motoA,int *motoB)
{
	if(*motoA>PWM_MAX)*motoA=PWM_MAX;
	if(*motoA<PWM_MIN)*motoA=PWM_MIN;
	
	if(*motoB>PWM_MAX)*motoB=PWM_MAX;
	if(*motoB<PWM_MIN)*motoB=PWM_MIN;
}


///****************************************
//函数名：Machinery_all()
//作用：通过pid驱动电机;
//****************************************/

//void Machinery_all(void)
//{
//	g_n_S_RightMotorOutput=yaw_PD_value(JY901_data.angle.angle[2]);
//	g_n_S_LeftMotorOutput=-g_n_S_RightMotorOutput;
//	Limit(&g_n_S_LeftMotorOutput,&g_n_S_RightMotorOutput);
//	SetMotorVoltageAndDirection_SR(g_n_S_RightMotorOutput);//设置电机电压和方向
//	SetMotorVoltageAndDirection_SL(g_n_S_LeftMotorOutput);//设置电机电压和方向
//}

