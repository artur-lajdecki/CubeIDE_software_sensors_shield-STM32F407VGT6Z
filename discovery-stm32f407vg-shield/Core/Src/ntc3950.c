/*
 * ntc3950.c
 *
 *  Created on: Jun 10, 2021
 *      Author: Artur
 */

#include  "ntc3950.h"
#include "stm32f4xx_hal.h"
#include "stdbool.h"
#include "math.h"
#include "main.h"

void thermistor_init(struct thermistor *th, float th_temp_C) {
	th->temperature_C_max = (uint32_t) (th_temp_C*100);
	th->ADC_max_val = ntc3950_Celcius_to_ADC(th_temp_C, ADC1read[8]);
}

uint32_t ntc3950_Celcius_to_ADC(float th_temp_C, uint32_t ADC_VREFINT_value) {

	float vrefint = 0; 	//Reference internal voltage
	float vrefext = 0; 	//External voltage calculated based on vrefint
	float vmeas = 0; 	//Measured voltage in volts [V]
	float Rntc = 0; 	//Resistance of the thermistor

	vrefint = VCAL * (*TEMP30_CAL_ADDR) / ADC_BUF_LEN;
	vrefext = vrefint * ADC_BUF_LEN / ADC_VREFINT_value;

	float tmp_value = 0;

	tmp_value = th_temp_C + 273.15f;
	tmp_value = 1.0f / tmp_value;
	tmp_value -= 1.0f / ((float)_NTC_TEMP_NOMINAL + 273.15f);
	tmp_value = tmp_value * (float)_NTC_BETA;
	tmp_value = expf(tmp_value);

	Rntc = (float)tmp_value * (float)_NTC_R_NOMINAL;

	vmeas = ((Rntc * vrefext) / ((float)_NTC_R_NOMINAL))/(1+(Rntc/(float)_NTC_R_NOMINAL));

	tmp_value = (vmeas * ADC_BUF_LEN) / vrefext;

	return tmp_value;


}

float ntc3950_ADC_to_Celcius(uint32_t ADC_value, uint32_t ADC_VREFINT_value)
{
	float vrefint = 0; 	//Reference internal voltage
	float vrefext = 0; 	//External voltage calculated based on vrefint
	float vmeas = 0; 	//Measured voltage in volts [V]
	float Rntc = 0; 	//Resistance of the thermistor
	float temp_C = 0; 	//Calculated temperature in Celcius

	vrefint = VCAL * (*TEMP30_CAL_ADDR) / ADC_BUF_LEN;
	vrefext = vrefint * ADC_BUF_LEN / ADC_VREFINT_value;
	vmeas = vrefext * ADC_value / ADC_BUF_LEN;

	// Calculating Resistance of the NTC Vmeasured*10kOhms
	Rntc= (vmeas*(float)_NTC_R_NOMINAL)/(vrefext-vmeas);

	// Calculating Temperature
	temp_C = Rntc/(float)_NTC_R_NOMINAL;
	temp_C = logf(temp_C);
	temp_C = temp_C/(float)_NTC_BETA;
	temp_C += 1.0f / ((float)_NTC_TEMP_NOMINAL + 273.15f);
	temp_C = 1.0f/temp_C;
	temp_C -= 273.15f;

	return temp_C;
}
