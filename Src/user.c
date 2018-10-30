/**
  * File Name: user.c
**/

#include "user.h"
#include "adc.h"
#include "i2c.h"

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

		if(!adcData.first_time) {
			Uint8FromFloat(&adcData.average, &dataToSend[0]);
			HAL_I2C_Slave_Transmit_DMA(&hi2c1, &dataToSend[0], DATA_TO_SEND_SIZE);
			adcData.first_time = 1;
		}
	}
	else {
		HAL_ADC_Start_IT(&hadc1);
	}
}

void HAL_I2C_SlaveTxCpltCallback (I2C_HandleTypeDef *hi2c)
{
	Uint8FromFloat(&adcData.average, &dataToSend[0]);
	HAL_I2C_Slave_Transmit_DMA(&hi2c1, &dataToSend[0], DATA_TO_SEND_SIZE);
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

void Uint8FromFloat(float *input, uint8_t *outArray)
{
	uint8_t *d = (uint8_t *) &input;

	outArray[0] = *d & 0xFF;
	outArray[1] = (*d >> 8) & 0xFF;
	outArray[2] = (*d >> 16) & 0xFF;
	outArray[3] = (*d >> 24) & 0xFF;
}

/****END OF FILE****/
