
#include "Sys_Init.h"

void Sys_Init(void)
{		

	/************ϵͳ��ʼ��*******************************************************/
	/*����*/
	delay_init();	    		//��ʱ������ʼ��	  
	//LED_Init();		  			//��ʼ����LED���ӵ�Ӳ���ӿ�
	//Beep_Init();					//��������ʼ��
	KEY_Init();						//������ʼ��
	//GPIO_OutPut_Init();
	//GPIO_InPut_Init();
	//PWM_Init();
	//USART3_Init(115200);		//����3��ʼ�� ������9600
	USART2_Init(9600);		//����2��������ʼ��
	USART1_Init(9600);
	USART3_Init(9600);
	USART4_Init(9600);
	USART5_Init(9600);
	Uart2_Mode = LCD;
	NVIC_Configuration(); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�

	IWDG_Init(6,3000);//20����ι��һ��

	Reset_Flag = 0;	

	//Beep(50,50,1);
	
}


