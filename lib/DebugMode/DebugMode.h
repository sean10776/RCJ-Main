#ifndef DEBUGMODE_H
#define DEBUGMODE_H

#define ESP Serial1
#include <Value.h>
#include <RCJ_SD.h>
#include <Camera.h>
#include <Light.h>
#include <IR.h>

class DebugMode{
/*****************************
void init(bool 決定是否連上ESP, IR 讀取ir物件, Light 讀取Light物件, Camera 讀取camera物件)：初始化
bool Debug()：調整參數+讀取SD資料
void SendData()：傳資訊給ESP
*****************************/
public:
	void init(bool debug, IR *ir, Light *li, Camera *cam);
	bool Debug();
	void SendData();
private:
	IR *_ir;
	Light *_li;
	Camera *_cam;
	bool _debug = false;
	RCJ_SD sd;
	bool Command(String &title, int &value);
	void datatrans(String data, int *value);
};

#endif