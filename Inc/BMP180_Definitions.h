#include "main.h"
#define bmp180Definitions
#define bmp180ReadRegisterAdress 0xEF
#define bmp180WriteRegisterAdress 0xEE
extern I2C_HandleTypeDef hi2c1;
#define bmp180I2C &hi2c1
#define bmp180CalibrationDataLenght 22
#define firstZeroValue 0
#define eightBit 8
#define coefficientOfIncreaseOne 1
#define coefficientOfIncreaseTwo 2
#define atmPressure  101325
#define uncompReadTempMessageLength 2
#define uncompWriteTempMesaageLenght 1
#define aThousandTimeOut 1000
#define fiveMsDelayTime 5
#define messageOne 0
#define messageTwo 1
#define messageThree 2
#define registerLength 1
#define writeRegister 0XF4
#define readRegister 0XF6
#define writeTempRegister 0x2E
#define writePressureRegister 0x34
#define overSamplingSettingsValue 0x03
#define sixBit 6
#define overSamplingSettingsDelayTime 26
#define sixteenBit 16
#define calibrationStartRegister 0xAA
#define uncompReadPressureMessageLenght 3
#define uncompWritePressureMessageLenght 1
#define calibrationStartAdressLenght 1
#define constFifteenBitValue 32768
#define constElevenBitValue 2048
#define	realTempValueInC 10.0
#define constThreeBitValue 8
#define constFourBitValue 16
#define constPressureFormulaValueOne 4000
#define constTwelveBitValue 4096
#define constThirteenBitValue 8192
#define constOneBitValue 2
#define constTwoBitValue 4
#define constSixteenBitValue 65536
#define constPressureFormulaValueTwo 50000
#define constPressureFormulaValueThree 0x80000000
#define constEightBitValue 256
#define constPressureFormulaValueFour 3038
#define constPressureFormulaValueFive -7357
#define constPressureFormulaValueSix 3791
#define constAltitudeFormulaValueOne 44330
#define constAltitudeFormulaValueTwo 1
#define constAltitudeFormulaValueThree 0.1902949572





#ifdef bmp180Definitions
int16_t  AC1 = 0;
int16_t  AC2 = 0;
int16_t  AC3 = 0;
uint16_t AC4 = 0;
uint16_t AC5 = 0;
uint16_t AC6 = 0;	
int16_t   B1 = 0;
int16_t   B2 = 0;
int16_t   MB = 0;
int16_t   MC = 0;
int16_t   MD = 0;
int32_t   UT = 0;
int32_t   UP = 0;
int32_t   X1 = 0;
int32_t   X2 = 0;
int32_t   X3 = 0;
int32_t   B3 = 0;
uint32_t   B4 = 0;
int32_t   B5 = 0;
int32_t   B6 = 0;
uint32_t   B7 = 0;
int32_t pressure=0;
#endif






