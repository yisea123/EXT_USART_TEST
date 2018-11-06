#ifndef __PWM_H
#define __PWM_H
#include "sys.h"
#include "Sys_Init.h"
//#define Dir_Y PEout(4)
#define DirFount_Y()    Dir_Y = 1     //´ÓÁãÎ»ÏòÇ°×ß
#define DirBack_Y()     Dir_Y = 0   //»ØÁãÎ»



extern TIM_OCInitTypeDef  TIM_OCInitStructure;
extern TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
/**************ÈıÖá·½Ïò*****************/
#define	DIR_X			PCout(5) 
#define	DIR_Y			PAout(4)
#define	DIR_Z			PBout(12)

/**************´«¸ĞÆ÷*****************/
#define Proximity_3		PBin(5)	//ÍĞÅÌ½Ó½ü¿ª¹Ø
#define Proximity_2		PBin(4) //ÍĞÅÌ½Ó½ü¿ª¹Ø
#define Proximity_1		PBin(3) //ÍĞÅÌ½Ó½ü¿ª¹Ø

#define Axis_Z_Up_Sensor 				PEin(8)//ZÖáÉÏÏŞÎ»
#define Axis_Z_Down_Sensor			PEin(10)//ZÖáÏÂÏŞÎ» 
#define Axis_X_Forward_Sensor		PDin(6)//XÖáÇ°ÏŞÎ»
#define Axis_X_Backward_Sensor	PEin(14)//XÖáºóÏŞÎ»



#define PWM_PCS       23   //PWMÆµÂÊ=72000000/(PCS+1)*(ARR+1) 
#define Z_Acc_Time_SL 50//³¬µÍËÙÄ£Ê½¼ÓËÙÊ±¼ä
#define Z_Acc_Time_L  200//µÍËÙÄ£Ê½¼ÓËÙÊ±¼ä
#define Z_Acc_Time_M  1000//ÖĞËÙÄ£Ê½¼ÓËÙÊ±¼ä
#define Z_Acc_Time_H	2000//¸ßËÙÄ£Ê½¼ÓËÙÊ±¼ä

#define X_Acc_Time_L  200//µÍËÙÄ£Ê½¼ÓËÙÊ±¼ä
#define X_Acc_Time_M  500//ÖĞËÙÄ£Ê½¼ÓËÙÊ±¼ä
#define X_Acc_Time_H	2000//¸ßËÙÄ£Ê½¼ÓËÙÊ±¼ä

/*****************************XÖá¿ØÖÆ²ÎÊı**************************/
#define X_DIV         					240     //Çı¶¯Æ÷ÉèÖÃÏ¸·Ö
#define X_STAR_FREQ     				50    	//³õÊ¼ÆµÂÊ Ìá¹©³õÊ¼ÆµÂÊ½øÈëÍâ²¿ÖĞ¶Ï
#define X_END_FREQ							50
#define X_PULSE_AFTZERO					10			//µ½´ïÁãµãºóÇ°½øµÄÂö³åÊı
#define X_MPP										0.6865		//mm per pulse ºÁÃ×Ã¿Âö³å0.1977
#define X_DIR_BACK							0
#define X_DIR_FRONT							1
//¸ßËÙ
#define X_SPEED_FREQ_H  				800   //¸ßËÙÆµÂÊ 
#define X_HORL_PULSE_VALVE_H   	2185  //¸ßËÙ×ÜÂö³åÊı·§Öµ£¬ÓÃÀ´·Ö±æÊÇ·ñ¸ßËÙĞĞ½ø
//ÖĞËÙ
#define X_SPEED_FREQ_M  				300   //Ä¿±êÆµÂÊ 
#define X_HORL_PULSE_VALVE_M   	1456  //ÖĞËÙ×ÜÂö³åÊı·§Öµ£¬ÓÃÀ´·Ö±æÊÇ·ñÖĞËÙĞĞ½ø
//µÍËÙ
#define X_SPEED_FREQ_L					200    //µÍËÙÆµÂÊ 
#define X_HORL_PULSE_VALVE_L  	728  	//ÖĞËÙ×ÜÂö³åÊı·§Öµ£¬ÓÃÀ´·Ö±æÊÇ·ñÖĞËÙĞĞ½ø
#define	X_Zero_Pluse						46		//XÖáµ½´ïÁãµãºóÇ°½øÂö³åÊı



/*****************************ZÖá¿ØÖÆ²ÎÊı**************************/
#define Z_DIV         					120     //Çı¶¯Æ÷ÉèÖÃÏ¸·Ö
#define Z_STAR_FREQ     				50    	//³õÊ¼ÆµÂÊ Ìá¹©³õÊ¼ÆµÂÊ½øÈëÍâ²¿ÖĞ¶Ï
#define Z_END_FREQ							50
#define Z_PULSE_AFTZERO					10			//µ½´ïÁãµãºóÇ°½øµÄÂö³åÊı
#define Z_MPP										0.40438		//mm per pulse ºÁÃ×Ã¿Âö³å
#define Z_DIR_FRONT							1
#define Z_DIR_BACK							0
#define Z_ZeroUp_Pluse					200//ZÖá¹éÎ»ÉÏÉıÂö³åÊı

//¸ßËÙ
#define Z_SPEED_FREQ_H  				800  	//¸ßËÙÆµÂÊ  
#define Z_HORL_PULSE_VALVE_H   	3709  //¸ßËÙ×ÜÂö³åÊı·§Öµ£¬ÓÃÀ´·Ö±æÊÇ·ñ¸ßËÙĞĞ½ø
//ÖĞËÙ
#define Z_SPEED_FREQ_M 					500   //Ä¿±êÆµÂÊ È 
#define Z_HORL_PULSE_VALVE_M   	2472  //ÖĞËÙ×ÜÂö³åÊı·§Öµ£¬ÓÃÀ´·Ö±æÊÇ·ñÖĞËÙĞĞ½ø
//µÍËÙ
#define Z_SPEED_FREQ_L  				200   //µÍËÙÆµÂÊ
#define Z_HORL_PULSE_VALVE_L    1236	//µÍËÙ×ÜÂö³åÊı·§Öµ£¬ÓÃÀ´·Ö±æÊÇ·ñ¸ßËÙĞĞ½ø
//³¬µÍËÙÓÃÀ´ÍĞ¾Ù
#define Z_SPEED_FREQ_SL          60
#define Z_SLDISTANCE						50
#define Z_HORL_PULSE_VALVE_SL   625


/*****************************YÖá¿ØÖÆ²ÎÊı**************************/
#define Y_DIV         					120     //Çı¶¯Æ÷ÉèÖÃÏ¸·Ö
#define Y_STAR_FREQ     				100    	//³õÊ¼ÆµÂÊ Ìá¹©³õÊ¼ÆµÂÊ½øÈëÍâ²¿ÖĞ¶Ï
#define Y_END_FREQ							100
#define Y_DIR_LEFT							1//YÖáĞĞ×ßµÄ·½ÏòÎª×ó
#define Y_DIR_RIGHT							0//YÖáĞĞ×ßµÄ·½ÏòÎªÓÒ
#define Y_LeftLim_MorePluse					1780//YÖá´ÓÔ­µãÍù×ó×ßµÄÂö³åÊı	
#define Y_LeftLim_MidPluse					1743//µÚÒ»´ÎÉÏµçĞĞ×ßÂö³åÊı
#define Y_LeftLim_LessPluse					1735//YÖá´ÓÔ­µãÍù×ó×ßµÄÂö³åÊı	
#define Y_RightLim_MorePluse				1775//YÖá´ÓÔ­µãÍùÓÒ×ßµÄÂö³åÊı
#define Y_RightLim_MidPluse				1748//µÚÒ»´ÎÉÏµçĞĞ×ßÂö³åÊı
#define Y_RightLim_LessPluse				1740//YÖá´ÓÔ­µãÍùÓÒ×ßµÄÂö³åÊı
#define Y_RightZero_Pluse				30//YÖá´Ó×óÍùÓÒ»ØÁã¼ÌĞøĞĞ×ßµÄÂö³åÊı
#define Y_LeftZero_Pluse				40//YÖá´ÓÓÒÍù×ó»ØÁã¼ÌĞøĞĞ×ßµÄÂö³åÊı

//¸ßËÙ
#define Y_SPEED_FREQ  				400   	//¸ßËÙÆµÂÊ 
#define Y_HORL_PULSE_VALVE_H   	3039  //¸ßËÙ×ÜÂö³åÊı·§Öµ£¬ÓÃÀ´·Ö±æÊÇ·ñ¸ßËÙĞĞ½ø
#define Y_ACC_TIME						500
#define Y_MPP								0.09

#define AXIS_X 0
#define AXIS_Z 1
#define AXIS_Y 2


typedef struct 
{
  u8 InCtrl_Flag;           	//¿ØÖÆÖĞ±êÖ¾ 0:²»ÊÜ¿Ø 1:¶Ì¾àÀë£¬²»¼Ó¼õËÙ£¬ÂıËÙÄ£Ê½ 2:³¤¾àÀë£¬¼Ó¼õËÙ£¬¿ìËÙÄ£Ê½
  u32 NowPulse;               //µ±Ç°ÒÑ×ßÂö³åÊı
  float NowFreq;              //µ±Ç°ÆµÂÊ
  float NowACC;
  u32 Target_Pulse;           //Ä¿±êÂö³åÊı    
  u32 Timer_Cnt;              //µ±Ç°ÒÑ×ßÊ±¼ä
  u32 PulsePoint[7];          //¹ı³ÌÊ±¼äµãµÄÂö³åÊı£¬·Ö±ğÎª¼Ó¼ÓËÙÍê³ÉÊ±¼äµã£¬ÔÈ¼ÓËÙÍê³ÉÊ±¼äµã£¬¼õ¼ÓËÙÍê³ÉÊ±¼äµã
  u32 TimerPoint[7];          //¹ı³ÌÊ±¼äµã
  int32_t YCoordinate;        //YÖá×ø±ê
  float FreqPoint[7];        	//¼ÓËÙ¹ı³ÌÊ±¼äµãÆµÂÊ
  u16 Time_Delta;             //ÓëÉÏ¸öÊ±¼äµãµÄÊ±¼ä²î
  u8  SpeedChange_Stage;      //¼Ó¼õËÙ¹ı³Ì3¸ö½×¶Î 1£º¼ÓËÙ¹ı³Ì 2£º¼õËÙ¹ı³Ì
	u16 Target_Fre;							//Ä¿±êÆµÂÊ
	float Jerk_Speed;						//¼Ó¼ÓËÙ¶È
	float Acc_Speed;							//ÔÈËÙ¼ÓËÙ¶È
  u32 Coordinate;							//µ±Ç°×ø±ê
	bool Dir;
	bool	CtrlEnd_Flag;
	float Stage4_Acc;
	float Stage1_Acc;
}TYPE_StepMotor;

typedef struct
{
	u8 command;//×ª¹¤Î»Ö¸Áî
	u8 tray_position;//ÍĞÅÌÊôĞÔ
	u8 tray_stage;//µ±Ç°ÍĞÅÌÎ»ÖÃ£¬
	u8 Put_Box_Stage;//·ÅÏä¶¯×÷½×¶Î
	u8 Get_Box_Stage;//È¡Ïä¶¯×÷½×¶Î
	u8 XZRun_Stage;//XZÔË¶¯Ç¶Ì×½×¶Î
	u8 XZRUN_Status_Change;//XZÔË¶¯×´Ì¬¸Ä±ä
	u8 Tray_PutBox_Stage;//ÍĞÅÌ·ÅÏäÇ¶Ì×½×¶Î
	u8 Tray_PutBox_Status_Change;//ÍĞÅÌ·ÅÏä×´Ì¬¸Ä±ä
	u8 Tray_GetBox_Stage;//ÍĞÅÌÈ¡Ïä½×¶Î
	u8 Tray_GetBox_Status_Change;//ÍĞÅÌÈ¡Ïä×´Ì¬¸Ä±ä
	bool end_flag;//Ç¶Ì×¶¯×÷½áÊø±êÖ¾
	bool Get_Box_Start_Flag;//×¥ÏäÖ¸Áî¿ªÊ¼±êÖ¾
	bool Put_Box_Start_Flag;//·ÅÏäÖ¸Áî¿ªÊ¼±êÖ¾
	bool Move_Alone;//µ¥µãÔË¶¯×´Ì¬
	u16 Target_X;//XÖá×ø±ê£¬µ¥Î»mm
	u16 Target_Z;//ZÖá×ø±ê£¬µ¥Î»mm
	u16 Comend;
	u8 Speed_Grade;//ËÙ¶ÈµµÎ»
	u16 Step_Grade;//²½³¤µµÎ»
	u16 PlatZ_Axis;//ÍĞ¼ÜZ×ø±ê
	u16 PlatX_Axis;//ÍĞ¼ÜZ×ø±ê
}TYPEDEF_ACTION;



extern TYPEDEF_ACTION Action;
extern TYPE_StepMotor Axis_X;
extern TYPE_StepMotor Axis_Z;
extern TYPE_StepMotor Axis_Y;
extern u8 Motor_CtrlOver_Flag;		//µç»ú¿ØÖÆ½áÊø±êÖ¾£¬´Ë±êÖ¾ÖÃ1ºó£¬ÉÏ´«½áÊø¿ØÖÆÓ¦´ğ
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
void Uniform_Speed_Advance(u32 Tar_Pluse,u8 Axis,bool dir);//XÖáË®Æ½ÔÈËÙÇ°½ø
void 	X_Uniform_Speed_Back(u32 Tar_Pluse);
u32 PWMCtrl_ARRCount(u32 pcs, float Fre);


#endif
