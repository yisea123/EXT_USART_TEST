 
#include "Sys_Init.h"	
int main(void)
{
	/*******�ϵ��ʼ��*******/
	Sys_Init();		
	
	/***************************��ѭ��****************************/
	while(1)
	{
	

			SURE_REC_UART2_Analyze();     //���������ڽ���

	}
}


int fputc(int ch, FILE *f)
{
USART_SendData(USART3, (unsigned char) ch);
while (!(USART3->SR & USART_FLAG_TXE));

return (ch);

}

