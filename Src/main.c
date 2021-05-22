#include "main.h"
	float realTemperature= 0;
	float realPressure= 0;
	float realAltitude= 0;
int main(void)
{ 
	
  HAL_Init();
  SystemClock_Config();
  I2C1_Init();
	StartBmp180();
	
  while (1)
  {
		realTemperature	= BMP180TemparuteValue();
		realPressure    = BMP180PressureValue();
		realAltitude    = BMP180AltitudeValue();
	
  }
}
