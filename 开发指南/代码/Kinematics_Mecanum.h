#ifndef __KINEMATICS_MECANUM_H
#define __KINEMATICS_MECANUM_H
#include "main.h"

#ifdef __cplusplus
 extern "C" {
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define WHEEL_RADIUS 5.05f  // 假设麦轮半径为3.8厘米

#define WHEEL_CIRCUMFERENCE 31.7300858f//轮子周长 m

#define LR_WHEELS_DISTANCE 22.69f//左右轮距 m
#define FR_WHEELS_DISTANCE 19.3f//前后轮距 m

typedef struct
{
	__IO float Linear_X;	//X轴线速度 m/s
	__IO float Linear_Y;	//Y轴线速度 m/s
	__IO float Angular_Z;	//Z轴角速度 rad/s
	__IO float M1_RPM;	  //M1电机转速 rpm
	__IO float M2_RPM;	  //M2电机转速 rpm
	__IO float M3_RPM;	  //M3电机转速 rpm
	__IO float M4_RPM;	  //M4电机转速 rpm
	__IO float X;
	__IO float Y;
	__IO float average_rps_x;
	__IO float average_rps_y;
	__IO float average_rps_a;
}Kinematics_Struct;		  //车体运动学结构体参数

extern Kinematics_Struct Kinematics_Inverse;//创建车体运动学逆解结构体参数
extern Kinematics_Struct Kinematics_Forward;//创建车体运动学正解结构体参数

void Kinematics_Mecanum_CalculateRPM(Kinematics_Struct *Kinematics);//麦克纳姆轮运动学逆解函数
void Kinematics_Mecanum_GetVelocities(Kinematics_Struct *Kinematics);//麦克纳姆轮运动学正解函数

// 结构体表示小车的位置
typedef struct {
    float x; 
    float y; 
	uint16_t Valid;
} CarPosition_Struct;

typedef struct {
	float X;
	float Y;
	float old_X;
	float old_Y;
} Position_Struct;

extern Position_Struct projected_value;
extern Position_Struct Measured_value;
float Normalize_Angle(float angle);
CarPosition_Struct calculateCarPosition(Kinematics_Struct *Kinematics);
void Kinematics_Mecanum_Init(Kinematics_Struct *Kinematics);

#ifdef __cplusplus
}
#endif

#endif
