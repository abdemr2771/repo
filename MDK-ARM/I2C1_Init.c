#include "main.h"
I2C_HandleTypeDef hi2c1;
void I2C1_Init(void)
{ 
	GPIO_InitTypeDef GPIO_InitStruct_I2C;
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_I2C1_CLK_ENABLE();
	
	GPIO_InitStruct_I2C.Pin   			= GPIO_PIN_8 | GPIO_PIN_9;
	GPIO_InitStruct_I2C.Mode  			= GPIO_MODE_AF_OD;
	GPIO_InitStruct_I2C.Pull  			= GPIO_PULLUP;
	GPIO_InitStruct_I2C.Speed 			= GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct_I2C.Alternate 	= GPIO_AF4_I2C1;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct_I2C);
	
	hi2c1.Instance = I2C1;
	hi2c1.Init.ClockSpeed = 400000;
	hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c1) != HAL_OK){
		Error_Handler();
	}
	
}
