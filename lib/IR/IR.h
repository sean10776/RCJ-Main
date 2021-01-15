#ifndef IR_H
#define IR_H

#if ARDUINO >= 100
 #include <Arduino.h>
#else
 #include "WProgram.h"
#endif
/*-----------------------------------------------------*/
class IR{
/**********************	
init() : 初始化IR
╔══GetVal(bool 校正(預設true),bool 顯示(預設false)) : 回傳IR值(0～360)
║  GetVal(float 外部取值(強度), bool 校正(預設true),bool 顯示(預設false)) : 回傳IR值(0～360)
╚══GetVal(float 外部取值(強度), int 外部取值變數, bool 校正,bool 顯示) : 回傳IR值(0～360)
GetVector(float 外部取值(x軸), float 外部取值(y軸), bool 顯示(預設false)) : 回傳ture有球，false則無
Set_offset(int 校正值) : 設定校正值
**********************/
public:
	void init();
	int GetVal(bool offset = true, bool dis = false);
	int GetVal(float &str, bool offset = true, bool dis = false);
	int GetVal(float &str, int *port, bool offset, bool dis);
	bool GetVector(float &x, float &y, float &str, bool dis = false);
	void Set_offset(int offset){_offset = offset;}
private:
	byte IR_Pin[10] ={10, 11, 12, 26, 27, 28, 29, 30, 31, 32};
	float Deg[10] = {85, 36, 0, 324, 288, 252, 216, 180, 144, 95};
	float Cos[10], Sin[10];
	int _offset = 90;
};
/*-----------------------------------------------------*/

#endif