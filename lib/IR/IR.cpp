#include "IR.h"

/*! 
 * @brief 初始化IR參數
 */
void IR::init(){
	for(int i = 0; i < 10;i++){
		pinMode(IR_Pin[i], INPUT);
		Cos[i] = cos(Deg[i] * PI / 180);
		Sin[i] = sin(Deg[i] * PI / 180);
	}
	_offset = 90;
}

/*! 
 * @brief 回傳IR值(0～360)
 * @param offset
 *	      外部取值(強度)
 * @param dis
 *	      顯示(預設false)
 */
int IR::GetVal(bool offset, bool dis){
	float str;
	return GetVal(str, NULL, offset, dis);
}

/*!
 * @brief 回傳IR值(0～360)
 * @param str
 *        外部取直強度
 * @param offset
 *        校正
 * @param dis
 *        顯示
 * @return 球方向(0～360)
 */
int IR::GetVal(float &str, bool offset, bool dis){
	return GetVal(str, NULL, offset, dis);
}

/*!
 *  @brief 回傳IR值(0～360)
 *  @param str
 *	       外部取值(強度)
 *  @param port
 *	       外部取值變數
 *  @param offset
 *	       校正
 *  @param dis
 *         顯示
 *  @return 球方向(0～360)
 */
int IR::GetVal(float &str, int *port, bool offset, bool dis){
	int width[10] = {0}, counter = 0;
	for(uint8_t i = 0; i < 5;i++){
		unsigned long timer = micros();
		do{
			for(uint8_t i = 0; i < 10;i++){
				width[i] += !digitalReadFast(IR_Pin[i]);
				counter += width[i];
				if(port) *(port + i) = width[i];
			}
		}while(micros() - timer <= 833);
	}
	
	int deg = -1;
	if(counter){
		float x = 0, y = 0;
		for(uint8_t i = 0; i < 10;i++){
			x += width[i] * Cos[i];
			y += width[i] * Sin[i];
			deg = int(atan2(y, x) * 180 / PI + 360) % 360;
		}
		str = sqrt(x * x + y * y);
		if(60 < deg && deg < 140 && offset) deg = deg - (_offset - 90);
	}
	
	if(dis){
		uint32_t sum = 0;
		for (int i = 0;i < 10; i++){
			sum += width[i];
			Serial.printf("%d = %4d", i, width[i]);
			Serial.println();
		}
		Serial.printf("Maxport = %d , sum = %d, mu = %d \n", deg, sum, sum / counter);
		Serial.println("--------------");
		Serial.flush();
	}
	return deg;
}

/*!
 * @brief 回傳ture有球，false則無
 * @param x
 *        外部取值(x軸) 
 * @param y
 *        外部取值(y軸)
 * @param ratio
 *        比率
 * @param dis
 *	      顯示(預設false)
 * @return 有無測到球
 */
bool IR::GetVector(float &x, float &y,float &ratio, bool dis){
	int width[10] = {0}, sum, counter = 0;
	for(uint8_t i = 0; i < 5;i++){
		sum = 0, counter = 0;
		unsigned long timer = micros();
		do{
			for(uint8_t i = 0; i < 10;i++){
				width[i] += !digitalReadFast(IR_Pin[i]);
				sum += width[i];
				counter += (width[i] > 0);
			}
		}while(micros() - timer <= 833);
	}
	
	float tx = 0, ty = 0;
	if(counter){
		for(uint8_t i = 0; i < 10;i++){
			tx += width[i] * Cos[i];
			ty += width[i] * Sin[i];
		}
		sum = sqrt((tx * tx) + (ty * ty));
		x = tx / sum; y = ty / sum;
		ratio = sum;
		if(dis) Serial.print(String("x: ") + x + "y: "+ y + "\nratio: " + ratio +"\n");
		return true;
	}
	if(dis)Serial.print(String("No Ball\n"));
	return false;
}