#ifndef __ACTIONSTATUS_H
#define __ACTIONSTATUS_H
#include "sys.h"
#include "Sys_Init.h"


#define Plat_Axis									240//托架Z轴坐标
#define AxisZ_Float_Disance				15//货架浮动距离，单位mm
#define AxisZ_PutBoxFloat_Disance 70		//取箱回来时，托盘位于托架上方的距离
#define AxisZ_UpDown_Pluse				105//托盘上升下降脉冲数
#define AxisZ_UpDownMore_Pluse		200//托盘上升下降脉冲数

#define ActionDelay		500//每个动作结束的延时时间

typedef struct
{
	bool XYZRET_Status_Change;
	u8 XYZ_Ret_Stage;
	bool Over_Flag;
	bool Start_Flag;
	bool X_Return_Flag;
	bool Z_Return_Flag;
}TYPEDEF_BACKZERO;
extern TYPEDEF_BACKZERO XYZ_To_Zero;
void Get_Box(u16 AXIS_X_Mm,u16 AXIS_Z_Mm);
void Put_Box(u16 AXIS_X_Mm,u16 AXIS_Z_Mm);
void Axis_Move_Alone(u8 Axis ,bool Dir);
void Tray_Get_Box(bool Axis_Y_Dir,u32 UpDown_Pluse);
void Tray_Put_Box(bool Axis_Y_Dir,u32 UpDown_Pluse);
void XYZ_BackZero(void);
void Auto_Rest(void);
#endif
