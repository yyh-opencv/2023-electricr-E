#include "bsp_uasrt.h"
#include "usart.h"
uint16_t RxBuffer1[15]={0};
uint16_t RxBuffer3[30]={0};
//uint8_t tem;// 这里的是无符号的
//uint8_t tem2;// 这里的是无符号的
int bb;
//struct TOF tof;
struct MV mv;
struct MV_3 mv3;
uint8_t uart1_rxbuff;
uint8_t uart3_rxbuff;
uint8_t RxFlag1 = 0;
uint8_t RxFlag3 = 0;


//void usatr1_MV_Receive_Data(uint8_t com_data)
//{
//		
//		static uint8_t RxCounter1=0;//计数
//		uint8_t f=0; 
//		static uint8_t RxState1 = 0;	
//		

//		if(RxState1==0&&com_data==0x5C)  //0x80帧头
//		{
//			
//			RxState1=1;
//			RxBuffer1[RxCounter1++]=com_data;  
//		}

//		else if(RxState1==1&&com_data==0x21)  //0x06帧头
//		{
//			RxState1=2;
//			RxBuffer1[RxCounter1++]=com_data;
//		}
//		
//		
//		else if(RxState1==2)
//		{
//			 
//			RxBuffer1[RxCounter1++]=com_data;
//			if(RxCounter1>=10)       //RxBuffer1接受满了,接收数据结束
//			{
//				RxState1=3;
//				RxFlag1=1;
//				
//				
//				mv.flag =RxBuffer1[RxCounter1-8]; 
//				mv.bw=RxBuffer1[RxCounter1-7]; 
//				mv.sw=RxBuffer1[RxCounter1-6];
//				mv.gw=RxBuffer1[RxCounter1-5];
//			
//				mv.bw_y=RxBuffer1[RxCounter1-3];
//				mv.sw_y=RxBuffer1[RxCounter1-2];
//				mv.gw_y=RxBuffer1[RxCounter1-1];
//			
//			  mv.MV_error =(int)(mv.bw*100+mv.sw*10+mv.gw);
//		  	mv.MV_error_y=(int)(mv.bw_y*100+mv.sw_y*10+mv.gw_y);
//				
//			}
//		}

//		else if(RxState1==3)		//检测是否接受到结束标志
//		{
//				if(RxCounter1 ==6)
//				{
//							
//							RxFlag1 = 0;
//							RxCounter1 = 0;
//							RxState1 = 0;
//						
//				}
//				else   //接收错误
//				{
//							RxState1 = 0;
//							RxCounter1=0;
//							for(f=0;f<15;f++)
//							{
//									RxBuffer1[f]=0x00;      //将存放数据数组清零
//							}
//				}
//		} 

//		else   //接收异常
//		{
//				RxState1 = 0;
//				RxCounter1=0;
//				for(f=0;f<15;f++)
//				{
//						RxBuffer1[f]=0x00;      //将存放数据数组清零
//				}
//		}
//}

//串口3直角坐标
void usatr3_MV_Receive_Data(uint8_t com_data)
{
		
		static uint8_t RxCounter3=0;//计数
		uint8_t f=0; 
		static uint8_t RxState3 = 0;	
		

		if(RxState3==0&&com_data==0x2B)  
		{
			
			RxState3=1;
			RxBuffer3[RxCounter3++]=com_data;  
		}

		else if(RxState3==1&&com_data==0x4F)  
		{
			RxState3=2;
			RxBuffer3[RxCounter3++]=com_data;
		}
		
		
		else if(RxState3==2)
		{
			 
			RxBuffer3[RxCounter3++]=com_data;
			if(RxCounter3>=26)       //RxBuffer1接受满了,接收数据结束
			{
				RxState3=3;
				RxFlag3=1;
				
			
				mv3.g_1_x1=RxBuffer3[RxCounter3-24];
				mv3.g_1_x2=RxBuffer3[RxCounter3-23];
				mv3.g_1_x3=RxBuffer3[RxCounter3-22];
				
				mv3.g_1_y1=RxBuffer3[RxCounter3-21];
				mv3.g_1_y2=RxBuffer3[RxCounter3-20];
				mv3.g_1_y3=RxBuffer3[RxCounter3-19];
				
				mv3.g_2_x1=RxBuffer3[RxCounter3-18];
				mv3.g_2_x2=RxBuffer3[RxCounter3-17];
				mv3.g_2_x3=RxBuffer3[RxCounter3-16];
				
				mv3.g_2_y1=RxBuffer3[RxCounter3-15];
				mv3.g_2_y2=RxBuffer3[RxCounter3-14];
				mv3.g_2_y3=RxBuffer3[RxCounter3-13];
				
				mv3.g_3_x1=RxBuffer3[RxCounter3-12];
				mv3.g_3_x2=RxBuffer3[RxCounter3-11];
				mv3.g_3_x3=RxBuffer3[RxCounter3-10];
				
				mv3.g_3_y1=RxBuffer3[RxCounter3-9];
				mv3.g_3_y2=RxBuffer3[RxCounter3-8];
				mv3.g_3_y3=RxBuffer3[RxCounter3-7];
				
				mv3.g_4_x1=RxBuffer3[RxCounter3-6];
				mv3.g_4_x2=RxBuffer3[RxCounter3-5];
				mv3.g_4_x3=RxBuffer3[RxCounter3-4];
				
				mv3.g_4_y1=RxBuffer3[RxCounter3-3];
				mv3.g_4_y2=RxBuffer3[RxCounter3-2];
				mv3.g_4_y3=RxBuffer3[RxCounter3-1];
				
				
			  mv3.g_1_x =(int)(mv3.g_1_x1*100+mv3.g_1_x2*10+mv3.g_1_x3);
				mv3.g_2_x =(int)(mv3.g_2_x1*100+mv3.g_2_x2*10+mv3.g_2_x3);
				mv3.g_3_x =(int)(mv3.g_3_x1*100+mv3.g_3_x2*10+mv3.g_3_x3);
				mv3.g_4_x =(int)(mv3.g_4_x1*100+mv3.g_4_x2*10+mv3.g_4_x3);
				
			  mv3.g_1_y =(int)(mv3.g_1_y1*100+mv3.g_1_y2*10+mv3.g_1_y3);
				mv3.g_2_y =(int)(mv3.g_2_y1*100+mv3.g_2_y2*10+mv3.g_2_y3);
				mv3.g_3_y =(int)(mv3.g_3_y1*100+mv3.g_3_y2*10+mv3.g_3_y3);
				mv3.g_4_y =(int)(mv3.g_4_y1*100+mv3.g_4_y2*10+mv3.g_4_y3);
				
		  	
			}
		}

		else if(RxState3==3)		//检测是否接受到结束标志
		{
				if(RxCounter3 ==26)
				{
							
							RxFlag3 = 0;
							RxCounter3 = 0;
							RxState3 = 0;
						
				}
				else   //接收错误
				{
							RxState3 = 0;
							RxCounter3=0;
							for(f=0;f<30;f++)
							{
									RxBuffer3[f]=0x00;      //将存放数据数组清零
							}
				}
		} 

		else   //接收异常
		{
				RxState3 = 0;
				RxCounter3=0;
				for(f=0;f<30;f++)
				{
						RxBuffer3[f]=0x00;      //将存放数据数组清零
				}
		}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{  
	uint8_t tem;// 这里的是无符号的
//	if(huart->Instance==USART2)
//	{

//			JY901_data.Rx_len=33;
//			JY901_Process();
//			HAL_UART_Receive_IT(&huart2,JY901_data.RxBuffer,RXBUFFER_LEN);
//	}
//	 
//	
//	//RedSignal_Toggle;   //用来看是否接收数据的, 这里要随时都没效果的话就代表连串口3的中断都没进来
//  else if(huart->Instance== USART1)     //这里只能这样大写USart1
//  {

//    tem=uart1_rxbuff;
//		
//    usatr1_MV_Receive_Data(tem);
//    HAL_UART_Receive_IT(&huart1,&uart1_rxbuff,1); 
//		
//  }	
	if(huart->Instance== USART3)     //这里只能这样大写USart1
  {

    tem=uart3_rxbuff;
		
    usatr3_MV_Receive_Data(tem);
    HAL_UART_Receive_IT(&huart3,&uart3_rxbuff,1); 
		
  }	
}



