
#include "Key.h"

bool Key_press_flag = 0;
bool KEY1_flag = 0;
bool KEY2_flag = 0;
bool KEY3_flag = 0;
bool KEY4_flag = 0;
bool KEY5_flag = 0;
bool KEY6_flag = 0;
bool KEY7_flag = 0;
bool KEY8_flag = 0;

bool Bottle_Judge_Record; //��Сƿ��¼ģʽ����(KEY3 + ��λ��)����	
u8 TEST_MODE;           //����ģʽ��ǣ���(KEY4 + ��λ��)����	
u8 TEST_MODE_SAVE = 1;
u8 Bottle_Judge_Mode = 0;	//��Сƿ�ж������¼ģʽ����¼�߰�ƿģʽ�л�
//		char buf0[] = {'+','+','+','\0'};
//		char buf1[] = {'A','T','+','C','W','M','O','D','E','_','D','E','F','=','1','\r','\n','\0'};
//		char buf2[] = {'A','T','+','C','W','J','A','P','_','D','E','F','=','"','J','S','-','L','I','K','U','"',',','"','j','e','s','o','o','1','2','3','"','\r','\n','\0'};
//		char buf3[] = {'A','T','+','C','I','P','S','T','A','R','T','=','"','T','C','P','"',',','"','1','9','2','.','1','6','8','.','0','.','5','3','"',',','6','0','0','0','\r','\n','\0'};
//		char buf4[] = {'A','T','+','C','I','P','M','O','D','E','=','1','\r','\n','\0'};
//		char buf5[] = {'A','T','+','C','I','P','S','T','A','_','D','E','F','=',
//									'"','1','9','2','.','1','6','8','.','0','.','1','1','7','"',',',
//									'"','1','9','2','.','1','6','8','.','0','.','1','1','6','"',',',
//									'"','2','5','5','.','2','5','5','.','2','5','5','.','0','"','\r','\n','\0'};
//		char buf6[] = {'A','T','+','C','I','P','S','E','N','D','\r','\n','\0'};

/*-----------*/
u16 Time_PushRod_Ctrl;   

void KEY_Init(void) //����IO��ʼ��
{ 
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;//PD0,PD2,PD4,PD6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //���ó���������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;				//IO���ٶ�Ϊ50MHz
 	GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��GPIOD	
	GPIO_SetBits(GPIOD, GPIO_Pin_3);
	//GPIO_ResetBits(GPIOD, GPIO_Pin_3);
}

/************�������***********/
void Key_Scan()
{
	if(KEY1 == 0)
	{
		if(Key_press_flag == 0)
		{
			delay_ms(3);
			if(KEY1 == 0)
			{
				Key_press_flag = 1;
				KEY1_flag = 1;
			}
		}
	}
	else if(KEY2 == 0)
	{
		if(Key_press_flag == 0)
		{
			delay_ms(3);
			if(KEY2 == 0)
			{
				Key_press_flag = 1;
				KEY2_flag = 1;
			}
		}
	}
	else if(KEY3 == 0)
	{
		if(Key_press_flag == 0)
		{
			delay_ms(3);
			if(KEY3 == 0)
			{
				Key_press_flag = 1;
				KEY3_flag = 1;
			}
		}
	}
	else if(KEY4 == 0)
	{
		if(Key_press_flag == 0)
		{
			delay_ms(3);
			if(KEY4 == 0)
			{
				Key_press_flag = 1;
				KEY4_flag = 1;
			}
		}
	}
	else if(KEY5 == 0)
	{
		if(Key_press_flag == 0)
		{
			delay_ms(3);
			if(KEY5 == 0)
			{
				Key_press_flag = 1;
				KEY5_flag = 1;
			}
		}
	}
	else if(KEY6 == 0)
	{
		if(Key_press_flag == 0)
		{
			delay_ms(3);
			if(KEY6 == 0)
			{
				Key_press_flag = 1;
				KEY6_flag = 1;
			}
		}		
	}
	else
	{
		Key_press_flag = 0;
	}
}

/************��������***********/
void Key_Deal()
{
	Key_Scan();
	/***********����1����********************/
	if(KEY1_flag == 1)
	{
		KEY1_flag = 0;
		Axis_Move_Alone(AXIS_X,X_DIR_FRONT);
		Beep(200,200,1);
		
	}
	/***********����2����********************/
	if(KEY2_flag == 1)
	{
		KEY2_flag = 0;
		Axis_Move_Alone(AXIS_X,X_DIR_BACK);
		Beep(200,200,1);

	}
	/***********����3����********************/
	if(KEY3_flag == 1)
	{
//		u8 CheckAdd =0;
		KEY3_flag = 0;		
		Axis_Move_Alone(AXIS_Y,Y_DIR_LEFT);
		Beep(200,100,1);      //��������һ��

//		send_char(buf3,0);//AT+CIPSTART="TCP","192.168.0.53",6000
//		delay_ms(1000);
//		send_char(buf4,0);//AT+CIPMODE=1
//		delay_ms(1000);
//		send_char(buf5,0);//AT+CIPSTA_DEF="192.168.0.117","192.168.0.116","255.255.255.0"
//		delay_ms(1000);
//		send_char(buf6,0);//AT+CIPSEND
	}
	/***********����4����********************/
	if(KEY4_flag == 1)
	{
		KEY4_flag = 0;
		Axis_Move_Alone(AXIS_Y,Y_DIR_RIGHT);
		Beep(200,100,1);      //��������һ��

	}
	/***********����5����********************/
	if(KEY5_flag == 1)
	{
		KEY5_flag = 0;
		Axis_Move_Alone(AXIS_Z,Z_DIR_FRONT);
		Beep(50,50,1);      //��������һ��
	}
	/***********����6����********************/
	if(KEY6_flag == 1)
	{
		KEY6_flag = 0;	
		Axis_Move_Alone(AXIS_Z,Z_DIR_BACK);
		Beep(50,50,1);      //��������һ��
	}
}



