
#include "main.h"
extern int iTim5Encoder;//��Ŵ�TIM5��ʱ���������ı���������		����
extern int iTim8Encoder;
extern int Tim5Encoder;//	����
extern int Tim8Encoder;//  ����

int GetTim5Encoder(void);
int GetTim8Encoder(void);
void SetMotorVoltageAndDirection_SL(int nMotorPwm);
void SetMotorVoltageAndDirection_SR(int nMotorPwm);
void ALL_Encoder(void);

