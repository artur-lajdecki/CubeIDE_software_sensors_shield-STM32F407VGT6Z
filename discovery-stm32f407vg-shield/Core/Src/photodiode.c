/*
 * photodiode.c
 *
 *  Created on: Jul 1, 2021
 *      Author: Artur
 */

#include "stm32f4xx_hal.h"
#include "photodiode.h"
#include "adc.h"
#include "main.h"
#include "stdbool.h"


void photodiode_init(struct photodiode *ph, float power_max_value) {
	ph->power_max_value = power_max_value;
	ph->ADC_max_value = photodiode_power_to_ADC(power_max_value, ADC1read[8]);
}

uint32_t photodiode_power_to_ADC(float power_value, uint32_t ADC_VREFINT_value) {

	float V_DDA = 0; 	//Actual analog voltage calculated based on internal reference voltage
	float vmeas = 0; 	//Measured voltage in volts [V]
	uint32_t ADC_value = 0;

	V_DDA = VCAL * (*TEMP30_CAL_ADDR) / ADC_VREFINT_value;

	//Coefficients based on linear regression
	const float a = 7.84;
	const float b = 51.88;

	vmeas = (uint32_t) (a * power_value - b);
	ADC_value = (vmeas * ADC_BUF_LEN) / V_DDA;
	return ADC_value;
}

float photodiode_ADC_to_power(uint32_t ADC_value, uint32_t ADC_VREFINT_value){

	float V_DDA = 0; 	//Actual analog voltage calculated based on internal reference voltage
	float vmeas = 0; 	//Measured voltage in volts [V]
	float power_value = 0;

	V_DDA = VCAL * (*TEMP30_CAL_ADDR) / ADC_VREFINT_value;
	vmeas = (V_DDA / ADC_BUF_LEN) * ADC_value;

	//Coefficients based on linear regression
	const float a = 7.84;
	const float b = 51.88;

	power_value = (vmeas + b) / a;

	return power_value;

}
