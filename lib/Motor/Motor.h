#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include "IMU.h"
/*-----------------------------------------------------*/
class Motor{
/*********************************
init() : 初始化馬達
SetMotor(byte 號碼(1～4), float 速度(-100～100)) : 控制單顆馬達轉速
Motion(float x分量, float y分量) : 控制車體移動方向
Stop(unsigned 時間(預設1)) : 停止
╔══Test() : 測試馬達轉向
║  Test(int 測試馬力(-100～100)) : 測試馬達轉向
╚══Test(unsigned 時間, int 測試馬力(-100～100)) : 測試馬達轉向
*********************************/
public:
	void init();
	void SetMotor(byte port, float speed);
	void Motion(float x, float y);
	void Stop(unsigned time = 1);
	void Test();
	void Test(int pwr);
	void Test(unsigned time, int pwr);
private:
	byte Motor_D[4][2] = {{2, 14}, {4, 15}, {6, 16}, {17, 8}};
	byte PWM[4] = {3, 5, 7, 9};
	IMU imu;
};
/*-----------------------------------------------------*/

#endif