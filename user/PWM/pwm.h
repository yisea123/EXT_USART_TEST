#ifndef __PWM_H
#define __PWM_H
#include "sys.h"
#include "Sys_Init.h"
//#define Dir_Y PEout(4)
#define DirFount_Y()    Dir_Y = 1     //从零位向前走
#define DirBack_Y()     Dir_Y = 0   //回零位



extern TIM_OCInitTypeDef  TIM_OCInitStructure;
extern TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
/**************三轴方向*****************/
#define	DIR_X			PCout(5) 
#define	DIR_Y			PAout(4)
#define	DIR_Z			PBout(12)

/**************传感器*****************/
#define Proximity_3		PBin(5)	//托盘接近开关
#define Proximity_2		PBin(4) //托盘接近开关
#define Proximity_1		PBin(3) //托盘接近开关

#define Axis_Z_Up_Sensor 				PEin(8)//Z轴上限位
#define Axis_Z_Down_Sensor			PEin(10)//Z轴下限位 
#define Axis_X_Forward_Sensor		PDin(6)//X轴前限位
#define Axis_X_Backward_Sensor	PEin(14)//X轴后限位



#define PWM_PCS       23   //PWM频率=72000000/(PCS+1)*(ARR+1) 
#define Z_Acc_Time_SL 50//超低速模式加速时间
#define Z_Acc_Time_L  200//低速模式加速时间
#define Z_Acc_Time_M  1000//中速模式加速时间
#define Z_Acc_Time_H	2000//高速模式加速时间

#define X_Acc_Time_L  200//低速模式加速时间
#define X_Acc_Time_M  500//中速模式加速时间
#define X_Acc_Time_H	2000//高速模式加速时间

/*****************************X轴控制参数**************************/
#define X_DIV         					240     //驱动器设置细分
#define X_STAR_FREQ     				50    	//初始频率 提供初始频率进入外部中断
#define X_END_FREQ							50
#define X_PULSE_AFTZERO					10			//到达零点后前进的脉冲数
#define X_MPP										0.6865		//mm per pulse 毫米每脉冲0.1977
#define X_DIR_BACK							0
#define X_DIR_FRONT							1
//高速
#define X_SPEED_FREQ_H  				800   //高速频率 
#define X_HORL_PULSE_VALVE_H   	2185  //高速总脉冲数阀值，用来分辨是否高速行进
//中速
#define X_SPEED_FREQ_M  				300   //目标频率 
#define X_HORL_PULSE_VALVE_M   	1456  //中速总脉冲数阀值，用来分辨是否中速行进
//低速
#define X_SPEED_FREQ_L					200    //低速频率 
#define X_HORL_PULSE_VALVE_L  	728  	//中速总脉冲数阀值，用来分辨是否中速行进
#define	X_Zero_Pluse						46		//X轴到达零点后前进脉冲数



/*****************************Z轴控制参数**************************/
#define Z_DIV         					120     //驱动器设置细分
#define Z_STAR_FREQ     				50    	//初始频率 提供初始频率进入外部中断
#define Z_END_FREQ							50
#define Z_PULSE_AFTZERO					10			//到达零点后前进的脉冲数
#define Z_MPP										0.40438		//mm per pulse 毫米每脉冲
#define Z_DIR_FRONT							1
#define Z_DIR_BACK							0
#define Z_ZeroUp_Pluse					200//Z轴归位上升脉冲数

//高速
#define Z_SPEED_FREQ_H  				800  	//高速频率  
#define Z_HORL_PULSE_VALVE_H   	3709  //高速总脉冲数阀值，用来分辨是否高速行进
//中速
#define Z_SPEED_FREQ_M 					500   //目标频率 � 
#define Z_HORL_PULSE_VALVE_M   	2472  //中速总脉冲数阀值，用来分辨是否中速行进
//低速
#define Z_SPEED_FREQ_L  				200   //低速频率
#define Z_HORL_PULSE_VALVE_L    1236	//低速总脉冲数阀值，用来分辨是否高速行进
//超低速用来托举
#define Z_SPEED_FREQ_SL          60
#define Z_SLDISTANCE						50
#define Z_HORL_PULSE_VALVE_SL   625


/*****************************Y轴控制参数**************************/
#define Y_DIV         					120     //驱动器设置细分
#define Y_STAR_FREQ     				100    	//初始频率 提供初始频率进入外部中断
#define Y_END_FREQ							100
#define Y_DIR_LEFT							1//Y轴行走的方向为左
#define Y_DIR_RIGHT							0//Y轴行走的方向为右
#define Y_LeftLim_MorePluse					1780//Y轴从原点往左走的脉冲数	
#define Y_LeftLim_MidPluse					1743//第一次上电行走脉冲数
#define Y_LeftLim_LessPluse					1735//Y轴从原点往左走的脉冲数	
#define Y_RightLim_MorePluse				1775//Y轴从原点往右走的脉冲数
#define Y_RightLim_MidPluse				1748//第一次上电行走脉冲数
#define Y_RightLim_LessPluse				1740//Y轴从原点往右走的脉冲数
#define Y_RightZero_Pluse				30//Y轴从左往右回零继续行走的脉冲数
#define Y_LeftZero_Pluse				40//Y轴从右往左回零继续行走的脉冲数

//高速
#define Y_SPEED_FREQ  				400   	//高速频率 
#define Y_HORL_PULSE_VALVE_H   	3039  //高速总脉冲数阀值，用来分辨是否高速行进
#define Y_ACC_TIME						500
#define Y_MPP								0.09

#define AXIS_X 0
#define AXIS_Z 1
#define AXIS_Y 2


typedef struct 
{
  u8 InCtrl_Flag;           	//控制中标志 0:不受控 1:短距离，不加减速，慢速模式 2:长距离，加减速，快速模式
  u32 NowPulse;               //当前已走脉冲数
  float NowFreq;              //当前频率
  float NowACC;
  u32 Target_Pulse;           //目标脉冲数    
  u32 Timer_Cnt;              //当前已走时间
  u32 PulsePoint[7];          //过程时间点的脉冲数，分别为加加速完成时间点，匀加速完成时间点，减加速完成时间点
  u32 TimerPoint[7];          //过程时间点
  int32_t YCoordinate;        //Y轴坐标
  float FreqPoint[7];        	//加速过程时间点频率
  u16 Time_Delta;             //与上个时间点的时间差
  u8  SpeedChange_Stage;      //加减速过程3个阶段 1：加速过程 2：减速过程
	u16 Target_Fre;							//目标频率
	float Jerk_Speed;						//加加速度
	float Acc_Speed;							//匀速加速度
  u32 Coordinate;							//当前坐标
	bool Dir;
	bool	CtrlEnd_Flag;
	float Stage4_Acc;
	float Stage1_Acc;
}TYPE_StepMotor;

typedef struct
{
	u8 command;//转工位指令
	u8 tray_position;//托盘属性
	u8 tray_stage;//当前托盘位置，
	u8 Put_Box_Stage;//放箱动作阶段
	u8 Get_Box_Stage;//取箱动作阶段
	u8 XZRun_Stage;//XZ运动嵌套阶段
	u8 XZRUN_Status_Change;//XZ运动状态改变
	u8 Tray_PutBox_Stage;//托盘放箱嵌套阶段
	u8 Tray_PutBox_Status_Change;//托盘放箱状态改变
	u8 Tray_GetBox_Stage;//托盘取箱阶段
	u8 Tray_GetBox_Status_Change;//托盘取箱状态改变
	bool end_flag;//嵌套动作结束标志
	bool Get_Box_Start_Flag;//抓箱指令开始标志
	bool Put_Box_Start_Flag;//放箱指令开始标志
	bool Move_Alone;//单点运动状态
	u16 Target_X;//X轴坐标，单位mm
	u16 Target_Z;//Z轴坐标，单位mm
	u16 Comend;
	u8 Speed_Grade;//速度档位
	u16 Step_Grade;//步长档位
	u16 PlatZ_Axis;//托架Z坐标
	u16 PlatX_Axis;//托架Z坐标
}TYPEDEF_ACTION;



extern TYPEDEF_ACTION Action;
extern TYPE_StepMotor Axis_X;
extern TYPE_StepMotor Axis_Z;
extern TYPE_StepMotor Axis_Y;
extern u8 Motor_CtrlOver_Flag;		//电机控制结束标志，此标志置1后，上传结束控制应答
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
void Uniform_Speed_Advance(u32 Tar_Pluse,u8 Axis,bool dir);//X轴水平匀速前进
void 	X_Uniform_Speed_Back(u32 Tar_Pluse);
u32 PWMCtrl_ARRCount(u32 pcs, float Fre);


#endif
