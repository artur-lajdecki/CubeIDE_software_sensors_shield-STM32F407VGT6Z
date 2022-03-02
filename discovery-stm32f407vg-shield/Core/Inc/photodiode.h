/*
 * photodiode.h
 *
 *  Created on: Jul 1, 2021
 *      Author: Artur
 */

#ifndef INC_PHOTODIODE_H_
#define INC_PHOTODIODE_H_

#include "stm32f4xx_hal.h"

#define PHOTODIODE_QUANTITY 4

struct photodiode {
	float power_value; //Calculated power in mW

	float power_max_value;
	uint32_t ADC_max_value; //Limit for raw ADC readings of photodiode
};
struct photodiode photodiode[PHOTODIODE_QUANTITY];

void photodiode_init(struct photodiode *ph, float power_max_value);
uint32_t photodiode_power_to_ADC(float power_value, uint32_t ADC_VREFINT_value);
float photodiode_ADC_to_power(uint32_t ADC_value, uint32_t ADC_VREFINT_value);

#endif /* INC_PHOTODIODE_H_ */
