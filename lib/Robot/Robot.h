#ifndef ROBOT_H
#define ROBOT_H

#include <Arduino.h>

#include "Value.h"//預設參數
#include "Motor.h"
#include "IMU.h"
#include "Light.h"
#include "IR.h"
#include "DebugMode.h"
#define LED 13

class Robot{
/****************************
void init()：初始化
void SetForward()：設定當前車頭方向為Goal
void Searching()：追球
bool Border()：出界判斷，出界回傳flase，否則true
bool Kicker(uint16_t 通電時間, uint16_t 斷電時間)：踢球 回傳當前是否踢過
char key()：讀取Serial input
****************************/
public:
	void init();
	void SetForward(){
		for(byte i = 0; i < 3;i++){
			cpx.setForward(cpx.getRVal());
		}
	}
	void Searching();
	bool Border();
	char key();
	bool Kicker(uint16_t, uint16_t);
	/************/
	Motor motor;
	IMU cpx;
	Light light;
	IR ir;
	DebugMode debugmode;
private:
	byte Kick_Pin = A19;
	void Error();
	/*******************/
	float A_Ldegree[10] = {90, 54, 18, 342, 306, 270, 234, 198, 162, 126};
	float A_LCos[10], A_LSin[10];
};

#endif