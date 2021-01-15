#ifndef IMU_H
#define IMU_H

#if ARDUINO >= 100
 #include <Arduino.h>
#else
 #include "WProgram.h"
#endif
#include "Value.h"
#include <EEPROM.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

/*-----------------------------------------------------*/
class IMU : public Adafruit_BNO055{
/****************************
init() : 初始化Compass
getRVal() : 取x軸raw值
getVal() : 取當前goal值
getForward() : 取Forward值
setForward(uint16_t Forward值): 設定Forward
Calibration() : 校正Compass
DisplayCalStatus() : 顯示Compass校正狀態
DisplaySensorOffsets() : 顯示Compass Offset值
****************************/
public:
	IMU() : Adafruit_BNO055(55){}
	bool init(adafruit_bno055_opmode_t mode = OPERATION_MODE_IMUPLUS){
		_mode = mode; 
		return begin(mode);
	}
	int getRVal();
	/*! @return 車頭方向(0~360)*/
	int getVal(){return (getRVal() - _Forward + 360) % 360;}
	uint16_t getForward(){return _Forward;}
	/*! @brief 設定車頭方向*/
	void setForward(uint16_t Forward){_Forward = Forward;}
	void Calibration(void);
	void DisplayCalStatus();
	void DisplaySensorOffsets(const adafruit_bno055_offsets_t);
	
private:
	adafruit_bno055_opmode_t _mode;
};
/*-----------------------------------------------------*/
#endif