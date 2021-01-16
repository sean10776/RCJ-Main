#include "RCJ_SD.h"

/*!
 * @brief 初始化SD參數
 */ 
void RCJ_SD::init(){
  if(!SD.begin(chipSelect)){
    Serial.print("SD Fail!!");
  }
}


/*!
 * @brief SD寫入
 * @param fn
 *        檔案名(要含副檔名)
 * @param data
 *        寫入資料
 * @return 動作完成回傳True
 */ 
bool RCJ_SD::SDwrite(char const *fn, String data){
	if(SD.exists(fn)) Serial.println(String("Remove:") + SD.remove(fn));
  myFile = SD.open(fn, FILE_WRITE);
  myFile.print(data);
  delay(5);
  myFile.close();
	return true;
}

/*!
 * @brief SD讀取
 * @param fn
 *        檔案名(要含副檔名)
 * @param data
 *        外部讀取資料
 * @return 動作完成回傳True; 無檔案回傳False
 */ 
bool RCJ_SD::SDread(char const *fn, String &data){
	if(SD.exists(fn)) myFile = SD.open(fn, FILE_READ);
	else return false;
	while(myFile.position() < myFile.size()){
    static String sbuf = "";
    if(myFile.available()){
      char cbuf = (char)myFile.read();
			data += cbuf;
    }
  }
  myFile.close();
	return true;
}