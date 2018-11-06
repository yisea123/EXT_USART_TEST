#include "Auto_Locate.h"

u16 Distance_Detection(void);
u8 Auto_Position_Buff[8] ;//���ص�ǰ������Ϣ
u16 Calc_Z_Distance(u8 Z_Cnt);
u8 rec_num;

/*u16 X_Cal_Uniform_Dis(int);*/
TYPEDEF_ARRARY X_Buf;
TYPEDEF_ARRARY Z_Buf;
TYPEDEF_UART2 Laser_Rec[LasBufLen];//���ܻ���
int X_Mutation_Distance = 25;//ˮƽͻ�����
int Z_Mutation_Distance = 25;//��ֱͻ�����
u8 X_Mutation_Judge(int Temp_Dis);//X��ͻ����
u8 Z_Mutation_Judge(int Temp_Dis);//Z��ͻ����
void Auto_Loate_Stop(void);
void Return_Coordinate(void);
u8 Laser_Length;
u8 Lrecflag;
int Read_Distance(void);

u8 Laser_Rright=0;//���ܻ�������

u8 Current_X=0;
u8 Current_Y=0;
u8 Current_Z=0;
int test(void);
TYPEDEF_AUTOLOCATE Auto_AdjustX =
{
	.Auto_Locate_Status_Change=1,
	.Over_Flag=0,
	.Start_Flag=0,
	.Back_Zero_Flag = 0,
	.Auto_Locate_Stage=1,
	.X_Cnt=1,
	.Y_Cnt=0,
	.Z_Cnt=1,
	.Compare_Cnt = 0
};

TYPEDEF_AUTOLOCATE Auto_AdjustZ =
{
	.Auto_Locate_Status_Change=1,
	.Over_Flag=0,
	.Start_Flag=0,
	.Back_Zero_Flag = 0,
	.Auto_Locate_Stage=1,
	.X_Cnt=1,
	.Y_Cnt=0,
	.Z_Cnt=1,
	.Compare_Cnt = 0
};
void Auto_LocateX(void)
{
	if(Auto_AdjustX.Start_Flag == 1)
	{
		int temp_dis;
		int result;
		if(Auto_AdjustX.Auto_Locate_Stage == 1)//��λ״̬��
		{
			if(Auto_AdjustX.Auto_Locate_Status_Change == 1)
			{
				Auto_AdjustX.Auto_Locate_Status_Change = 0;
				//Auto_Rest();//��λ��ԭ��
				Motor_BackToZero(AXIS_X);
			}
			if(Auto_AdjustX.Back_Zero_Flag == 1)
			{
				Auto_AdjustX.Back_Zero_Flag = 0;
				Auto_AdjustX.Auto_Locate_Status_Change = 1;
				Auto_AdjustX.Auto_Locate_Stage++;//������һ���׶�
			}
		}
		else if(Auto_AdjustX.Auto_Locate_Stage == 2)//ͻ����״̬��
		{
			if(Auto_AdjustX.Auto_Locate_Status_Change == 1)//��λ״̬��
			{
				Auto_AdjustX.Auto_Locate_Status_Change = 0;
				Uniform_Speed_Advance(50000,AXIS_X,X_DIR_FRONT);//X������ǰ��
			}
			temp_dis = Read_Distance();
			if(temp_dis==0xff)return;			
				result = X_Mutation_Judge(temp_dis);
			if(result==0xff)//�����ͻ��
			{
				//Action_Stop();
				Axis_X.InCtrl_Flag = 0;//���ֹͣ
				TIM_Cmd(TIM2, DISABLE);
				Axis_Y.InCtrl_Flag = 0;//���ֹͣ
				TIM_Cmd(TIM3, DISABLE);
				Axis_Z.InCtrl_Flag = 0;//���ֹͣ
				TIM_Cmd(TIM4, DISABLE);
				Auto_AdjustX.X_Cnt++;
				if(Auto_AdjustX.X_Cnt == 2)
				{
				Auto_AdjustX.Auto_Locate_Stage = 4;
				Auto_AdjustX.Auto_Locate_Status_Change = 1;
				return;
				}
				Auto_AdjustX.Auto_Locate_Status_Change = 1;
				Auto_AdjustX.Auto_Locate_Stage++;//������һ���׶�
				delay_ms(500);
				delay_ms(500);
			}
			else
			{
				return;
			}
		}
		else if(Auto_AdjustX.Auto_Locate_Stage ==3)//������λ
		{
			if(Auto_AdjustX.Auto_Locate_Status_Change == 1)
			{
				Auto_AdjustX.Auto_Locate_Status_Change = 0;
				Uniform_Speed_Advance((22/X_MPP),AXIS_X,X_DIR_BACK);//x�����ˮƽ10
			}
			if(Axis_X.InCtrl_Flag == 0)
			{
				delay_ms(500);
				delay_ms(500);				
				Return_Coordinate();
				Auto_AdjustX.Auto_Locate_Status_Change = 1;
				Auto_AdjustX.Auto_Locate_Stage++;//������һ���׶�
			}
		}
		
		else if(Auto_AdjustX.Auto_Locate_Stage ==4)//Խ��ä���׶�			
		{
			if(Auto_AdjustX.Auto_Locate_Status_Change == 1)//��λ״̬��
			{
//				Auto_AdjustX.X_Cnt++;
				if(Auto_AdjustX.X_Cnt>5)//X���Զ���λ��ϻع�ԭ�������һ���Զ���λ
				{
					Uart_Send(0,CMD_AUTOLOC,Local_Ip,0x61,0XA0,0);//���ؽ�����Ϣ�ɹ�
					Auto_Loate_Stop();
					X_Uniform_Speed_Back(50000);
					return;
				}
				Auto_AdjustX.Auto_Locate_Status_Change = 0;
				Uniform_Speed_Advance(200,AXIS_X,X_DIR_FRONT);//X������ǰ��
			}
			if(Axis_X.InCtrl_Flag == 0)
			{
				Auto_AdjustX.Auto_Locate_Stage = 2;//���½���ڶ��׶Σ����Ŷ�λ��һ��
				Auto_AdjustX.Auto_Locate_Status_Change = 1;
				return;
			}
		}
		else
		{
			Auto_AdjustX.Auto_Locate_Stage = 1;
			Auto_AdjustX.Start_Flag = 0;
			Auto_AdjustX.X_Cnt = 1;
			Auto_AdjustX.Z_Cnt = 1;
			Auto_AdjustX.Y_Cnt = 0;
		}
		
		
	}
}

void Auto_LocateZ(void)
{
	if(Auto_AdjustZ.Start_Flag == 1)
	{
		int temp_dis;
		int result;
		if(Auto_AdjustZ.Auto_Locate_Stage == 1)//��λ״̬��
			{
				if(Auto_AdjustZ.Auto_Locate_Status_Change == 1)
				{
					Auto_AdjustZ.Auto_Locate_Status_Change = 0;
					Motor_BackToZero(AXIS_Z);
				}
				if(Auto_AdjustZ.Back_Zero_Flag == 1)
				{
					Auto_AdjustZ.Back_Zero_Flag = 0;
					Auto_AdjustZ.Auto_Locate_Status_Change = 1;
					Auto_AdjustZ.Auto_Locate_Stage++;
				}
			}	
			else if(Auto_AdjustZ.Auto_Locate_Stage == 2)//���ͻ��
			{
				if(Auto_AdjustZ.Auto_Locate_Status_Change == 1)
				{
					Auto_AdjustZ.Auto_Locate_Status_Change = 0;
					Uniform_Speed_Advance(50000,AXIS_Z,Z_DIR_FRONT);//X������ǰ��
				}
			temp_dis = Read_Distance();
			if(temp_dis==0xff)return;//�޾����Ӧ			
				result = Z_Mutation_Judge(temp_dis);
			if(result==0xff)//�����ͻ��
			{
				//Action_Stop();
					
					Auto_AdjustZ.Z_Cnt++;
					if(Auto_AdjustZ.Z_Cnt==6)//����㲻���ж�λ
					{
						Auto_AdjustZ.Auto_Locate_Stage = 4;
						Auto_AdjustZ.Auto_Locate_Status_Change = 1;
						return;
					}
				Axis_X.InCtrl_Flag = 0;
				TIM_Cmd(TIM2, DISABLE);
				Axis_Y.InCtrl_Flag = 0;
				TIM_Cmd(TIM3, DISABLE);
				Axis_Z.InCtrl_Flag = 0;
				TIM_Cmd(TIM4, DISABLE);
				
				Auto_AdjustZ.Auto_Locate_Status_Change = 1;
				Auto_AdjustZ.Auto_Locate_Stage++;//������һ���׶�
				delay_ms(500);
				delay_ms(500);
			}
			else
			{
				return;
			}
				
			}
			
			else if(Auto_AdjustZ.Auto_Locate_Stage == 3)//Z�����ˮƽ
			{
				if(Auto_AdjustZ.Auto_Locate_Status_Change == 1)
				{
					Auto_AdjustZ.Auto_Locate_Status_Change = 0;
					Uniform_Speed_Advance((5/Z_MPP),AXIS_Z,Z_DIR_BACK);//Z�����ˮƽ10
				}
				if(Axis_Z.InCtrl_Flag == 0)
				{
					delay_ms(500);
					delay_ms(500);
					Return_Coordinate();//����������Ϣ
					Auto_AdjustZ.Auto_Locate_Status_Change = 1;
					Auto_AdjustZ.Auto_Locate_Stage++;//������һ���׶�
				}
			}
			else if(Auto_AdjustZ.Auto_Locate_Stage == 4)//Խ��ä���׶�
			{
				if(Auto_AdjustZ.Auto_Locate_Status_Change == 1)//��λ״̬��
				{					
//					Auto_AdjustZ.Z_Cnt++;
					if(Auto_AdjustZ.Z_Cnt>7)//X���Զ���λ��ϻع�ԭ�������һ���Զ���λ
					{
						Uart_Send(0,CMD_AUTOLOC,Local_Ip,0x61,0XA1,0);//���ؽ�����Ϣ�ɹ�
						Auto_Loate_Stop();
						Uniform_Speed_Advance(50000,AXIS_Z,Z_DIR_BACK);//Z���˻����
						return;
					}
					Auto_AdjustZ.Auto_Locate_Status_Change = 0;
					Uniform_Speed_Advance(180,AXIS_Z,Z_DIR_FRONT);//Z������ǰ��
				}
			if(Axis_Z.InCtrl_Flag == 0)//ä��Խ���������½���ڶ��׶�
			{
				Auto_AdjustZ.Auto_Locate_Stage = 2;//���½���ڶ��׶Σ����Ŷ�λ��һ��
				Auto_AdjustZ.Auto_Locate_Status_Change = 1;
				return;
			}
			}
			else
			{
			}
	}
}

/*static u8 Traverse_XYZ(u8 Y_Cnt,u8 Z_Cnt ,u8 X_Cnt)
{
	u16 Z_Run;
	if (Auto_AdjustX.X_Cnt > 5)//X������꣬Z�������һ��
	{
		++Auto_AdjustX.Z_Cnt;
		Auto_AdjustX.X_Cnt = 1;
		Auto_AdjustX.Z_Cnt = Z_Cnt;
	}	
	
	Auto_AdjustX.X_Cnt = X_Cnt;//����
	Auto_AdjustX.Z_Cnt = Z_Cnt;//����
	Auto_AdjustX.Y_Cnt = Y_Cnt;//����
	Z_Run = Calc_Z_Distance(Z_Cnt);//����Ŀ��Z�����
	
	Current_X=Auto_AdjustX.X_Cnt;//����λ��
	Current_Y=Auto_AdjustX.Y_Cnt;//
	Current_Z=Auto_AdjustX.Z_Cnt;//
	
	if(Auto_AdjustX.X_Cnt ==1 && Auto_AdjustX.Z_Cnt == 10 && Auto_AdjustX.Y_Cnt == 1)//��������
	{
		Auto_AdjustX.X_Cnt = 1;
		Auto_AdjustX.Z_Cnt = 1;
		Auto_AdjustX.Y_Cnt = 0;
		return 1;
	}	
	Motor_MoveToPosition(X_Cnt*412,Z_Run);//�ƶ���Ŀ�����
	
	++Auto_AdjustX.X_Cnt;//������һ��X��	
	if(Auto_AdjustX.X_Cnt > 5 && Auto_AdjustX.Z_Cnt == 9&&Auto_AdjustX.Y_Cnt==0)
	{
		Auto_AdjustX.X_Cnt = 1;
		Auto_AdjustX.Z_Cnt = 1;
		Auto_AdjustX.Y_Cnt++;
	}

	return 0;
}*/

int test()
{
//	return 1;
//	if(Auto_AdjustZ.Auto_Locate_Stage == 1)
//	{
//		
//	}
}

u8 X_Mutation_Judge(int Temp_Dis)//X��ͻ����
{
	u8 equal_cnt = 0;
	X_Buf.Distance_Arrary[Auto_AdjustX.Compare_Cnt] = Temp_Dis;
	Auto_AdjustX.Compare_Cnt++;
	if(Auto_AdjustX.Compare_Cnt>=2)
	{
		Auto_AdjustX.Compare_Cnt = 0;//�������¸���
		for(int j =0;j<2;j++)
		{			
			if((X_Mutation_Distance -10)<X_Buf.Distance_Arrary[j]&&X_Buf.Distance_Arrary[j]<(X_Mutation_Distance +40))
			{
				equal_cnt++;
			}
		}
		if(equal_cnt>=1)
		{
			return 0xff;//����ͻ��
		}
		else 	
			return 0;
	}
		else
		{
			return 0 ;
		}
}

u8 Z_Mutation_Judge(int Temp_Dis)//Z��ͻ����
{
	u8 equal_cnt = 0;
	Z_Buf.Distance_Arrary[Auto_AdjustZ.Compare_Cnt] = Temp_Dis;
	Auto_AdjustZ.Compare_Cnt++;
	if(Auto_AdjustZ.Compare_Cnt>=4)
	{
		Auto_AdjustZ.Compare_Cnt = 0;//�������¸���
		for(int j =0;j<4;j++)
		{			
			if((Z_Mutation_Distance -5)<Z_Buf.Distance_Arrary[j]&&Z_Buf.Distance_Arrary[j]<(Z_Mutation_Distance +40))
			{
				equal_cnt++;
			}
		}
		if(equal_cnt>=3)
		{
			return 0xff;//����ͻ��
		}
		else 
			return 0;
	}
		else
		{
			return 0 ;
		}
}

/*u16 X_Cal_Uniform_Dis(int Temp_Dis)
{
	static u32 sum=0;
	u16 Aver_Dis;
	static u8 equal_cnt = 0;
	X_Buf.Distance_Arrary[Auto_AdjustX.Compare_Cnt] = Temp_Dis;
	sum+=Temp_Dis;
	Auto_AdjustX.Compare_Cnt++;
	if(Auto_AdjustX.Compare_Cnt>=16)
	{
		Auto_AdjustX.Compare_Cnt = 0;
		Aver_Dis = sum>>4;
		sum = 0;
		for(int j =0;j<16;j++)
		{
			
			if(((Aver_Dis -5)<X_Buf.Distance_Arrary[j])&&(X_Buf.Distance_Arrary[j]<(Aver_Dis +5)))
			{
				equal_cnt++;

			}
		}
			if(equal_cnt==16)
			{
				equal_cnt = 0;
				return Aver_Dis;
			}
			else 
			{
				equal_cnt = 0;
				Auto_AdjustX.Compare_Cnt = 0;
				sum = 0;
				return 0;
			}
		
	}
	else
	{
		
		return 0;
	}
}*/

int Read_Distance(void)
{
	int temp_distance;
	if(Lrecflag)
	{
		Lrecflag = 0;
		switch (Laser_Rec[Laser_Rright-1].Data_Len)
		{
			case 1:
			{
				Laser_Rec[LasBufLen-1].distance_data[0] = Laser_Rec[Laser_Rright-1].Buf[0];;
				Laser_Rec[LasBufLen-1].distance_data[1] = 0x00;				
				Laser_Rec[LasBufLen-1].distance_data[2] = 0x00;
				temp_distance = Laser_Rec[LasBufLen-1].distance_data[0]-0x30;
			}break;
			case 2:
			{
				Laser_Rec[LasBufLen-1].distance_data[0] = Laser_Rec[Laser_Rright-1].Buf[0];
				Laser_Rec[LasBufLen-1].distance_data[1] = Laser_Rec[Laser_Rright-1].Buf[1];
				Laser_Rec[LasBufLen-1].distance_data[2] = 0x00;
				temp_distance = (Laser_Rec[LasBufLen-1].distance_data[0]-0x30)*10+(Laser_Rec[LasBufLen-1].distance_data[1]-0x30);
			}break;
			case 3:
			{
				Laser_Rec[LasBufLen-1].distance_data[0] = Laser_Rec[Laser_Rright-1].Buf[0];
				Laser_Rec[LasBufLen-1].distance_data[1] = Laser_Rec[Laser_Rright-1].Buf[1];
				Laser_Rec[LasBufLen-1].distance_data[2] = Laser_Rec[Laser_Rright-1].Buf[2];
				temp_distance =(Laser_Rec[LasBufLen-1].distance_data[0]-0x30)*100+(Laser_Rec[LasBufLen-1].distance_data[1]-0x30)*10+
				(Laser_Rec[LasBufLen-1].distance_data[2]-0x30);
			}break;
		}
		Laser_Rright--;
		return temp_distance;
	}
	else
	{
		return 0xff;
	}

}

/*
void asdasd(void)
{
	int temp_dis;
	u16 result;
	temp_dis = Read_Distance();
	if(temp_dis == 0xff)return;
	result = X_Cal_Uniform_Dis(temp_dis);
	if(result !=0)
	{
		result=result;
		result=result;
	}
}*/

void Auto_Loate_Stop(void)
{
	Auto_AdjustX.Auto_Locate_Status_Change = 1;
	Auto_AdjustX.Over_Flag = 1;
	Auto_AdjustX.Start_Flag = 0;
	Auto_AdjustX.Auto_Locate_Stage = 1;
	Auto_AdjustX.X_Cnt = 1;
	Auto_AdjustX.Y_Cnt = 0;
	Auto_AdjustX.Z_Cnt = 1;
	Auto_AdjustX.Compare_Cnt = 0;
	Auto_AdjustX.Back_Zero_Flag = 0;
	
	Auto_AdjustZ.Auto_Locate_Status_Change = 1;
	Auto_AdjustZ.Over_Flag = 1;
	Auto_AdjustZ.Start_Flag = 0;
	Auto_AdjustZ.Auto_Locate_Stage = 1;
	Auto_AdjustZ.X_Cnt = 1;
	Auto_AdjustZ.Y_Cnt = 0;
	Auto_AdjustZ.Z_Cnt = 1;
	Auto_AdjustZ.Compare_Cnt = 0;
	Auto_AdjustZ.Back_Zero_Flag = 0;
}

void Return_Coordinate()
{
	Current_Position_Buff[0] = ((Axis_X.Coordinate*X_MPP)+0.5)/256;//X����
	Current_Position_Buff[1] = (u8)(((Axis_X.Coordinate*X_MPP)+0.5)/1)%256;//X����
	Current_Position_Buff[2] = ((Axis_Z.Coordinate*Z_MPP)+0.5)/256;//Z����
	Current_Position_Buff[3] = (u8)(((Axis_Z.Coordinate*Z_MPP)+0.5)/1)%256;//Z����	
	Current_Position_Buff[4] = 0;
	Current_Position_Buff[5] = 0;
	Current_Position_Buff[6] = 0;
	Current_Position_Buff[7] = 0;
	Uart_Send(1,0X08,Local_Ip,Prot_Cfg,0,Current_Position_Buff);//��������
}
