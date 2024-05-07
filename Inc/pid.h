#include "main.h"

int Balance_angle(int angle_ADC);
int Balance_angle_y(int angle_ADC);
int Balance_angle_handx(int angle_ADC);
int Balance_angle_handy(int angle_ADC);
struct Angle
{
	float KP_angle;
  float KD_angle;
  int balance_angle;
  float error;
  int back_pwm;
};

struct Angle_Y
{
	float KP_angle_y;
  float KD_angle_y;
  int balance_angle_y;
  float error_y;
  int back_pwm_y;
};


//struct Hand_X
//{
//	float KP_angle_handx;
//  float KD_angle_handx;
//  int balance_angle_handx;
//  float error_handx;
//  int back_pwm_handx;
//};

//struct Hand_Y
//{
//	float KP_angle_handy;
//  float KD_angle_handy;
//  int balance_angle_handy;
//  float error_handy;
//  int back_pwm_handy;
//};
//extern struct Hand_X hand_x;
//extern struct Hand_Y hand_y;

void Limit(int *motoA,int *motoB);
int yaw_PD_value(float yaw_measure);
void Limit(int *motoA,int *motoB);
void Machinery_all(void);
void new_multiply_pid(void);
int Velocity(int Target,int encoder_left,int encoder_right);
extern float yaw_calcu;;
extern int sudu_Targe;


