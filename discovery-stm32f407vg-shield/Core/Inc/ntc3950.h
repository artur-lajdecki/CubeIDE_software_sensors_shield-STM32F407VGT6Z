#ifndef INC_NTC3950_H_
#define INC_NTC3950_H_

#include "stm32f4xx_hal.h"

//Parameters for simplified B parameter equation

#define THERMISTOR_QUANTITY 4

#define _NTC_R_SERIES         10000.0f
#define _NTC_R_NOMINAL        10000.0f
#define _NTC_TEMP_NOMINAL     25.0f
#define _NTC_ADC_MAX          4096 // 12bit
#define _NTC_BETA             3950

struct thermistor {
	float temperature_value; //Calculated temperature in Celcius

	float temperature_max_value;
	uint32_t ADC_max_value; //Limit for raw ADC readings of thermistor
};
struct thermistor thermistor[THERMISTOR_QUANTITY];

void thermistor_init(struct thermistor *th, float temperature_max_value);
float ntc3950_ADC_to_Celcius(uint32_t ADC_value, uint32_t ADC_VREFINT_value);
uint32_t ntc3950_Celcius_to_ADC(float temperature_value, uint32_t ADC_VREFINT_value);


#endif /* INC_NTC3950_H_ */
