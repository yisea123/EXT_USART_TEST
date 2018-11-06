#ifndef __AUTO_LOCATE
#define __AUTO_LOCATE
#include "sys.h"
#include "Sys_Init.h"

#define LasBufLen  20
#define Auto_Locate_X 0x00
#define Auto_Locate_Z 0x01
typedef struct
{
	bool Auto_Locate_Status_Change;	
	bool Over_Flag;
	bool Start_Flag;	
	bool Back_Zero_Flag;
	u8 Auto_Locate_Stage;
	u8 X_Cnt;
	u8 Y_Cnt;
	u8 Z_Cnt;
	u8 Compare_Cnt;

}TYPEDEF_AUTOLOCATE;


typedef struct{
	int Distance_Arrary[16];
	int Aver_Distance;
	u32 sum;
}TYPEDEF_ARRARY;

typedef struct
{
	u8 Buf[7];
	u8 distance_data[3];
	u8 Data_Len;
}TYPEDEF_UART2;

extern u8 Laser_Rright;
extern u8 Laser_Length;
extern u8 Lrecflag;
extern u8 rec_num;
extern TYPEDEF_AUTOLOCATE Auto_AdjustX;
extern TYPEDEF_AUTOLOCATE Auto_AdjustZ;
extern TYPEDEF_UART2 Laser_Rec[LasBufLen];//Ω” ‹ª∫¥Ê
void Auto_LocateX(void);
void Auto_LocateZ(void);
void Auto_Loate_Stop(void);
void asdasd(void);
#endif
