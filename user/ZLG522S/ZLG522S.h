
#ifndef __ZLG522S_H
#define __ZLG522S_H

#include "sys.h"
#include <stdbool.h>

#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
//=================================================================================================
////============= 函数剪裁 ==========================================================================
//#define GET_DVC_INFO_EN				1
//#define PCD_CONFIG_EN					0
//#define PCD_CLOSE_EN					0
//#define PCDLoadKey_en					0
//#define PCDWriteReg_en				0
//#define PCDReadReg_en					0

//#define PICC_REQUEST_EN 			0
//#define PiccAnticoll_en				0
//#define PiccSelect_en					0
//#define PiccHalt_en						0
//#define PiccAuthE2_en					0
//#define PiccAuthKey_en				0
//#define PiccRead_en						0
//#define PiccWrite_en					0
//#define PiccULWrite_en				0
//#define PiccValue_en					0
//#define PiccReset_en					0			
#define PICC_ACTIVE_TYPEA_EN	1
#define PiccAutoDetect_en			1
//#define PiccADRcv_en					0
//#define PiccReadADDT_en				0

////============= 常量定义 ==========================================================================
////定义A型卡命令
#define REQSTD		0x26	
#define REQALL		0x52
#define SELCODE1	0x93
#define SELCODE2	0x95
#define SELCODE3	0x97
#define KEYA			0x60
#define KEYB			0x61
#define DECREMENT	0xc0
#define INCREMENT	0xc1
#define RESTORE		0xc2
#define ISO14443A	0x00
#define ISO14443B	0x80
#define INT8U unsigned char

// 定义串行数据缓冲区各字符单元索引值
#define FRAMELEN				0				// 帧长度
#define CMDTYPE					1				// 包号
#define COMMAND					2				// 命令
#define STATUS					2				// 响应状态
#define LENGTH      		3				// 数据长度
#define DATA        		4				// 数据起始位置
#define PRTCLEN					6				// 协议字符长度

// 通信协议常量
#define STX     				0x20
#define ETX     				0x03
#define ACK						  0x06
#define NAK							0x15

// 定义返回错误代码
#define OK						  0
#define COMMERR					1
#define SEQERR					2
#define BCCERR					4

// 定义缓冲区大小
#define MAXSERSIZE      64+2+6
extern u8 SerBfr[MAXSERSIZE];// 串行数据缓冲�
extern u8 Coal_SampleID[8];
extern u8 Coal_ID[16];
extern u8 Status1;
extern u8 Status2;
extern bool RFID_Hand_OK; 	//读卡器初始化与串口握手成功标记

extern u8 BottleRfidId[4];//瓶RFID
extern u8 ColRfidId[8];//煤样信息


//============= 函数声明 =================================================================
/**************************************************************************************************
** 函数原型:    unsigned char ZLG522S_UARTInit(void)
** 函数功能:    ZLG522S初始化
** 输入参数:    -		
** 输出参数:    
** 返 回 值:    命令执行结果
** 说    明:		该函数
**************************************************************************************************/
void USART3_Init(u32 bound);		//串口3初始化
u8 ZLG522S_UARTInit(void);			//ZLG522S初始化
void RFIDdelay_us(u16 time);
/**************************************************************************************************
** 函数原型:    unsigned char ReadColRfid(BottleRfidId,ColRfidId)
** 函数功能:    读RFID和煤样信息
** 输入参数:    RFID 和 煤样信息  缓冲区		
** 输出参数:    
** 返 回 值:    命令执行结果 0成功  1失败
** 说    明:	该函数
							1、A卡激活 M指令  返回RFID
							2、直接密码验证 F指令
							3、读缓冲区8 G指令 返回煤样信息
**************************************************************************************************/
unsigned char ReadColRfid(unsigned char BottleRfidId_temp[],unsigned char ColRfidId_temp[]);

//读卡函数
/**************************************************************************************************
** 函数原型:    unsigned char PiccActiveTypeA(	unsigned char BaudRate,unsigned char Req_Code,
**												unsigned char *Atq,unsigned char *Ats,
**												unsigned char *PiccSnrLen,unsigned char *PiccSnr)
** 函数功能:    模块信息配置
** 输入参数:    unsigned char BaudRate			// 保留参数，设置为0
**							unsigned char Req_Code			// 请求码	
** 输出参数:    unsigned char *Atq					// 请求回应
**							unsigned char *Ats					// 最后一级选择应答
**							unsigned char *Piunsigned char PiccAutoDetect(unsigned char OutMode,  unsigned char TxMode, unsigned char Req_Code, 
					 unsigned char AuthMode, unsigned char KEYAB,  unsigned char *Key, unsigned char Block)ccSnrLen		// 卡号长度
**							unsigned char *PiccSnr			// 卡号
** 返 回 值:    命令执行结果
**************************************************************************************************/
extern u8 PiccActiveTypeA(u8 BaudRate, u8 Req_Code, u8 *Atq, u8 *Ats, u8 *PiccSnrLen, u8 *PiccSnr);
u8 PiccAutoDetect(u8 OutMode, u8 TxMode, u8 Req_Code, u8 AuthMode, u8 KEYAB,  u8 *Key, u8 Block);
char IC_PiccAutKey(u8 *Key);		//直接密码验证
char ActiveCardKey(void);				//A型卡激活和密码验证
unsigned char IC_ReadBlockData(u8 Block);	  //读卡
unsigned char IC_WriteBlockData(u8 Block);  	//写卡
int IC_SearchBrush(void);
u32 BottleID_ByteTOString(u8 B1, u8 B2, u8 B3, u8 B4); //瓶/卡ID由字节转为4个连续字符串

#endif				// __ZLG522S_H__

