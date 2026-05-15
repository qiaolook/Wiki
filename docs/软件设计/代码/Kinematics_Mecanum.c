/**************************************************************************
文件功能：
1、麦克纳姆轮运动学逆解函数
2、麦克纳姆轮运动学正解函数
**************************************************************************/
#include "Kinematics_Mecanum.h"
#include "HWT101.h"

float Normalize_Angle(float angle) {
	// 处理正负90和正负180附近的归整
	if (angle > 89.5f && angle < 90.5f) return 90.0f;
	if (angle < -89.5f && angle > -90.5f) return -90.0f;
	if (angle > 179.5f && angle < 180.5f) return 180.0f;
	if (angle < -179.5f && angle > -180.5f) return -180.0f;
	if (angle > -0.5f && angle < 0.5f) return 0.0f;
	return angle;
}

Kinematics_Struct Kinematics_Inverse;//创建车体运动学逆解结构体参数
Kinematics_Struct Kinematics_Forward;//创建车体运动学正解结构体参数

void Kinematics_Mecanum_Init(Kinematics_Struct *Kinematics)
{
	/*  初始化速度 */
	Kinematics->Linear_X = 0;
	Kinematics->Linear_Y = 0;
	Kinematics->Angular_Z = 0;

	Kinematics->M1_RPM = 0;
	Kinematics->M2_RPM = 0;
	Kinematics->M3_RPM = 0;
	Kinematics->M4_RPM = 0;

	Measured_value.X = 0;
	Measured_value.Y = 0;
}
/**************************************************************************
函数功能：麦克纳姆轮运动学逆解函数
入口参数：车体运动学结构体参数
返回  值：通过输入车体的线速度与角速度计算出4个电机的转速
**************************************************************************/
void Kinematics_Mecanum_CalculateRPM(Kinematics_Struct *Kinematics)
{
	float linear_vel_x_mins;
	float linear_vel_y_mins;
	float angular_vel_z_mins;
	float tangential_vel;
	float x_rpm;
	float y_rpm;
	float tan_rpm;
	float angle_rad = 0;
	angle_rad = HWT101_Struct.CurrentAngle  * M_PI / 180.0f;

	float vel_x =  Kinematics->Linear_X  * cosf(angle_rad) + Kinematics->Linear_Y  * sinf(angle_rad);
	float vel_y = -Kinematics->Linear_X  * sinf(angle_rad) + Kinematics->Linear_Y  * cosf(angle_rad);

	//convert cm/s to cm/min
	linear_vel_x_mins = vel_x * 60;
	linear_vel_y_mins = vel_y * 60;

	//convert rad/s to rad/min
	angular_vel_z_mins = Kinematics->Angular_Z * 0.6 ;

	tangential_vel = angular_vel_z_mins * (FR_WHEELS_DISTANCE / 2 + LR_WHEELS_DISTANCE / 2);

	x_rpm = linear_vel_x_mins / WHEEL_CIRCUMFERENCE;
	y_rpm = linear_vel_y_mins / WHEEL_CIRCUMFERENCE;
	tan_rpm = tangential_vel / WHEEL_CIRCUMFERENCE;

	//calculate for the target motor RPM and direction
	Kinematics->M1_RPM = x_rpm - y_rpm - tan_rpm;//M1电机目标转速 B

	Kinematics->M2_RPM = x_rpm + y_rpm + tan_rpm;//M2电机目标转速 C

	Kinematics->M3_RPM = x_rpm + y_rpm - tan_rpm;//M3电机目标转速 A

	Kinematics->M4_RPM = x_rpm - y_rpm + tan_rpm;//M4电机目标转速 D
}

/**************************************************************************
函数功能：麦克纳姆轮运动学正解函数
入口参数：车体运动学结构体参数
返回  值：通过输入4个电机的转速计算出车体的线速度与角速度
**************************************************************************/
void Kinematics_Mecanum_GetVelocities(Kinematics_Struct *Kinematics)
{
	// 计算车体的线速度和角速度
	float angle_rad = 0;
	angle_rad =  HWT101_Struct.CurrentAngle * M_PI / 180.0f;

	// 基于麦克纳姆轮正解：车体坐标系下的线速度
	float vx = Kinematics->X -Measured_value.old_X;
	float vy = Kinematics->Y -Measured_value.old_Y;
	Measured_value.old_X = Kinematics->X;
	Measured_value.old_Y = Kinematics->Y;

	// 变换为全局坐标速度
	Kinematics->average_rps_x = vx * cosf(angle_rad) - vy * sinf(angle_rad);
	Kinematics->average_rps_y = vx * sinf(angle_rad) + vy * cosf(angle_rad);
    Kinematics->average_rps_a = (-Kinematics->M1_RPM + Kinematics->M2_RPM - Kinematics->M3_RPM + Kinematics->M4_RPM) / 4 / 60* WHEEL_CIRCUMFERENCE / (FR_WHEELS_DISTANCE / 2 + LR_WHEELS_DISTANCE / 2);
}

// 函数：计算小车位置
CarPosition_Struct calculateCarPosition(Kinematics_Struct *Kinematics)
{
	CarPosition_Struct Measured_Position;
	Measured_Position.Valid = SUCCESSRECEIVE;
	Measured_Position.x = 0;
	Measured_Position.y = 0;
    // 假设小车的初始位置为(0, 0)
	Measured_value.X += Kinematics->average_rps_x;
	Measured_value.Y += Kinematics->average_rps_y;

	float angle = Normalize_Angle(HWT101_Struct.CurrentAngle);

	if (angle == 0 || angle == 180 || angle == -180) {
		Measured_Position.x = Measured_value.X * 0.98;
		Measured_Position.y = Measured_value.Y * 0.965;
	} else if (angle == 90 || angle == -90) {
		Measured_Position.x = Measured_value.X * 0.965;
		Measured_Position.y = Measured_value.Y * 0.98;
	} else {
		Measured_Position.x = Measured_value.X * 0.98;
		Measured_Position.y = Measured_value.Y * 0.965;
	}

return Measured_Position;
}

