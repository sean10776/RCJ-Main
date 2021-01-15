#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include<Arduino.h>
#include<Robot.h>
#define BT Serial1

class Bluetooth{
public:
	void init(){BT.begin(Serial_rate);}
	void Read_data();
	void Send_data();
private:
	bool split_data(String &, int &);
	const uint32_t Serial_rate = 115200;
};

#endif