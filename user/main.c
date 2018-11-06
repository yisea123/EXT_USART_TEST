 
#include "Sys_Init.h"	
int main(void)
{
	/*******上电初始化*******/
	Sys_Init();		
	
	/***************************主循环****************************/
	while(1)
	{
	

			SURE_REC_UART2_Analyze();     //迪文屏串口解析

	}
}


int fputc(int ch, FILE *f)
{
USART_SendData(USART3, (unsigned char) ch);
while (!(USART3->SR & USART_FLAG_TXE));

return (ch);

}

