#include "pid.h"
#include "encoder.h"
#include "jy901.h"

int g_n_S_LeftMotorOutput=0;//���ϵ�����
int g_n_S_RightMotorOutput=0;//���ϵ��


/************�ǶȻ�*************

	float KP_angle;
  float KD_angle;
  int balance_angle;
  float error;
  int back_pwm;
	**************/
float Last_Bias,D_Bias;//PID��ر���
float Last_Bias_y,D_Bias_y;	
//ɫ�����
//struct Angle angle={0.08,0.25,143,0,0};
//struct Angle_Y angle_y={0.05,0,91,0,0};
//�������
struct Angle angle={0.12,1,143,0,0};
struct Angle_Y angle_y={0.11,-1,91,0,0};


////������̨
//float Last_Bias_handx,D_Bias_handx;//PID��ر���
//float Last_Bias_handy,D_Bias_handy;	

//struct Hand_X hand_x={0,0,0,0,0};
//struct Hand_Y hand_y={0,0,0,0,0};

//�޷�
int PWM_MAX=800,PWM_MIN=-800;	// PWM�޷�����

//ת��
float yaw_err,yaw_err_difference,last_yaw_err;
float Turn_Kp=14;
float Turn_Kd=10;
float yaw_calcu;
int Turn_out; //ת�����
//�ٶȻ�
float fP_SL =3.8, fI_SL= 0.005;//����ֻ�õ�PI�������ɵ��������͸��ؾ���
//float fP_SR=0 ,fI_SR=0; //����ֻ�õ�PI�������ɵ��������͸��ؾ���
int sudu_Targe =0;
int Velocity_out;//�ٶ�?
int MOTO_L;
int MOTO_R;



//�����̨��
int Balance_angle(int angle_ADC)
{
	angle.error=angle.balance_angle-angle_ADC;
	D_Bias=angle.error-Last_Bias;
	angle.back_pwm=-angle.KP_angle*angle.error-angle.KD_angle*D_Bias;
	Last_Bias=angle.error;//������һ�ε�ƫ��
  return angle.back_pwm;
}

int Balance_angle_y(int angle_ADC)
{
	angle_y.error_y=angle_y.balance_angle_y-angle_ADC;
	D_Bias_y=angle_y.error_y-Last_Bias_y;
	angle_y.back_pwm_y=angle_y.KP_angle_y*angle_y.error_y-angle_y.KD_angle_y*D_Bias_y;
	

	Last_Bias_y=angle_y.error_y;//������һ�ε�ƫ��
  return angle_y.back_pwm_y;
}



//������̨��
//int Balance_angle_handx(int angle_ADC)
//{
//	hand_x.error_handx=hand_x.balance_angle_handx-angle_ADC;
//	D_Bias_handx=hand_x.error_handx-Last_Bias_handx;
//	hand_x.back_pwm_handx=-hand_x.KP_angle_handx*hand_x.error_handx+hand_x.KD_angle_handx*D_Bias_handx;
//	Last_Bias_handx=hand_x.error_handx;//������һ�ε�ƫ��
//  return hand_x.back_pwm_handx;
//}

//int Balance_angle_handy(int angle_ADC)
//{
//	hand_y.error_handy=hand_y.balance_angle_handy-angle_ADC;
//	D_Bias_handy=hand_y.error_handy-Last_Bias_handy;
//	hand_y.back_pwm_handy=hand_y.KP_angle_handy*hand_y.error_handy-hand_y.KD_angle_handy*D_Bias_handy;
//	

//	Last_Bias_handy=hand_y.error_handy;//������һ�ε�ƫ��
//  return hand_y.back_pwm_handy;
//}


/*****************  
ת�򻷣�����|��С��
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
�ٶȻ�PI��������Kp*Ek+Ki*Ek_S(Ek_S��ƫ��Ļ���)
******************/



int Velocity(int Target,int encoder_left,int encoder_right)
{
  // ����ɾ�̬�����������ھ�̬�洢����ʹ�ñ���������
  static int PWM_out,Encoder_Err,Encoder_S,EnC_Err_Lowout,EnC_Err_Lowout_last;
  float a=0.7;
  
  // 1.�����ٶ�ƫ��
  // ��ȥ���--�ҵ���⣺�ܹ����ٶ�Ϊ"0"�ĽǶȣ����ǻ�е��ֵ��
  Encoder_Err = ((encoder_left+encoder_right)+Target);
  // 2.���ٶ�ƫ����е�ͨ�˲�
  // low_out = (1-a)*Ek+a*low_out_last
  EnC_Err_Lowout = (1-a)*Encoder_Err + a*EnC_Err_Lowout_last; // ʹ�ò��θ���ƽ�����˳���Ƶ���ţ������ٶ�ͻ��
  EnC_Err_Lowout_last = EnC_Err_Lowout;   // ��ֹ�ٶȹ���Ӱ��ֱ��������������
  // 3.���ٶ�ƫ����ֳ�λ��
  Encoder_S+=EnC_Err_Lowout;
  // 4.�����޷�
  Encoder_S=Encoder_S>1000?1000:(Encoder_S<(-1000)?(-1000):Encoder_S);
  
  // 5.�ٶȻ��������
  PWM_out = fP_SL*EnC_Err_Lowout+fI_SL*Encoder_S;
  
  return PWM_out;
}

void new_multiply_pid(void)
{
	// 2.������ѹ��ջ������У���������������
			Velocity_out=Velocity(sudu_Targe,Tim5Encoder,Tim8Encoder); // �ٶȻ�
//      Vertical_out=Vertical(Velocity_out+Med_Angle,Roll,gyrox);			  // ֱ����
			Turn_out=yaw_PD_value(JY901_data.angle.angle[2]);	
	
	    MOTO_L = Velocity_out-Turn_out; // ����
      MOTO_R= Velocity_out+Turn_out; // �ҵ��
      Limit(&MOTO_L,&MOTO_R);     // PWM�޷�
      SetMotorVoltageAndDirection_SL(MOTO_L);       // ���ص������
			SetMotorVoltageAndDirection_SR(MOTO_R); 
}

//����޷�
void Limit(int *motoA,int *motoB)
{
	if(*motoA>PWM_MAX)*motoA=PWM_MAX;
	if(*motoA<PWM_MIN)*motoA=PWM_MIN;
	
	if(*motoB>PWM_MAX)*motoB=PWM_MAX;
	if(*motoB<PWM_MIN)*motoB=PWM_MIN;
}


///****************************************
//��������Machinery_all()
//���ã�ͨ��pid�������;
//****************************************/

//void Machinery_all(void)
//{
//	g_n_S_RightMotorOutput=yaw_PD_value(JY901_data.angle.angle[2]);
//	g_n_S_LeftMotorOutput=-g_n_S_RightMotorOutput;
//	Limit(&g_n_S_LeftMotorOutput,&g_n_S_RightMotorOutput);
//	SetMotorVoltageAndDirection_SR(g_n_S_RightMotorOutput);//���õ����ѹ�ͷ���
//	SetMotorVoltageAndDirection_SL(g_n_S_LeftMotorOutput);//���õ����ѹ�ͷ���
//}

