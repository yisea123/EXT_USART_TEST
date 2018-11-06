#ifndef __LCDRS232_H
#define __LCDRS232_H

#include "sys.h"
#include "Sys_Init.h"



//串口2接收数据CCU-TO-TCU
//设备信息
typedef struct
{
	unsigned char Star0;
	unsigned char Star1;
	unsigned char Len;
	unsigned char Comend;
	unsigned char ComData[100];
	unsigned char check;
}struct_USART2;
enum	UART2_MODE{LCD = 1,Laser =2};
extern unsigned char R_right;                                  //接收报文正确标志
extern volatile struct_USART2 Uart2Buff[5];                    //在stm32f10x_it.h里定义	  //串口2接收数据CCU-TO-TCU
extern	unsigned int x_row;   
extern  unsigned int z_column;  
extern unsigned int x_run;   
extern unsigned int z_run;  
extern enum	UART2_MODE Uart2_Mode;
void USART1_Init(u32 baud);
void USART4_Init(u32 baud);
void USART5_Init(u32 baud);
void USART2_Init(u32 baud); //串口2初始化
void USART2_printf_str(u8 len, u8*put_str);	//发送Card信息
void SURE_REC_UART2_Analyze(void);
void REC_UART2_Analyze(unsigned char right_num);//串口数析【SCREEN-TO-ACU】
void Set_Variable(unsigned char adressH,unsigned char adressL, 
									unsigned char data0, unsigned char data1, 
									unsigned char data2, unsigned char data3, 
									unsigned char length);
void SCREEN_Refresh(void);
void ChangePage(unsigned char page);

#endif
