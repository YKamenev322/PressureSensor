/**
  * File Name: user.h
**/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __user_H
#define __user_H

#include "stm32f1xx_hal.h"

#define ADC_RESULTS_NUMBER 10
#define LED_DELAY 1000
#define DATA_TO_SEND_SIZE 4

struct adcData_struct {
	uint8_t conversions;
	uint32_t results[ADC_RESULTS_NUMBER];
	float average;
	uint8_t first_time;
} adcData;

uint8_t dataToSend[DATA_TO_SEND_SIZE];

void clearArrayUint32(uint32_t* target, uint16_t size);
void clearArrayFloat(float* target, uint16_t size);
void Uint8FromFloat(float *input, uint8_t *outArray);

#endif /*__user_H */

/****END OF FILE****/
