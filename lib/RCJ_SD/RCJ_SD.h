#ifndef RCJ_SD_H
#define RCJ_SD_H

#include <Arduino.h>
#include <SD.h>

class RCJ_SD{
/*************************************
void init()：初始化SD卡
bool SDwrite(char const* 檔案名, String 輸入資料)寫入後回傳true
bool SDread(char const* 檔案名, String 回傳資料)讀取成功回傳true，否則false
*************************************/
public:
	void init();
	bool SDwrite(char const *fn, String data);
	bool SDread(char const *fn, String &data);
private:
	File myFile;
	Sd2Card card;
	SdVolume volume;
	SdFile root;
	const int chipSelect = BUILTIN_SDCARD;
};
#endif