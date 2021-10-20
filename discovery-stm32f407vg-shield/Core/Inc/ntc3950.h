#ifndef INC_NTC3950_H_
#define INC_NTC3950_H_

#include "stm32f4xx_hal.h"

#define _NTC_R_SERIES         10000.0f
#define _NTC_R_NOMINAL        10000.0f
#define _NTC_TEMP_NOMINAL     25.0f
#define _NTC_ADC_MAX          4096 // 12bit
#define _NTC_BETA             3950

#define THERMISTOR_QUANTITY 4

#define ADC_BUF_LEN 4095 // Resolution of ADC
#define TEMP30_CAL_ADDR ((uint16_t*) ((uint32_t) 0x1FFF7A2A)) //Raw data acquired at temperature of 30 °C VDDA = 3.3 V
															  //ST did a measurement for us when manufacturing the chip,
															  //using a precise external reference voltage on the VREF+ pin,
				 	 	 	 	 	 	 	 	 	 	 	  //and stored the resulting ADC reading into the system memory

#define VCAL 3.3	//The voltage used as external reference at calibration. Put as 330 instead 3.3V to avoid float, vmeasured would be in 10mV units





struct thermistor {
	uint32_t ADC_max_val;
	uint32_t temperature_C_max;
	_Bool save_settings;
	uint8_t place_value;
	uint8_t previous_place_value;
};

//struct thermistor thermistor_1;
//struct thermistor thermistor_2;
//struct thermistor thermistor_3;
//struct thermistor thermistor_4;

struct thermistor thermistor[4];

void thermistor_init(struct thermistor *th, float th_temp_C);

float ntc3950_ADC_to_Celcius(uint32_t ADC_value, uint32_t ADC_VREFINT_value);

uint32_t ntc3950_Celcius_to_ADC(float th_temp_C, uint32_t ADC_VREFINT_value);

#endif /* INC_NTC3950_H_ */
