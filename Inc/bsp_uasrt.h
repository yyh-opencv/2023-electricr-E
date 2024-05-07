#include "main.h"
extern uint8_t uart1_rxbuff;
extern uint8_t uart3_rxbuff;
//extern uint16_t RxBuffer1[15];
//uint16_t RxBuffer2[15]={0};
//extern uint8_t tem;// 这里的是无符号的
//uint8_t tem2;// 这里的是无符号的


struct MV
{
	uint8_t  flag;
	uint8_t bw;
	uint8_t sw;
	uint8_t gw;
	uint8_t bw_y;
	uint8_t sw_y;
	uint8_t gw_y;
	int MV_error;
	int MV_error_y;
};
struct MV_3
{
  uint8_t g_1_x1;
	uint8_t g_1_x2;
	uint8_t g_1_x3;
	
  uint8_t g_1_y1;
	uint8_t g_1_y2;
	uint8_t g_1_y3;
	
  uint8_t g_2_x1;
	uint8_t g_2_x2;
	uint8_t g_2_x3;
	
  uint8_t g_2_y1;
	uint8_t g_2_y2;
	uint8_t g_2_y3;
	
  uint8_t g_3_x1;
	uint8_t g_3_x2;
	uint8_t g_3_x3;
	
  uint8_t g_3_y1;
	uint8_t g_3_y2;
	uint8_t g_3_y3;
	
  uint8_t g_4_x1;
	uint8_t g_4_x2;
	uint8_t g_4_x3;
	
  uint8_t g_4_y1;
	uint8_t g_4_y2;
	uint8_t g_4_y3;
  
	
	//解算目标
	int g_1_x,g_2_x,g_3_x,g_4_x;
	int g_1_y,g_2_y,g_3_y,g_4_y;
};

void usatr3_MV_Receive_Data(uint8_t com_data);
void usatr1_MV_Receive_Data(uint8_t com_data);

