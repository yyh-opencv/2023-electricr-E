#include "jy901.h"
#include "stdio.h"
#include "string.h"
#include "usart.h"
//#include "openmv.h"
//#include "Tracing.h"
#include "bsp_uasrt.h"
extern uint8_t y;
//User_USART JY901_data;
//struct SAcc 		stcAcc;
//struct SGyro 		stcGyro;
//struct SAngle 	stcAngle;
//struct SMag 	stcMag;
//struct SPress 	stcPress;
//struct SLonLat 	stcLonLat;
//struct SQ stcQ;

//void User_USART_Init(User_USART *Data)
//{
//		for(uint16_t i=0; i < RXBUFFER_LEN; i++)	Data->RxBuffer[i] = 0;
//		Data->frame_head = 0x55;
//		Data->Rx_flag = 0;
//		Data->Rx_len = 0;
//}



User_USART JY901_data;
extern UART_HandleTypeDef huart6;
extern UART_HandleTypeDef huart1;

struct SAcc 		stcAcc;
struct SGyro 		stcGyro;
struct SAngle 	stcAngle;

uint8_t a =0;



//��ʼ������
void User_USART_Init(User_USART *Data)
{
		for(uint16_t i=0; i < RXBUFFER_LEN; i++)	Data->RxBuffer[i] = 0;
		Data->frame_head = 0x55;
		Data->Rx_flag = 0;
		Data->Rx_len = 0;
}

void JY901_Process()
{
		if(JY901_data.Rx_len < RXBUFFER_LEN) return;   	//���ݳ��Ȳ���

		for(uint8_t i=0;i<3;i++)
		{
				if(JY901_data.RxBuffer[i*11]!= JY901_data.frame_head) continue;
				switch(JY901_data.RxBuffer[i*11+1])
				{
//						case 0x51:	
//							memcpy(&stcAcc,&JY901_data.RxBuffer[2 + i*11],8);
//							for(uint8_t j = 0; j < 3; j++) JY901_data.acc.a[j] = (float)stcAcc.a[j]/32768.00*16;									//���ٶ�
//						break;
//						case 0x52:	
//							memcpy(&stcGyro,&JY901_data.RxBuffer[2 + i*11],8);
//							for(uint8_t j = 0; j < 3; j++) JY901_data.w.w[j] = (float)stcGyro.w[j]/32768.00*2000;								//���ٶ�
//						break;
						case 0x53:	
							memcpy(&stcAngle,&JY901_data.RxBuffer[2 + i*11],8);
							for(uint8_t j = 0; j < 3; j++) JY901_data.angle.angle[j] = (float)stcAngle.Angle[j]/32768.00*180;		//�Ƕ�
						break;
				}
				
		}

}



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{  
	uint8_t tem;// ��������޷��ŵ�
//	if(huart->Instance==USART2)
//	{

//			JY901_data.Rx_len=33;
//			JY901_Process();
//			HAL_UART_Receive_IT(&huart2,JY901_data.RxBuffer,RXBUFFER_LEN);
//	}
//	 
//	
//	//RedSignal_Toggle;   //�������Ƿ�������ݵ�, ����Ҫ��ʱ��ûЧ���Ļ��ʹ���������3���ж϶�û����
//  else if(huart->Instance== USART1)     //����ֻ��������дUSart1
//  {

//    tem=uart1_rxbuff;
//		
//    usatr1_MV_Receive_Data(tem);
//    HAL_UART_Receive_IT(&huart1,&uart1_rxbuff,1); 
//		
//  }	
	else if(huart->Instance== USART3)     //����ֻ��������дUSart1
  {

    tem=uart3_rxbuff;
		
    usatr3_MV_Receive_Data(tem);
    HAL_UART_Receive_IT(&huart3,&uart3_rxbuff,1); 
		
  }	
}
