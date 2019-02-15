/**
  * File Name: user.c
**/

#include "user.h"
#include "adc.h"
#include "i2c.h"

struct adcData_struct adcData;
uint8_t dataToSend[DATA_TO_SEND_SIZE];
uint8_t input_data = 0;
uint8_t firsttime = 0;
uint8_t transitionDone = 0;

void HAL_ADC_ConvCpltCallback (ADC_HandleTypeDef *hadc)
{
	HAL_ADC_Stop_IT(&hadc1);
	adcData.results[adcData.conversions] = HAL_ADC_GetValue(&hadc1);
	adcData.conversions++;

	if(adcData.conversions == ADC_RESULTS_NUMBER) {
		float temp = 0;
		for(uint8_t i=0; i<ADC_RESULTS_NUMBER; i++) {
			temp = temp + ((float) (adcData.results[i]) / 4096 * 3.3);
			adcData.results[i] = 0;
		}
		adcData.average = temp / ADC_RESULTS_NUMBER;
		adcData.conversions++;
	}
	else {
		HAL_ADC_Start_IT(&hadc1);
	}

	if(!firsttime) {
		firsttime = 1;
	}
}

void HAL_I2C_SlaveTxCpltCallback (I2C_HandleTypeDef *hi2c)
{
	transitionDone = 1;
}

void HAL_I2C_SlaveRxCpltCallback (I2C_HandleTypeDef *hi2c)
{

}

void HAL_I2C_AddrCallback (I2C_HandleTypeDef * hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode)
{

}


void clearArrayUint32(uint32_t* target, uint16_t size)
{
	for(uint16_t i=0; i<size; i++) {
		target[i] = 0;
	}
}

void clearArrayFloat(float* target, uint16_t size)
{
	for(uint16_t i=0; i<size; i++) {
		target[i] = 0;
	}
}

void Uint8FromFloat(float input, uint8_t *outArray)
{
	float *dest = (float*) (outArray);
	*dest = input;
}

/****END OF FILE****/
