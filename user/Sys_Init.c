
#include "Sys_Init.h"

void Sys_Init(void)
{		

	/************系统初始化*******************************************************/
	/*公用*/
	delay_init();	    		//延时函数初始化	  
	//LED_Init();		  			//初始化与LED连接的硬件接口
	//Beep_Init();					//蜂鸣器初始化
	KEY_Init();						//按键初始化
	//GPIO_OutPut_Init();
	//GPIO_InPut_Init();
	//PWM_Init();
	//USART3_Init(115200);		//串口3初始化 波特率9600
	USART2_Init(9600);		//串口2迪文屏初始化
	USART1_Init(9600);
	USART3_Init(9600);
	USART4_Init(9600);
	USART5_Init(9600);
	Uart2_Mode = LCD;
	NVIC_Configuration(); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级

	IWDG_Init(6,3000);//20秒钟喂狗一次

	Reset_Flag = 0;	

	//Beep(50,50,1);
	
}


