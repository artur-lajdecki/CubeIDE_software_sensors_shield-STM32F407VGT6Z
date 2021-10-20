/*
 * photodiode.h
 *
 *  Created on: Jul 1, 2021
 *      Author: Artur
 */

#ifndef INC_PHOTODIODE_H_
#define INC_PHOTODIODE_H_

#include "stm32f4xx_hal.h"

struct photodiode {
	uint32_t ADC_max_val;
	uint32_t optical_power_max;
	_Bool save_settings;
	uint8_t place_value;
	uint8_t previous_place_value;
};

//struct photodiode photodiode_1;
//struct photodiode photodiode_2;
//struct photodiode photodiode_3;
//struct photodiode photodiode_4;

struct photodiode photodiode[4];

void photodiode_init(struct photodiode *ph, float ph_power);

uint32_t photodiode_power_to_ADC(float ph_power);

float photodiode_ADC_to_power(uint32_t ADC_value, uint32_t ADC_VREFINT_value);
#endif /* INC_PHOTODIODE_H_ */
