#ifndef __PWM_H
#define __PWM_H
#include "sys.h"
#include "Sys_Init.h"
//#define Dir_Y PEout(4)
#define DirFount_Y()    Dir_Y = 1     //����λ��ǰ��
#define DirBack_Y()     Dir_Y = 0   //����λ



extern TIM_OCInitTypeDef  TIM_OCInitStructure;
extern TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
/**************���᷽��*****************/
#define	DIR_X			PCout(5) 
#define	DIR_Y			PAout(4)
#define	DIR_Z			PBout(12)

/**************������*****************/
#define Proximity_3		PBin(5)	//���̽ӽ�����
#define Proximity_2		PBin(4) //���̽ӽ�����
#define Proximity_1		PBin(3) //���̽ӽ�����

#define Axis_Z_Up_Sensor 				PEin(8)//Z������λ
#define Axis_Z_Down_Sensor			PEin(10)//Z������λ 
#define Axis_X_Forward_Sensor		PDin(6)//X��ǰ��λ
#define Axis_X_Backward_Sensor	PEin(14)//X�����λ



#define PWM_PCS       23   //PWMƵ��=72000000/(PCS+1)*(ARR+1) 
#define Z_Acc_Time_SL 50//������ģʽ����ʱ��
#define Z_Acc_Time_L  200//����ģʽ����ʱ��
#define Z_Acc_Time_M  1000//����ģʽ����ʱ��
#define Z_Acc_Time_H	2000//����ģʽ����ʱ��

#define X_Acc_Time_L  200//����ģʽ����ʱ��
#define X_Acc_Time_M  500//����ģʽ����ʱ��
#define X_Acc_Time_H	2000//����ģʽ����ʱ��

/*****************************X����Ʋ���**************************/
#define X_DIV         					240     //����������ϸ��
#define X_STAR_FREQ     				50    	//��ʼƵ�� �ṩ��ʼƵ�ʽ����ⲿ�ж�
#define X_END_FREQ							50
#define X_PULSE_AFTZERO					10			//��������ǰ����������
#define X_MPP										0.6865		//mm per pulse ����ÿ����0.1977
#define X_DIR_BACK							0
#define X_DIR_FRONT							1
//����
#define X_SPEED_FREQ_H  				800   //����Ƶ�� 
#define X_HORL_PULSE_VALVE_H   	2185  //��������������ֵ�������ֱ��Ƿ�����н�
//����
#define X_SPEED_FREQ_M  				300   //Ŀ��Ƶ�� 
#define X_HORL_PULSE_VALVE_M   	1456  //��������������ֵ�������ֱ��Ƿ������н�
//����
#define X_SPEED_FREQ_L					200    //����Ƶ�� 
#define X_HORL_PULSE_VALVE_L  	728  	//��������������ֵ�������ֱ��Ƿ������н�
#define	X_Zero_Pluse						46		//X�ᵽ������ǰ��������



/*****************************Z����Ʋ���**************************/
#define Z_DIV         					120     //����������ϸ��
#define Z_STAR_FREQ     				50    	//��ʼƵ�� �ṩ��ʼƵ�ʽ����ⲿ�ж�
#define Z_END_FREQ							50
#define Z_PULSE_AFTZERO					10			//��������ǰ����������
#define Z_MPP										0.40438		//mm per pulse ����ÿ����
#define Z_DIR_FRONT							1
#define Z_DIR_BACK							0
#define Z_ZeroUp_Pluse					200//Z���λ����������

//����
#define Z_SPEED_FREQ_H  				800  	//����Ƶ��  
#define Z_HORL_PULSE_VALVE_H   	3709  //��������������ֵ�������ֱ��Ƿ�����н�
//����
#define Z_SPEED_FREQ_M 					500   //Ŀ��Ƶ�� � 
#define Z_HORL_PULSE_VALVE_M   	2472  //��������������ֵ�������ֱ��Ƿ������н�
//����
#define Z_SPEED_FREQ_L  				200   //����Ƶ��
#define Z_HORL_PULSE_VALVE_L    1236	//��������������ֵ�������ֱ��Ƿ�����н�
//�����������о�
#define Z_SPEED_FREQ_SL          60
#define Z_SLDISTANCE						50
#define Z_HORL_PULSE_VALVE_SL   625


/*****************************Y����Ʋ���**************************/
#define Y_DIV         					120     //����������ϸ��
#define Y_STAR_FREQ     				100    	//��ʼƵ�� �ṩ��ʼƵ�ʽ����ⲿ�ж�
#define Y_END_FREQ							100
#define Y_DIR_LEFT							1//Y�����ߵķ���Ϊ��
#define Y_DIR_RIGHT							0//Y�����ߵķ���Ϊ��
#define Y_LeftLim_MorePluse					1780//Y���ԭ�������ߵ�������	
#define Y_LeftLim_MidPluse					1743//��һ���ϵ�����������
#define Y_LeftLim_LessPluse					1735//Y���ԭ�������ߵ�������	
#define Y_RightLim_MorePluse				1775//Y���ԭ�������ߵ�������
#define Y_RightLim_MidPluse				1748//��һ���ϵ�����������
#define Y_RightLim_LessPluse				1740//Y���ԭ�������ߵ�������
#define Y_RightZero_Pluse				30//Y��������һ���������ߵ�������
#define Y_LeftZero_Pluse				40//Y������������������ߵ�������

//����
#define Y_SPEED_FREQ  				400   	//����Ƶ�� 
#define Y_HORL_PULSE_VALVE_H   	3039  //��������������ֵ�������ֱ��Ƿ�����н�
#define Y_ACC_TIME						500
#define Y_MPP								0.09

#define AXIS_X 0
#define AXIS_Z 1
#define AXIS_Y 2


typedef struct 
{
  u8 InCtrl_Flag;           	//�����б�־ 0:���ܿ� 1:�̾��룬���Ӽ��٣�����ģʽ 2:�����룬�Ӽ��٣�����ģʽ
  u32 NowPulse;               //��ǰ����������
  float NowFreq;              //��ǰƵ��
  float NowACC;
  u32 Target_Pulse;           //Ŀ��������    
  u32 Timer_Cnt;              //��ǰ����ʱ��
  u32 PulsePoint[7];          //����ʱ�������������ֱ�Ϊ�Ӽ������ʱ��㣬�ȼ������ʱ��㣬���������ʱ���
  u32 TimerPoint[7];          //����ʱ���
  int32_t YCoordinate;        //Y������
  float FreqPoint[7];        	//���ٹ���ʱ���Ƶ��
  u16 Time_Delta;             //���ϸ�ʱ����ʱ���
  u8  SpeedChange_Stage;      //�Ӽ��ٹ���3���׶� 1�����ٹ��� 2�����ٹ���
	u16 Target_Fre;							//Ŀ��Ƶ��
	float Jerk_Speed;						//�Ӽ��ٶ�
	float Acc_Speed;							//���ټ��ٶ�
  u32 Coordinate;							//��ǰ����
	bool Dir;
	bool	CtrlEnd_Flag;
	float Stage4_Acc;
	float Stage1_Acc;
}TYPE_StepMotor;

typedef struct
{
	u8 command;//ת��λָ��
	u8 tray_position;//��������
	u8 tray_stage;//��ǰ����λ�ã�
	u8 Put_Box_Stage;//���䶯���׶�
	u8 Get_Box_Stage;//ȡ�䶯���׶�
	u8 XZRun_Stage;//XZ�˶�Ƕ�׽׶�
	u8 XZRUN_Status_Change;//XZ�˶�״̬�ı�
	u8 Tray_PutBox_Stage;//���̷���Ƕ�׽׶�
	u8 Tray_PutBox_Status_Change;//���̷���״̬�ı�
	u8 Tray_GetBox_Stage;//����ȡ��׶�
	u8 Tray_GetBox_Status_Change;//����ȡ��״̬�ı�
	bool end_flag;//Ƕ�׶���������־
	bool Get_Box_Start_Flag;//ץ��ָ�ʼ��־
	bool Put_Box_Start_Flag;//����ָ�ʼ��־
	bool Move_Alone;//�����˶�״̬
	u16 Target_X;//X�����꣬��λmm
	u16 Target_Z;//Z�����꣬��λmm
	u16 Comend;
	u8 Speed_Grade;//�ٶȵ�λ
	u16 Step_Grade;//������λ
	u16 PlatZ_Axis;//�м�Z����
	u16 PlatX_Axis;//�м�Z����
}TYPEDEF_ACTION;



extern TYPEDEF_ACTION Action;
extern TYPE_StepMotor Axis_X;
extern TYPE_StepMotor Axis_Z;
extern TYPE_StepMotor Axis_Y;
extern u8 Motor_CtrlOver_Flag;		//������ƽ�����־���˱�־��1���ϴ���������Ӧ��
extern u8 NowAngle_A;
extern u8 NowAngle_B;
extern bool x_stop_flag;
extern bool z_stop_flag ;

void PWM_Init(void);
void PWM_Set_X(u32 Arr,u32 Psc);
void PWM_Set_Y(u32 Arr,u32 Psc);
void PWM_Set_Z(u32 Arr,u32 Psc);
void Motor_MoveToPosition(u16 AXIS_X_Mm,u16 AXIS_Z_Mm);
void StepMotorCtrl_Pulse(u32 Target , u8 AXIS ,bool Dir);
void StepMotorCtrl_Zero_Pulse(u32 Target ,bool Dir);
void Motor_BackToZero(u8 Axis);
void Motor_Y_BackToLeft(void);
void Tray_Limit_Contr(void);
void Axis_Ultra_Limit(void);
void Uniform_Speed_Advance(u32 Tar_Pluse,u8 Axis,bool dir);//X��ˮƽ����ǰ��
void 	X_Uniform_Speed_Back(u32 Tar_Pluse);
u32 PWMCtrl_ARRCount(u32 pcs, float Fre);


#endif