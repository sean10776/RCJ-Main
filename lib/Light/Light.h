#ifndef LIGHT_H
#define LIGHT_H

#include <Arduino.h>
#include<Value.h>
/*-----------------------------------------------------*/
class Light{
/****************************
init() : 初始化光感
ReadVal(byte 光感號碼(0～9)) : 回傳光感值
SetVal(int *外部取值變數(預設NULL), bool 決定回傳or讀入):設定光值
Satus():顯示設定的光值
GetRVal(int *外部取值變數):讀取Raw值
GetDVal(bool *外部取值變數,bool 顯示(預設false)) : 讀取過半的True False值
LCos[光感號碼] : 對應cos值
LSin[光感號碼] : 對應sin值
****************************/
public:
	void init();
	/*! 
	 * @brief 讀取單光感光值
	 * @param i
	 * 		  光感號碼(0~9) 
	 * @return 回傳i號光值
	 */
	int ReadVal(byte i){return analogRead(Light_Pin[i]);}
	void SetVal(int *port = NULL, bool insert = false);
	void Status();
	void SetPer(int per){Light_Per = per;}
	void GetRVal(int *port);
	bool GetDVal(bool *port, bool dis = false);
	float LCos[10], LSin[10];
private:
	byte Light_Pin[10] = {A14, A15, A16, A17, A21, A22, A6, A7, A8, A9};
	int shift = 18;
	uint16_t Light_Max[10], Light_Mid[10], Light_Min[10];
};
/*-----------------------------------------------------*/

#endif