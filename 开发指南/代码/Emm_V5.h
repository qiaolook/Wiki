#ifndef __EMM_V5_H
#define __EMM_V5_H

#include "can.h"

/**********************************************************
***	Emm_V5.0步进闭环控制例程
***	编写作者：ZHANGDATOU
***	技术支持：张大头闭环伺服
***	淘宝店铺：https://zhangdatou.taobao.com
***	CSDN博客：http s://blog.csdn.net/zhangdatou666
***	qq交流群：262438510
**********************************************************/
/* 车体电机 */
#define MOTOR1ADD	1	//电机1地址
#define MOTOR2ADD	2	//电机2地址
#define MOTOR3ADD	3	//电机3地址
#define MOTOR4ADD	4	//电机4地址

/* 机械手电机 */
#define MOTOR5ADD	5	//电机5地址
#define MOTOR6ADD	6	//电机6地址
#define MOTOR7ADD	7

/* 电机方向 */
#define FOREWARD 1		//正转
#define REVERSAL 0		//反转

#define		ABS(x)		((x) > 0 ? (x) : -(x))

typedef enum {
	S_VER   = 0,			/* 读取固件版本和对应的硬件版本 */
	S_RL    = 1,			/* 读取读取相电阻和相电感 */
	S_PID   = 2,			/* 读取PID参数 */
	S_VBUS  = 3,			/* 读取总线电压 */
	S_CPHA  = 5,			/* 读取相电流 */
	S_ENCL  = 7,			/* 读取经过线性化校准后的编码器值 */
	S_TPOS  = 8,			/* 读取电机目标位置角度 */
	S_VEL   = 9,			/* 读取电机实时转速 */
	S_CPOS  = 10,			/* 读取电机实时位置角度 */
	S_PERR  = 11,			/* 读取电机位置误差角度 */
	S_FLAG  = 13,			/* 读取使能/到位/堵转状态标志位 */
	S_Conf  = 14,			/* 读取驱动参数 */
	S_State = 15,			/* 读取系统状态参数 */
	S_ORG   = 16,     /* 读取正在回零/回零失败状态标志位 */
}SysParams_t;

typedef struct
{


	/* 电机编码数 */
	__IO uint8_t M1_EncodedBuff[7];
	__IO uint8_t M2_EncodedBuff[7];
	__IO uint8_t M3_EncodedBuff[7];
	__IO uint8_t M4_EncodedBuff[7];
	__IO uint8_t M5_EncodedBuff[7];
	__IO uint8_t M6_EncodedBuff[7];

	__IO uint16_t M1_EncodedStatus;
	__IO uint16_t M2_EncodedStatus;
	__IO uint16_t M3_EncodedStatus;
	__IO uint16_t M4_EncodedStatus;
	__IO uint16_t M5_EncodedStatus;
	__IO uint16_t M6_EncodedStatus;


	__IO uint16_t M5_Zero_Reach_Status;
	__IO uint16_t M6_Zero_Reach_Status;

	//	uint32_t M5_Last_NUM;

	/* 电机达到状态 */
	__IO uint16_t M5_Reach_Status;
	__IO uint16_t M6_Reach_Status;

	__IO uint8_t M5_ReachBuff[3];
	__IO uint8_t M6_ReachBuff[3];

	__IO uint32_t Kp;
	__IO uint32_t Ki;
	__IO uint32_t Kd;

}Emm_V5_Pos_Status_Struct;

extern Emm_V5_Pos_Status_Struct  Emm_V5_Pos_Status;
/**********************************************************
*** 注意：每个函数的参数的具体说明，请查阅对应函数的注释说明
**********************************************************/
void Emm_V5_Reset_CurPos_To_Zero(uint8_t addr); // 将当前位置清零
void Emm_V5_Reset_Clog_Pro(uint8_t addr); // 解除堵转保护
void Emm_V5_Read_Sys_Params(uint8_t addr, SysParams_t s); // 读取参数
void Emm_V5_Modify_Ctrl_Mode(uint8_t addr, bool svF, uint8_t ctrl_mode); // 发送命令修改开环/闭环控制模式
void Emm_V5_En_Control(uint8_t addr, bool state, bool snF); // 电机使能控制
void Emm_V5_Vel_Control(uint8_t addr, uint8_t dir, uint16_t vel, uint8_t acc, bool snF); // 速度模式控制
void Emm_V5_Pos_Control(uint8_t addr, uint8_t dir, uint16_t vel, uint8_t acc, uint32_t clk, bool raF, bool snF); // 位置模式控制
void Emm_V5_Stop_Now(uint8_t addr, bool snF); // 让电机立即停止运动
void Emm_V5_Synchronous_motion(uint8_t addr); // 触发多机同步开始运动
void Emm_V5_Origin_Set_O(uint8_t addr, bool svF); // 设置挡圈回零的零点位置
void Emm_V5_Origin_Modify_Params(uint8_t addr, bool svF, uint8_t o_mode, uint8_t o_dir, uint16_t o_vel, uint32_t o_tm, uint16_t sl_vel, uint16_t sl_ma, uint16_t sl_ms, bool potF); // 修改回零参数
void Emm_V5_Origin_Trigger_Return(uint8_t addr, uint8_t o_mode, bool snF); // 发送命令触发回零
void Emm_V5_Origin_Interrupt(uint8_t addr); // 强制中断并退出回零
void Emm_V5_Pos_Status_Read_Init(Emm_V5_Pos_Status_Struct *Emm_V5_Pos_Status);
#endif
