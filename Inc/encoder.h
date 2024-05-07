
#include "main.h"
extern int iTim5Encoder;//存放从TIM5定时器读出来的编码器脉冲		上左
extern int iTim8Encoder;
extern int Tim5Encoder;//	上左
extern int Tim8Encoder;//  上右

int GetTim5Encoder(void);
int GetTim8Encoder(void);
void SetMotorVoltageAndDirection_SL(int nMotorPwm);
void SetMotorVoltageAndDirection_SR(int nMotorPwm);
void ALL_Encoder(void);

