#include "BMP180_Definitions.h"
#include "math.h"

void ReadCalibrationData(void)
{
	uint8_t redaingCalibrationDataArray[bmp180CalibrationDataLenght] = {firstZeroValue}, messageNumber = firstZeroValue ;
	uint16_t bmp180CalibrationStartAdress = calibrationStartRegister;
	HAL_I2C_Mem_Read(bmp180I2C, bmp180WriteRegisterAdress,bmp180CalibrationStartAdress,calibrationStartAdressLenght,redaingCalibrationDataArray, bmp180CalibrationDataLenght, aThousandTimeOut );
	
	AC1 =(redaingCalibrationDataArray[messageNumber]<<eightBit | redaingCalibrationDataArray[messageNumber +coefficientOfIncreaseOne]);
	messageNumber += coefficientOfIncreaseTwo;
	AC2 =(redaingCalibrationDataArray[messageNumber]<<eightBit | redaingCalibrationDataArray[messageNumber +coefficientOfIncreaseOne]);
	messageNumber += coefficientOfIncreaseTwo;	
	AC3 =(redaingCalibrationDataArray[messageNumber]<<eightBit | redaingCalibrationDataArray[messageNumber +coefficientOfIncreaseOne]);
	messageNumber += coefficientOfIncreaseTwo;
	AC4 =(redaingCalibrationDataArray[messageNumber]<<eightBit | redaingCalibrationDataArray[messageNumber +coefficientOfIncreaseOne]);
	messageNumber += coefficientOfIncreaseTwo;
	AC5 =(redaingCalibrationDataArray[messageNumber]<<eightBit | redaingCalibrationDataArray[messageNumber +coefficientOfIncreaseOne]);
	messageNumber += coefficientOfIncreaseTwo;
	AC6 =(redaingCalibrationDataArray[messageNumber]<<eightBit | redaingCalibrationDataArray[messageNumber +coefficientOfIncreaseOne]);
	messageNumber += coefficientOfIncreaseTwo;
	B1  =(redaingCalibrationDataArray[messageNumber]<<eightBit | redaingCalibrationDataArray[messageNumber +coefficientOfIncreaseOne]);
	messageNumber += coefficientOfIncreaseTwo;
	B2  =(redaingCalibrationDataArray[messageNumber]<<eightBit | redaingCalibrationDataArray[messageNumber +coefficientOfIncreaseOne]);
	messageNumber += coefficientOfIncreaseTwo;
	MB  =(redaingCalibrationDataArray[messageNumber]<<eightBit | redaingCalibrationDataArray[messageNumber +coefficientOfIncreaseOne]);
	messageNumber += coefficientOfIncreaseTwo;
	MC  =(redaingCalibrationDataArray[messageNumber]<<eightBit | redaingCalibrationDataArray[messageNumber +coefficientOfIncreaseOne]);
	messageNumber += coefficientOfIncreaseTwo;
	MD  =(redaingCalibrationDataArray[messageNumber]<<eightBit | redaingCalibrationDataArray[messageNumber +coefficientOfIncreaseOne]);
	messageNumber += coefficientOfIncreaseTwo;
} 

int16_t BMP180UncompensatedTemperature(void)
{
	uint8_t uncompensatedWriteTemperatureValue = writeTempRegister;
	uint8_t uncompensatedReadTemperatureValue [uncompReadTempMessageLength]= {firstZeroValue};
	HAL_I2C_Mem_Write(bmp180I2C, bmp180WriteRegisterAdress, writeRegister,registerLength ,&uncompensatedWriteTemperatureValue, sizeof(uncompWriteTempMesaageLenght), aThousandTimeOut);
	HAL_Delay(fiveMsDelayTime);
	HAL_I2C_Mem_Read(bmp180I2C, bmp180ReadRegisterAdress, readRegister, registerLength,uncompensatedReadTemperatureValue ,uncompReadTempMessageLength,aThousandTimeOut);
	return ((uncompensatedReadTemperatureValue[messageOne]<<eightBit) + uncompensatedReadTemperatureValue[messageTwo]) ; 
}
int32_t BMP180UncompensatedPressure(void)
{
	uint8_t uncompensatedWritePressureValue = (writePressureRegister +(overSamplingSettingsValue<<sixBit));
	uint8_t uncompensatedReadPressureValue[uncompReadPressureMessageLenght]={firstZeroValue,}; 
	HAL_I2C_Mem_Write(bmp180I2C,bmp180WriteRegisterAdress, writeRegister, registerLength, &uncompensatedWritePressureValue,sizeof(uncompensatedWritePressureValue) ,aThousandTimeOut);
	HAL_Delay(overSamplingSettingsDelayTime);
	HAL_I2C_Mem_Read(bmp180I2C, bmp180ReadRegisterAdress, readRegister, registerLength,uncompensatedReadPressureValue, uncompReadPressureMessageLenght, aThousandTimeOut );
	return (((uncompensatedReadPressureValue[messageOne]<<sixteenBit) + (uncompensatedReadPressureValue[messageTwo]<<eightBit) + (uncompensatedReadPressureValue[messageThree]))>> (eightBit-overSamplingSettingsValue));
}
float BMP180TemparuteValue(void)
{
  UT = BMP180UncompensatedTemperature();
	X1 = ((UT-AC6)* AC5/constFifteenBitValue);
	X2 = (MC*constElevenBitValue/(X1+ MD));
	B5 = (X1 + X2);
	return (((B5 + constThreeBitValue)/constFourBitValue)/realTempValueInC);
}

float BMP180PressureValue(void)
{
	UP = BMP180UncompensatedPressure();
	B6 = (B5 - constPressureFormulaValueOne);
	X1 = ((B2*(B6*B6/constTwelveBitValue))/constElevenBitValue);
	X2 = (AC2*B6/constElevenBitValue);
	X3 =  X1 + X2;
	B3 = (((((long)AC1*constTwoBitValue +X3)<<overSamplingSettingsValue)+constOneBitValue)/constTwoBitValue);
	X1 = (AC3*B6/constThirteenBitValue);
	X2 = ((B1*(B6*B6/constTwelveBitValue))/constSixteenBitValue);
	X3 = (((X1+X2)+constOneBitValue)/constTwoBitValue);
	B4 = AC4*(unsigned long)(X3 +constFifteenBitValue)/constFifteenBitValue;
	B7 = ((unsigned long)UP-B3)*(constPressureFormulaValueTwo>>overSamplingSettingsValue);
	if(B7<constPressureFormulaValueThree){ 
		pressure = ((B7*constOneBitValue)/B4);
	}
	else{
		pressure = ((B7/B4)*constOneBitValue);
	}
	X1 = (pressure/constEightBitValue)*(pressure/constEightBitValue);
	X1 = ((X1*constPressureFormulaValueFour)/constSixteenBitValue);
	X2 = ((constPressureFormulaValueFive/pressure)/constSixteenBitValue);
	


	
	return (pressure + (X1+X2+constPressureFormulaValueSix)/constFourBitValue);
}

float BMP180AltitudeValue(void)
{
	
	int32_t pressureForAltitude = BMP180PressureValue();
	return (constAltitudeFormulaValueOne*(constAltitudeFormulaValueTwo -(pow((pressureForAltitude/(float)atmPressure), constAltitudeFormulaValueThree))));
}

void StartBmp180(void)
{
	ReadCalibrationData();

}
