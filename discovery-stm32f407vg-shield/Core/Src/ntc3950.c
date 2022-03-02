/*
 * ntc3950.c
 *
 *  Created on: Jun 10, 2021
 *      Author: Artur
 */

#include "stm32f4xx_hal.h"
#include  "ntc3950.h"
#include "adc.h"
#include "main.h"
#include "stdbool.h"
#include "math.h"

void thermistor_init(struct thermistor *th, float temperature_max_value) {
	th->temperature_max_value = temperature_max_value;
	th->ADC_max_value = ntc3950_Celcius_to_ADC(temperature_max_value, ADC1read[8]);
}

uint32_t ntc3950_Celcius_to_ADC(float temperature_value, uint32_t ADC_VREFINT_value) {

//	float vrefint = 0; 	//Reference internal voltage
//	float vrefext = 0; 	//External voltage calculated based on vrefint

	float V_DDA = 0; 	//Actual analog voltage calculated based on internal reference voltage
	float vmeas = 0; 	//Measured voltage in volts [V]
	double Rntc = 0; 	//Resistance of the thermistor
	uint32_t ADC_value = 0; // Calculated ADC value



//	vrefint = VCAL * (*TEMP30_CAL_ADDR) / ADC_BUF_LEN;
//	vrefext = vrefint * ADC_BUF_LEN / ADC_VREFINT_value;

	V_DDA = VCAL * (*TEMP30_CAL_ADDR) / ADC_VREFINT_value;

	//	We can compute a resistance for a measured temperature:
	//	R2 = R1 / (exp( B*(1/ T1 - 1/ T2) )) or R = Ro * e^(B * (1/T - 1/To)) where Ro = R0
	//	is the resistance at temperature T0 (25 °C = 298.15 K)
	//	Note that T has units of Kelvin.
	//	Where:
	//	- B = beta coefficient
	//	- R1 = resistance at 25C
	//	- T1 = nominal temperature 25C
	// 	- T2 = measured temperature

//	Rntc = ((float)_NTC_BETA) * ( (1/((float)_NTC_TEMP_NOMINAL) + 273.15f) - (1/temperature_value + 273.15f) );
//	Rntc = exp(Rntc);
//	Rntc = (float)_NTC_R_NOMINAL / Rntc;

	double T = temperature_value + 273.15;
	double To = _NTC_TEMP_NOMINAL + 273.15;


	Rntc = ( 1/T - 1 / To);
	Rntc = ((float)_NTC_BETA) * Rntc;
	Rntc = exp(Rntc);
	Rntc = (float)_NTC_R_NOMINAL * Rntc;

	vmeas = (Rntc * V_DDA) / (Rntc + (float)_NTC_R_NOMINAL);

	ADC_value = (vmeas * ADC_BUF_LEN) / V_DDA;

	return ADC_value;


}

float ntc3950_ADC_to_Celcius(uint32_t ADC_value, uint32_t ADC_VREFINT_value)
{
//	float vrefint = 0; 	//Reference internal voltage
//	float vrefext = 0; 	//External voltage calculated based on vrefint

	float V_DDA = 0; 	//Actual analog voltage calculated based on internal reference voltage
	float vmeas = 0; 	//Measured voltage in volts [V]
	float Rntc = 0; 	//Resistance of the thermistor
	float temp_C = 0; 	//Calculated temperature in Celcius

//	vrefint = VCAL * (*TEMP30_CAL_ADDR) / ADC_BUF_LEN;
//	vrefext = vrefint * ADC_BUF_LEN / ADC_VREFINT_value;

	V_DDA = VCAL * (*TEMP30_CAL_ADDR) / ADC_VREFINT_value;
	vmeas = (V_DDA / ADC_BUF_LEN) * ADC_value;

	// Calculating Resistance of the NTC Vmeasured*10kOhms
	Rntc= (vmeas * (float)_NTC_R_NOMINAL) / (V_DDA - vmeas);

	//	We can compute a resistance for a measured temperature:
	//	T2= T1*B/ln(R1/R2) / ( B/ln(R1/R2) - T1 ) ,
	//	Where:
	//	Note that T has units of Kelvin.
	//	- B = beta coefficient
	//	- R1 = resistance at 25C
	//	- R2 = measured resistance
	//	- T1 = nominal temperature 25C

	// Calculating Temperature
	temp_C = Rntc/(float)_NTC_R_NOMINAL;
	temp_C = logf(temp_C);
	temp_C = temp_C/(float)_NTC_BETA;
	temp_C += 1.0f / ((float)_NTC_TEMP_NOMINAL + 273.15f);
	temp_C = 1.0f/temp_C;
	temp_C -= 273.15f;

	return temp_C;
}
