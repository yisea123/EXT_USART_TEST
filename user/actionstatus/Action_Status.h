#ifndef __ACTIONSTATUS_H
#define __ACTIONSTATUS_H
#include "sys.h"
#include "Sys_Init.h"


#define Plat_Axis									240//�м�Z������
#define AxisZ_Float_Disance				15//���ܸ������룬��λmm
#define AxisZ_PutBoxFloat_Disance 70		//ȡ�����ʱ������λ���м��Ϸ��ľ���
#define AxisZ_UpDown_Pluse				105//���������½�������
#define AxisZ_UpDownMore_Pluse		200//���������½�������

#define ActionDelay		500//ÿ��������������ʱʱ��

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
