#ifndef CAMERA_H
#define CAMERA_H

#include <Arduino.h>
/*-----------------------------------------------------*/
class Camera{

public:
	void init();
	void init(int rate);
	int GetVal(float ratio, bool dis = false); 
private:
	bool Uart_read(String &title, int &val);
};
/*-----------------------------------------------------*/
#define Cam Serial6

#endif