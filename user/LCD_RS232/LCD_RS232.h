#ifndef __LCDRS232_H
#define __LCDRS232_H

#include "sys.h"
#include "Sys_Init.h"



//����2��������CCU-TO-TCU
//�豸��Ϣ
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
extern unsigned char R_right;                                  //���ձ�����ȷ��־
extern volatile struct_USART2 Uart2Buff[5];                    //��stm32f10x_it.h�ﶨ��	  //����2��������CCU-TO-TCU
extern	unsigned int x_row;   
extern  unsigned int z_column;  
extern unsigned int x_run;   
extern unsigned int z_run;  
extern enum	UART2_MODE Uart2_Mode;
void USART1_Init(u32 baud);
void USART4_Init(u32 baud);
void USART5_Init(u32 baud);
void USART2_Init(u32 baud); //����2��ʼ��
void USART2_printf_str(u8 len, u8*put_str);	//����Card��Ϣ
void SURE_REC_UART2_Analyze(void);
void REC_UART2_Analyze(unsigned char right_num);//����������SCREEN-TO-ACU��
void Set_Variable(unsigned char adressH,unsigned char adressL, 
									unsigned char data0, unsigned char data1, 
									unsigned char data2, unsigned char data3, 
									unsigned char length);
void SCREEN_Refresh(void);
void ChangePage(unsigned char page);

#endif
