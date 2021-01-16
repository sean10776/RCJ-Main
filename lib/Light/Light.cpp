#include "Light.h"

/*!
 * @brief 初始化光感參數
 */
void Light::init(){
	for(int i = 0; i < 10;i++){
		Light_Min[i] = 1024;Light_Max[i] = 0;
		pinMode(Light_Pin[i], INPUT);
		float deg = ((int(10 - i) * 36 + shift + 270) % 360) * PI / 180;
		LCos[i] = cos(deg); LSin[i] = sin(deg);
	}
}

/*!
 * @brief 設定光感判斷值
 * @param port
 *        外部取值變數(預設NULL)
 * @param insert
 *        決定回傳(false)or讀入(true) (預設false)
 */
void Light::SetVal(int *port, bool insert){
	if(insert){
		for(int i= 0; i < 10; i++){
			Light_Mid[i] = *(port + i);
		}
	}
	else{
		for(int i = 0; i < 10;i++){
			int val = ReadVal(i);
			Light_Max[i] = max(Light_Max[i], val);
			Light_Min[i] = min(Light_Min[i], val);
			Light_Mid[i] = (Light_Min[i]*(100-Light_Per) + Light_Max[i]*Light_Per)/100;
			if(port)*(port + i) = Light_Mid[i];
		}
	}
}

/*!
 * @brief 顯示設定的光值
 */
void Light::Status(){
	Serial.println("Port\t Min\t Mid\t Max\t Raw");
	for(int i = 0; i < 10;i++){
		Serial.printf("%4d\t%4d\t%4d\t%4d\t%4d\n", i, Light_Min[i], Light_Mid[i], Light_Max[i], ReadVal(i));
	}
	Serial.flush();
}

/*!
 * @brief 讀取Raw值
 * @param port
 *        外部取值變數
 */
void Light::GetRVal(int *port){
	for(int i = 0;i < 10;i++){
		*(port + i) = ReadVal(i);
	}
}


/*!
 * @brief 讀取過判斷值的T/F值
 * @param port
 *        外部讀取對應光感號碼
 * @param dis
 *        顯示光感號碼
 * @return 全部沒過判斷(true) / False
 */
bool Light::GetDVal(bool *port, bool dis){
	bool counter = 0;
  for (int i = 0; i < 10; i++) { //判斷元件壓在白線上
    if (ReadVal(i) > Light_Mid[i]) {
      if(dis) Serial.print(String(i) + "\t");
      if(port != NULL)*(port + i) = true;
      counter++;
    }
  }
  if(dis)Serial.println();
  if(counter == 0)return false;
  return true;
}
/*
unsigned int Light::GetBVal(bool dis){
	int data = 0;
	for(int i = 0; i < 10; i++) {
		if (ReadVal(i) > Light_Mid[i]) {
      if(dis) Serial.print(String(i) + "\t");
      data = data | (1 << i);
    }
	}
}*/