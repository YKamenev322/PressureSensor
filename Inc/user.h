/**
  * File Name: user.h
**/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __user_H
#define __user_H

#include "stm32f1xx_hal.h"

#define ADC_RESULTS_NUMBER 10
#define LED_DELAY 1000
#define ADC_DELAY 20
#define DATA_TO_SEND_SIZE 6
#define TRANSITION_TIMEOUT 1000

struct adcData_struct {
	uint8_t conversions;
	uint32_t results[ADC_RESULTS_NUMBER];
	float average;
};

#define PRESSURE_RESPONSE_CODE 		0xAA

#pragma pack(push, 1)

struct pressureResponse_s
{
	uint8_t code;
	float value;
	uint8_t checksum;
};

#pragma pack(pop)

extern uint8_t input_data;
extern struct adcData_struct adcData;
extern uint8_t dataToSend[DATA_TO_SEND_SIZE];
extern uint8_t transitionDone;
extern uint8_t firsttime;

void clearArrayUint32(uint32_t *target, uint16_t size);
void clearArrayFloat(float *target, uint16_t size);
void Uint8FromFloat(float input, uint8_t *outArray);
void formData();

void AddChecksumm8b(uint8_t *msg, uint16_t length);

#endif /*__user_H */

/****END OF FILE****/
