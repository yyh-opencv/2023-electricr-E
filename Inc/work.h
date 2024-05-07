#include "main.h"
#define MOTOX_1 833
#define MOTOX_2 2166 
#define MOTOX_3 1278
#define MOTOX_4 1833 
#define basic_key_34 HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) 
#define sw3 HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15)
void yuntai_follow(void);
void xianfu_x(void);
void xianfu_y(void);
void handle_yuntai(void);
void Lcd_Proc(void);
void Tracing(void);
//µçÈü
void basic_1(void);
void key_proc(void);
void basic_34(void);
