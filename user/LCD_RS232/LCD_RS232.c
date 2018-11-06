
//#include "stm32f10x.h"
#include "LCD_RS232.h"

unsigned char R_right;                                  //���ձ�����ȷ��־
volatile struct_USART2 Uart2Buff[5];                    //��stm32f10x_it.h�ﶨ��	  //����2��������CCU-TO-TCU
unsigned int x_row;   
unsigned int z_column;  
void Uart_Sendtest(u8 t1,u8 t2,u8 t3,u8 t4,u8 t5,u8 t6);
unsigned int x_run;   
 unsigned int z_run;  
enum	UART2_MODE Uart2_Mode;
//����2��ʼ��


void USART5_Init(u32 baud)
{
	NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure; 
	USART_InitTypeDef USART_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);					//USART2ʱ������
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	
	USART_DeInit(UART5);  //��λ����2
	
	/* Configure USART2 Tx (PA.2) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  /* Configure USART2 Rx (PA.3) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  USART_InitStructure.USART_BaudRate =baud;						    				//������115200bps
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;			//8Ϊ����λ
  USART_InitStructure.USART_StopBits = USART_StopBits_1;					//1λֹͣλ
  USART_InitStructure.USART_Parity = USART_Parity_No;							//����żУ��λ
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  //��Ӳ��������
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  /********************USART2�жϳ�ʼ��***********************/
  //Usart2 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=4 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  

  USART_Init(UART5, &USART_InitStructure); 		//��ʼ������
	
	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//�����ж�
	USART_Cmd(UART5, ENABLE);                    //ʹ�ܴ���
	USART_ClearFlag(UART5, USART_FLAG_TXE);			//�巢����ɱ�־
}


void USART4_Init(u32 baud)
{
	NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure; 
	USART_InitTypeDef USART_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);					//USART2ʱ������
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	USART_DeInit(UART4);  //��λ����2
	
	/* Configure USART2 Tx (PA.2) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  /* Configure USART2 Rx (PA.3) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  USART_InitStructure.USART_BaudRate =baud;						    				//������115200bps
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;			//8Ϊ����λ
  USART_InitStructure.USART_StopBits = USART_StopBits_1;					//1λֹͣλ
  USART_InitStructure.USART_Parity = USART_Parity_No;							//����żУ��λ
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  //��Ӳ��������
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  /********************USART2�жϳ�ʼ��***********************/
  //Usart2 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  

  USART_Init(UART4, &USART_InitStructure); 		//��ʼ������
	
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//�����ж�
	USART_Cmd(UART4, ENABLE);                    //ʹ�ܴ���
	USART_ClearFlag(UART4, USART_FLAG_TXE);			//�巢����ɱ�־
}

void USART2_Init(u32 baud)
{
	NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure; 
	USART_InitTypeDef USART_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);					//USART2ʱ������
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	USART_DeInit(USART2);  //��λ����2
	
	/* Configure USART2 Tx (PA.2) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  /* Configure USART2 Rx (PA.3) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  USART_InitStructure.USART_BaudRate =baud;						    				//������115200bps
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;			//8Ϊ����λ
  USART_InitStructure.USART_StopBits = USART_StopBits_1;					//1λֹͣλ
  USART_InitStructure.USART_Parity = USART_Parity_No;							//����żУ��λ
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  //��Ӳ��������
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  /********************USART2�жϳ�ʼ��***********************/
  //Usart2 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  

  USART_Init(USART2, &USART_InitStructure); 		//��ʼ������
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�����ж�
	USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ���
	USART_ClearFlag(USART2, USART_FLAG_TXE);			//�巢����ɱ�־
}

void USART1_Init(u32 baud)
{
	NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure; 
	USART_InitTypeDef USART_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);					//USART2ʱ������
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	USART_DeInit(USART1);  //��λ����2
	
	/* Configure USART2 Tx (PA.2) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  /* Configure USART2 Rx (PA.3) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  USART_InitStructure.USART_BaudRate =baud;						    				//������115200bps
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;			//8Ϊ����λ
  USART_InitStructure.USART_StopBits = USART_StopBits_1;					//1λֹͣλ
  USART_InitStructure.USART_Parity = USART_Parity_No;							//����żУ��λ
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  //��Ӳ��������
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  /********************USART2�жϳ�ʼ��***********************/
  //Usart2 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  

  USART_Init(USART1, &USART_InitStructure); 		//��ʼ������
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�����ж�
	USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���
	USART_ClearFlag(USART1, USART_FLAG_TXE);			//�巢����ɱ�־
}

void USART2_printf_str(u8 len, u8*put_str)
{
	u8 i;
	for(i=0; i<len; i++)
	{
		USART_SendData(USART2,put_str[i]);
	}
}

/*******************************************************************************
* Function Name  : USART2_IRQHandler
* Description    : This function handles USART2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
unsigned char recflag=0; //���ձ�־
unsigned int reclenth=0;//���ճ��ȼ�¼���ֶΣ�
unsigned char recbuff;	 //���ջ���
unsigned char check_temp=0;//У��λ



void UART5_IRQHandler(void)
{
  USART_ClearITPendingBit(UART5,USART_IT_RXNE); 

	recbuff=USART_ReceiveData(UART5);	//���������ݴ�
	if(Uart2_Mode == LCD)
	{
		
		switch(recflag)//��ʼֵΪ0
		{
			case 0: //֡ͷ1
			{
				 if(recbuff==0xa5)
				 {
					Uart2Buff[R_right].Star0=recbuff;
					recflag=1;
				 }
				 else 
				 {
					recflag=0;//���ճ�ʼ�����½���
					reclenth=0;
					check_temp=0;
				 }
			}break;
			case 1: //֡ͷ2
			{
				 if(recbuff==0x5a)
				 {
					Uart2Buff[R_right].Star1=recbuff;
					recflag=2;
				 }
				 else 
				 {
					recflag=0;//���ճ�ʼ�����½���
					reclenth=0;
					check_temp=0;
				 }
			}break;
			case 2: //���ݳ���
			{
				 Uart2Buff[R_right].Len=recbuff;
				 check_temp+=recbuff;
				 recflag=3;
			}break;
			case 3: //ָ��
			{
				 Uart2Buff[R_right].Comend=recbuff;
				 check_temp+=recbuff;
				 recflag=4;
			}break;
			case 4: //����
			{
				 Uart2Buff[R_right].ComData[reclenth]=recbuff;
				 reclenth++;
				 check_temp+=recbuff;
				 if(reclenth==(Uart2Buff[R_right].Len-1))
				 {
						 recflag=0;//���ճ�ʼ�����½���
						 check_temp=0;
						 reclenth=0;
						 R_right++;//���ճɹ���־��ʹ�ܡ�
						 if(R_right>=4)R_right=1;
				 }
			}break;
		}
	}
	else	
	{
		switch(rec_num)//��ʼֵΪ0
		{
		case 0: //����0
		{
			if(recbuff!=0x6d)
			{
			 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;	//
			 Laser_Length++;			
			 rec_num = 1;
			}
			else
			{
				Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;
				rec_num = 0;//���ճ�ʼ�����½���
				Lrecflag = 0; //������ɱ�־
				Laser_Length = 0;
			}
		}break;
		case 1: //����1
		{
			 if(recbuff!=0x6d)//����
			 {
					 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;	//
					 Laser_Length++;
					 rec_num = 2;					   
			 }				 
				else
				{
				 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;
					Laser_Length++;
				 Laser_Rec[Laser_Rright].Data_Len = 1;						
				 rec_num = 4;//���ճ�ʼ�����½���
				}				 					
		}break;			
		case 2://����2
		{
			 if(recbuff!=0x6d)//����
			 {
				 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;	//
				 Laser_Length++;
				 rec_num = 3;					 
			 }
			 else
			 {
				 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;
				 Laser_Rec[Laser_Rright].Data_Len = 2;
				 rec_num = 4;//���ճ�ʼ�����½���
				 Laser_Length++;
			 }
		
						 
		}break;

		case 3://У��1
		{			
			if(recbuff == 0x6d)//����
		 {				 
			 Laser_Rec[Laser_Rright].Data_Len = 3;
			 rec_num = 4;//���ճ�ʼ�����½���
			 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;
			 Laser_Length++;
		 }
		 else
		 {
			 rec_num = 0;//���ճ�ʼ�����½���
			 Lrecflag = 0; //������ɱ�־
			 Laser_Length = 0;
		 }			 		
		}break;
		case 4://У��2
		{			
			if(recbuff == 0x6d)//����
		 {				 
			 rec_num = 5;//���ճ�ʼ�����½���
			 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;
			 Laser_Length++;
		 }
		 else
		 {
			 rec_num = 0;//���ճ�ʼ�����½���
			 Lrecflag = 0; //������ɱ�־
			 Laser_Length = 0;
		 }			 		
		}break;
		case 5://У��3
		{			
			if(recbuff == 0x0d)//����
		 {				 
			 rec_num = 6;//���ճ�ʼ�����½���
			 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;
			 Laser_Length++;
		 }
		 else
		 {
			 rec_num = 0;//���ճ�ʼ�����½���
			 Lrecflag = 0; //������ɱ�־
			 Laser_Length = 0;
		 }			 		
		}break;
		case 6://У��4
		{			
			if(recbuff == 0x0a)//����
		 {			
			 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;				  
			 rec_num = 0;//���ճ�ʼ�����½���
			 Laser_Rright++;
			 Laser_Length=0;
			 Lrecflag = 1; //�������
			 
			 if(Laser_Rright>=(LasBufLen-1))
			 {
				Laser_Rright = 1;
				Laser_Length = 0;						 
			 }
		 }
		 else
		 {
			 rec_num = 0;//���ճ�ʼ�����½���
			 Lrecflag = 0; //������ɱ�־
			 Laser_Length = 0;
		 }			 		
		}break;
		

		}
	}
}


void UART4_IRQHandler(void)
{
  USART_ClearITPendingBit(UART4,USART_IT_RXNE); 

	recbuff=USART_ReceiveData(UART4);	//���������ݴ�
	if(Uart2_Mode == LCD)
	{
		
		switch(recflag)//��ʼֵΪ0
		{
			case 0: //֡ͷ1
			{
				 if(recbuff==0xa5)
				 {
					Uart2Buff[R_right].Star0=recbuff;
					recflag=1;
				 }
				 else 
				 {
					recflag=0;//���ճ�ʼ�����½���
					reclenth=0;
					check_temp=0;
				 }
			}break;
			case 1: //֡ͷ2
			{
				 if(recbuff==0x5a)
				 {
					Uart2Buff[R_right].Star1=recbuff;
					recflag=2;
				 }
				 else 
				 {
					recflag=0;//���ճ�ʼ�����½���
					reclenth=0;
					check_temp=0;
				 }
			}break;
			case 2: //���ݳ���
			{
				 Uart2Buff[R_right].Len=recbuff;
				 check_temp+=recbuff;
				 recflag=3;
			}break;
			case 3: //ָ��
			{
				 Uart2Buff[R_right].Comend=recbuff;
				 check_temp+=recbuff;
				 recflag=4;
			}break;
			case 4: //����
			{
				 Uart2Buff[R_right].ComData[reclenth]=recbuff;
				 reclenth++;
				 check_temp+=recbuff;
				 if(reclenth==(Uart2Buff[R_right].Len-1))
				 {
						 recflag=0;//���ճ�ʼ�����½���
						 check_temp=0;
						 reclenth=0;
						 R_right++;//���ճɹ���־��ʹ�ܡ�
						 if(R_right>=4)R_right=1;
				 }
			}break;
		}
	}
	else	
	{
		switch(rec_num)//��ʼֵΪ0
		{
		case 0: //����0
		{
			if(recbuff!=0x6d)
			{
			 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;	//
			 Laser_Length++;			
			 rec_num = 1;
			}
			else
			{
				Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;
				rec_num = 0;//���ճ�ʼ�����½���
				Lrecflag = 0; //������ɱ�־
				Laser_Length = 0;
			}
		}break;
		case 1: //����1
		{
			 if(recbuff!=0x6d)//����
			 {
					 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;	//
					 Laser_Length++;
					 rec_num = 2;					   
			 }				 
				else
				{
				 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;
					Laser_Length++;
				 Laser_Rec[Laser_Rright].Data_Len = 1;						
				 rec_num = 4;//���ճ�ʼ�����½���
				}				 					
		}break;			
		case 2://����2
		{
			 if(recbuff!=0x6d)//����
			 {
				 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;	//
				 Laser_Length++;
				 rec_num = 3;					 
			 }
			 else
			 {
				 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;
				 Laser_Rec[Laser_Rright].Data_Len = 2;
				 rec_num = 4;//���ճ�ʼ�����½���
				 Laser_Length++;
			 }
		
						 
		}break;

		case 3://У��1
		{			
			if(recbuff == 0x6d)//����
		 {				 
			 Laser_Rec[Laser_Rright].Data_Len = 3;
			 rec_num = 4;//���ճ�ʼ�����½���
			 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;
			 Laser_Length++;
		 }
		 else
		 {
			 rec_num = 0;//���ճ�ʼ�����½���
			 Lrecflag = 0; //������ɱ�־
			 Laser_Length = 0;
		 }			 		
		}break;
		case 4://У��2
		{			
			if(recbuff == 0x6d)//����
		 {				 
			 rec_num = 5;//���ճ�ʼ�����½���
			 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;
			 Laser_Length++;
		 }
		 else
		 {
			 rec_num = 0;//���ճ�ʼ�����½���
			 Lrecflag = 0; //������ɱ�־
			 Laser_Length = 0;
		 }			 		
		}break;
		case 5://У��3
		{			
			if(recbuff == 0x0d)//����
		 {				 
			 rec_num = 6;//���ճ�ʼ�����½���
			 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;
			 Laser_Length++;
		 }
		 else
		 {
			 rec_num = 0;//���ճ�ʼ�����½���
			 Lrecflag = 0; //������ɱ�־
			 Laser_Length = 0;
		 }			 		
		}break;
		case 6://У��4
		{			
			if(recbuff == 0x0a)//����
		 {			
			 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;				  
			 rec_num = 0;//���ճ�ʼ�����½���
			 Laser_Rright++;
			 Laser_Length=0;
			 Lrecflag = 1; //�������
			 
			 if(Laser_Rright>=(LasBufLen-1))
			 {
				Laser_Rright = 1;
				Laser_Length = 0;						 
			 }
		 }
		 else
		 {
			 rec_num = 0;//���ճ�ʼ�����½���
			 Lrecflag = 0; //������ɱ�־
			 Laser_Length = 0;
		 }			 		
		}break;
		

		}
	}
}

void USART3_IRQHandler(void)
{
  USART_ClearITPendingBit(USART3,USART_IT_RXNE); 

	recbuff=USART_ReceiveData(USART3);	//���������ݴ�
	if(Uart2_Mode == LCD)
	{
		
		switch(recflag)//��ʼֵΪ0
		{
			case 0: //֡ͷ1
			{
				 if(recbuff==0xa5)
				 {
					Uart2Buff[R_right].Star0=recbuff;
					recflag=1;
				 }
				 else 
				 {
					recflag=0;//���ճ�ʼ�����½���
					reclenth=0;
					check_temp=0;
				 }
			}break;
			case 1: //֡ͷ2
			{
				 if(recbuff==0x5a)
				 {
					Uart2Buff[R_right].Star1=recbuff;
					recflag=2;
				 }
				 else 
				 {
					recflag=0;//���ճ�ʼ�����½���
					reclenth=0;
					check_temp=0;
				 }
			}break;
			case 2: //���ݳ���
			{
				 Uart2Buff[R_right].Len=recbuff;
				 check_temp+=recbuff;
				 recflag=3;
			}break;
			case 3: //ָ��
			{
				 Uart2Buff[R_right].Comend=recbuff;
				 check_temp+=recbuff;
				 recflag=4;
			}break;
			case 4: //����
			{
				 Uart2Buff[R_right].ComData[reclenth]=recbuff;
				 reclenth++;
				 check_temp+=recbuff;
				 if(reclenth==(Uart2Buff[R_right].Len-1))
				 {
						 recflag=0;//���ճ�ʼ�����½���
						 check_temp=0;
						 reclenth=0;
						 R_right++;//���ճɹ���־��ʹ�ܡ�
						 if(R_right>=4)R_right=1;
				 }
			}break;
		}
	}
	else	
	{
		switch(rec_num)//��ʼֵΪ0
		{
		case 0: //����0
		{
			if(recbuff!=0x6d)
			{
			 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;	//
			 Laser_Length++;			
			 rec_num = 1;
			}
			else
			{
				Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;
				rec_num = 0;//���ճ�ʼ�����½���
				Lrecflag = 0; //������ɱ�־
				Laser_Length = 0;
			}
		}break;
		case 1: //����1
		{
			 if(recbuff!=0x6d)//����
			 {
					 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;	//
					 Laser_Length++;
					 rec_num = 2;					   
			 }				 
				else
				{
				 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;
					Laser_Length++;
				 Laser_Rec[Laser_Rright].Data_Len = 1;						
				 rec_num = 4;//���ճ�ʼ�����½���
				}				 					
		}break;			
		case 2://����2
		{
			 if(recbuff!=0x6d)//����
			 {
				 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;	//
				 Laser_Length++;
				 rec_num = 3;					 
			 }
			 else
			 {
				 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;
				 Laser_Rec[Laser_Rright].Data_Len = 2;
				 rec_num = 4;//���ճ�ʼ�����½���
				 Laser_Length++;
			 }
		
						 
		}break;

		case 3://У��1
		{			
			if(recbuff == 0x6d)//����
		 {				 
			 Laser_Rec[Laser_Rright].Data_Len = 3;
			 rec_num = 4;//���ճ�ʼ�����½���
			 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;
			 Laser_Length++;
		 }
		 else
		 {
			 rec_num = 0;//���ճ�ʼ�����½���
			 Lrecflag = 0; //������ɱ�־
			 Laser_Length = 0;
		 }			 		
		}break;
		case 4://У��2
		{			
			if(recbuff == 0x6d)//����
		 {				 
			 rec_num = 5;//���ճ�ʼ�����½���
			 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;
			 Laser_Length++;
		 }
		 else
		 {
			 rec_num = 0;//���ճ�ʼ�����½���
			 Lrecflag = 0; //������ɱ�־
			 Laser_Length = 0;
		 }			 		
		}break;
		case 5://У��3
		{			
			if(recbuff == 0x0d)//����
		 {				 
			 rec_num = 6;//���ճ�ʼ�����½���
			 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;
			 Laser_Length++;
		 }
		 else
		 {
			 rec_num = 0;//���ճ�ʼ�����½���
			 Lrecflag = 0; //������ɱ�־
			 Laser_Length = 0;
		 }			 		
		}break;
		case 6://У��4
		{			
			if(recbuff == 0x0a)//����
		 {			
			 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;				  
			 rec_num = 0;//���ճ�ʼ�����½���
			 Laser_Rright++;
			 Laser_Length=0;
			 Lrecflag = 1; //�������
			 
			 if(Laser_Rright>=(LasBufLen-1))
			 {
				Laser_Rright = 1;
				Laser_Length = 0;						 
			 }
		 }
		 else
		 {
			 rec_num = 0;//���ճ�ʼ�����½���
			 Lrecflag = 0; //������ɱ�־
			 Laser_Length = 0;
		 }			 		
		}break;
		

		}
	}
}

void USART2_IRQHandler(void)
{
  USART_ClearITPendingBit(USART2,USART_IT_RXNE); 

	recbuff=USART_ReceiveData(USART2);	//���������ݴ�
	if(Uart2_Mode == LCD)
	{
		
		switch(recflag)//��ʼֵΪ0
		{
			case 0: //֡ͷ1
			{
				 if(recbuff==0xa5)
				 {
					Uart2Buff[R_right].Star0=recbuff;
					recflag=1;
				 }
				 else 
				 {
					recflag=0;//���ճ�ʼ�����½���
					reclenth=0;
					check_temp=0;
				 }
			}break;
			case 1: //֡ͷ2
			{
				 if(recbuff==0x5a)
				 {
					Uart2Buff[R_right].Star1=recbuff;
					recflag=2;
				 }
				 else 
				 {
					recflag=0;//���ճ�ʼ�����½���
					reclenth=0;
					check_temp=0;
				 }
			}break;
			case 2: //���ݳ���
			{
				 Uart2Buff[R_right].Len=recbuff;
				 check_temp+=recbuff;
				 recflag=3;
			}break;
			case 3: //ָ��
			{
				 Uart2Buff[R_right].Comend=recbuff;
				 check_temp+=recbuff;
				 recflag=4;
			}break;
			case 4: //����
			{
				 Uart2Buff[R_right].ComData[reclenth]=recbuff;
				 reclenth++;
				 check_temp+=recbuff;
				 if(reclenth==(Uart2Buff[R_right].Len-1))
				 {
						 recflag=0;//���ճ�ʼ�����½���
						 check_temp=0;
						 reclenth=0;
						 R_right++;//���ճɹ���־��ʹ�ܡ�
						 if(R_right>=4)R_right=1;
				 }
			}break;
		}
	}
	else	
	{
		switch(rec_num)//��ʼֵΪ0
		{
		case 0: //����0
		{
			if(recbuff!=0x6d)
			{
			 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;	//
			 Laser_Length++;			
			 rec_num = 1;
			}
			else
			{
				Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;
				rec_num = 0;//���ճ�ʼ�����½���
				Lrecflag = 0; //������ɱ�־
				Laser_Length = 0;
			}
		}break;
		case 1: //����1
		{
			 if(recbuff!=0x6d)//����
			 {
					 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;	//
					 Laser_Length++;
					 rec_num = 2;					   
			 }				 
				else
				{
				 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;
					Laser_Length++;
				 Laser_Rec[Laser_Rright].Data_Len = 1;						
				 rec_num = 4;//���ճ�ʼ�����½���
				}				 					
		}break;			
		case 2://����2
		{
			 if(recbuff!=0x6d)//����
			 {
				 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;	//
				 Laser_Length++;
				 rec_num = 3;					 
			 }
			 else
			 {
				 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;
				 Laser_Rec[Laser_Rright].Data_Len = 2;
				 rec_num = 4;//���ճ�ʼ�����½���
				 Laser_Length++;
			 }
		
						 
		}break;

		case 3://У��1
		{			
			if(recbuff == 0x6d)//����
		 {				 
			 Laser_Rec[Laser_Rright].Data_Len = 3;
			 rec_num = 4;//���ճ�ʼ�����½���
			 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;
			 Laser_Length++;
		 }
		 else
		 {
			 rec_num = 0;//���ճ�ʼ�����½���
			 Lrecflag = 0; //������ɱ�־
			 Laser_Length = 0;
		 }			 		
		}break;
		case 4://У��2
		{			
			if(recbuff == 0x6d)//����
		 {				 
			 rec_num = 5;//���ճ�ʼ�����½���
			 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;
			 Laser_Length++;
		 }
		 else
		 {
			 rec_num = 0;//���ճ�ʼ�����½���
			 Lrecflag = 0; //������ɱ�־
			 Laser_Length = 0;
		 }			 		
		}break;
		case 5://У��3
		{			
			if(recbuff == 0x0d)//����
		 {				 
			 rec_num = 6;//���ճ�ʼ�����½���
			 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;
			 Laser_Length++;
		 }
		 else
		 {
			 rec_num = 0;//���ճ�ʼ�����½���
			 Lrecflag = 0; //������ɱ�־
			 Laser_Length = 0;
		 }			 		
		}break;
		case 6://У��4
		{			
			if(recbuff == 0x0a)//����
		 {			
			 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;				  
			 rec_num = 0;//���ճ�ʼ�����½���
			 Laser_Rright++;
			 Laser_Length=0;
			 Lrecflag = 1; //�������
			 
			 if(Laser_Rright>=(LasBufLen-1))
			 {
				Laser_Rright = 1;
				Laser_Length = 0;						 
			 }
		 }
		 else
		 {
			 rec_num = 0;//���ճ�ʼ�����½���
			 Lrecflag = 0; //������ɱ�־
			 Laser_Length = 0;
		 }			 		
		}break;
		

		}
	}
}

void USART1_IRQHandler(void)
{
  USART_ClearITPendingBit(USART1,USART_IT_RXNE); 

	recbuff=USART_ReceiveData(USART1);	//���������ݴ�
	if(Uart2_Mode == LCD)
	{
		
		switch(recflag)//��ʼֵΪ0
		{
			case 0: //֡ͷ1
			{
				 if(recbuff==0xa5)
				 {
					Uart2Buff[R_right].Star0=recbuff;
					recflag=1;
				 }
				 else 
				 {
					recflag=0;//���ճ�ʼ�����½���
					reclenth=0;
					check_temp=0;
				 }
			}break;
			case 1: //֡ͷ2
			{
				 if(recbuff==0x5a)
				 {
					Uart2Buff[R_right].Star1=recbuff;
					recflag=2;
				 }
				 else 
				 {
					recflag=0;//���ճ�ʼ�����½���
					reclenth=0;
					check_temp=0;
				 }
			}break;
			case 2: //���ݳ���
			{
				 Uart2Buff[R_right].Len=recbuff;
				 check_temp+=recbuff;
				 recflag=3;
			}break;
			case 3: //ָ��
			{
				 Uart2Buff[R_right].Comend=recbuff;
				 check_temp+=recbuff;
				 recflag=4;
			}break;
			case 4: //����
			{
				 Uart2Buff[R_right].ComData[reclenth]=recbuff;
				 reclenth++;
				 check_temp+=recbuff;
				 if(reclenth==(Uart2Buff[R_right].Len-1))
				 {
						 recflag=0;//���ճ�ʼ�����½���
						 check_temp=0;
						 reclenth=0;
						 R_right++;//���ճɹ���־��ʹ�ܡ�
						 if(R_right>=4)R_right=1;
				 }
			}break;
		}
	}
	else	
	{
		switch(rec_num)//��ʼֵΪ0
		{
		case 0: //����0
		{
			if(recbuff!=0x6d)
			{
			 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;	//
			 Laser_Length++;			
			 rec_num = 1;
			}
			else
			{
				Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;
				rec_num = 0;//���ճ�ʼ�����½���
				Lrecflag = 0; //������ɱ�־
				Laser_Length = 0;
			}
		}break;
		case 1: //����1
		{
			 if(recbuff!=0x6d)//����
			 {
					 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;	//
					 Laser_Length++;
					 rec_num = 2;					   
			 }				 
				else
				{
				 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;
					Laser_Length++;
				 Laser_Rec[Laser_Rright].Data_Len = 1;						
				 rec_num = 4;//���ճ�ʼ�����½���
				}				 					
		}break;			
		case 2://����2
		{
			 if(recbuff!=0x6d)//����
			 {
				 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;	//
				 Laser_Length++;
				 rec_num = 3;					 
			 }
			 else
			 {
				 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;
				 Laser_Rec[Laser_Rright].Data_Len = 2;
				 rec_num = 4;//���ճ�ʼ�����½���
				 Laser_Length++;
			 }
		
						 
		}break;

		case 3://У��1
		{			
			if(recbuff == 0x6d)//����
		 {				 
			 Laser_Rec[Laser_Rright].Data_Len = 3;
			 rec_num = 4;//���ճ�ʼ�����½���
			 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;
			 Laser_Length++;
		 }
		 else
		 {
			 rec_num = 0;//���ճ�ʼ�����½���
			 Lrecflag = 0; //������ɱ�־
			 Laser_Length = 0;
		 }			 		
		}break;
		case 4://У��2
		{			
			if(recbuff == 0x6d)//����
		 {				 
			 rec_num = 5;//���ճ�ʼ�����½���
			 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;
			 Laser_Length++;
		 }
		 else
		 {
			 rec_num = 0;//���ճ�ʼ�����½���
			 Lrecflag = 0; //������ɱ�־
			 Laser_Length = 0;
		 }			 		
		}break;
		case 5://У��3
		{			
			if(recbuff == 0x0d)//����
		 {				 
			 rec_num = 6;//���ճ�ʼ�����½���
			 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;
			 Laser_Length++;
		 }
		 else
		 {
			 rec_num = 0;//���ճ�ʼ�����½���
			 Lrecflag = 0; //������ɱ�־
			 Laser_Length = 0;
		 }			 		
		}break;
		case 6://У��4
		{			
			if(recbuff == 0x0a)//����
		 {			
			 Laser_Rec[Laser_Rright].Buf[Laser_Length] = recbuff ;				  
			 rec_num = 0;//���ճ�ʼ�����½���
			 Laser_Rright++;
			 Laser_Length=0;
			 Lrecflag = 1; //�������
			 
			 if(Laser_Rright>=(LasBufLen-1))
			 {
				Laser_Rright = 1;
				Laser_Length = 0;						 
			 }
		 }
		 else
		 {
			 rec_num = 0;//���ճ�ʼ�����½���
			 Lrecflag = 0; //������ɱ�־
			 Laser_Length = 0;
		 }			 		
		}break;
		

		}
	}
}

void Uart_Sendtest(u8 t1,u8 t2,u8 t3,u8 t4,u8 t5,u8 t6)
{
	u8 send_buf[6];

	send_buf[0]=t1;
	send_buf[1]=t2;
	send_buf[2]=t3;
	send_buf[3]=t4;
	send_buf[4]=t5;
	send_buf[5]=t6;
	

	for(int i=0;i<sizeof(send_buf);i++)
	{
		while( USART_GetFlagStatus(UART5,USART_FLAG_TC)!= SET);  
		//�ȴ�������ɡ�   ��� USART_FLAG_TC �Ƿ���1��    //���⺯�� P359 ����
		USART_SendData(UART5,send_buf[i]);
	}
}

/***********************************************
* �������ƣ�void SURE_REC_UART2_Analyze(void)
* �����������ж��Ƿ�Ҫ�������ڽ��յ�������
* �����������
* ���ú�������
* ���ؽ������
***********************************************/
void SURE_REC_UART2_Analyze(void)
{
	unsigned char i;
	if(R_right)			
	{	
		Uart_Sendtest(Uart2Buff[R_right-1].Star0,Uart2Buff[R_right-1].Star1,Uart2Buff[R_right-1].Len,Uart2Buff[R_right-1].Comend,Uart2Buff[R_right-1].ComData[0],Uart2Buff[R_right-1].ComData[1]);
		R_right--;
		}
	
}

