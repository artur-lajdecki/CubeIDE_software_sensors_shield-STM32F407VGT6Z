/*
 * photodiode.c
 *
 *  Created on: Jul 1, 2021
 *      Author: Artur
 */

#include "photodiode.h"
#include "stm32f4xx_hal.h"
#include "stdbool.h"

void photodiode_init(struct photodiode *ph, float ph_power) {
	ph->optical_power_max = (uint32_t)(ph_power*100);
	ph->ADC_max_val = photodiode_power_to_ADC(ph_power);
}

uint32_t photodiode_power_to_ADC(float ph_power) {

	uint32_t ADC_value = 0;
	const float a = 7.84;
	const float b = 51.88;

	ADC_value = (uint32_t) (a * ph_power - b);

	return ADC_value;
}

float photodiode_ADC_to_power(uint32_t ADC_value, uint32_t ADC_VREFINT_value){

	float power_value = 0;
	const float a = 7.84;
	const float b = 51.88;

	power_value = (ADC_value + b) / a;

	return power_value;

}
