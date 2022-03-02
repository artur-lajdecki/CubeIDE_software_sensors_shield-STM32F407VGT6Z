/*
 * daq-channel.c
 *
 *  Created on: 21 Oct 2021
 *      Author: Artur
 */

#include "daq-channel.h"

//struct DAQ_channel *DAQ_channel_SelectChannel(DAQ_channel_no no) {
//	return &DAQ_channel[no];
//}

void DAQ_channel_init(DAQ_channel_no no, GPIO_TypeDef* CHANNEL_GPIOx,
		uint16_t  CHANNEL_GPIO_Pin, struct thermistor *th, struct photodiode *ph) {

	DAQ_channel_set_index(no, no);
	DAQ_channel_set_GPIO_TypeDef(no, CHANNEL_GPIOx);
	DAQ_channel_set_GPIO_Pin(no, CHANNEL_GPIO_Pin);
	DAQ_channel_set_thermistor(no, th);
	DAQ_channel_set_photodiode(no, ph);

}

void DAQ_channel_set_index(DAQ_channel_no no, uint8_t i) {
	DAQ_channel[no].index = i;
}

void DAQ_channel_set_GPIO_TypeDef(DAQ_channel_no no, GPIO_TypeDef* CHANNEL_GPIOx) {
	DAQ_channel[no].CHANNEL_GPIOx = CHANNEL_GPIOx;
}

void DAQ_channel_set_GPIO_Pin(DAQ_channel_no no, uint16_t  CHANNEL_GPIO_Pin) {
	DAQ_channel[no].CHANNEL_GPIO_Pin = CHANNEL_GPIO_Pin;
}

void DAQ_channel_set_flag_enable(DAQ_channel_no no, _Bool flag) {
	DAQ_channel[no].flag_enable = flag;
}

void DAQ_channel_set_thermistor(DAQ_channel_no no, struct thermistor *th) {
	DAQ_channel[no].th = th;
}

void DAQ_channel_set_photodiode(DAQ_channel_no no, struct photodiode *ph) {
	DAQ_channel[no].ph = ph;
}

void DAQ_channel_set_flag_save(DAQ_channel_no no, _Bool flag) {
	DAQ_channel[no].flag_save = flag;
}

void DAQ_channel_set_flag_th_limit(DAQ_channel_no no, _Bool flag) {
	DAQ_channel[no].flag_th_limit = flag;
}

void DAQ_channel_set_th_limit(DAQ_channel_no no, uint32_t th_limit) {
	DAQ_channel[no].th_limit = th_limit;
	DAQ_channel[no].th->temperature_max_value = ((float)DAQ_channel[no].th_limit/100);
	DAQ_channel[no].th->ADC_max_value = ntc3950_Celcius_to_ADC(DAQ_channel[no].th->temperature_max_value, ADC1read[8]);
}

void DAQ_channel_set_flag_ph_limit(DAQ_channel_no no, _Bool flag) {
	DAQ_channel[no].flag_ph_limit = flag;
}

void DAQ_channel_set_ph_limit(DAQ_channel_no no, uint32_t ph_limit) {
	DAQ_channel[no].ph_limit = ph_limit;
	DAQ_channel[no].ph->power_max_value = ((float)DAQ_channel[no].ph_limit/100);
	DAQ_channel[no].ph->ADC_max_value = photodiode_power_to_ADC(DAQ_channel[no].ph->power_max_value, ADC1read[8]);

}

//GET
uint8_t DAQ_channel_get_index(DAQ_channel_no no) {
	return DAQ_channel[no].index;

}

GPIO_TypeDef *DAQ_channel_get_GPIO_TypeDef(DAQ_channel_no no) {
	return DAQ_channel[no].CHANNEL_GPIOx;

}

uint16_t DAQ_channel_get_GPIO_Pin(DAQ_channel_no no) {
	return DAQ_channel[no].CHANNEL_GPIO_Pin;

}

_Bool DAQ_channel_get_flag_enable(DAQ_channel_no no) {
	return DAQ_channel[no].flag_enable;
}

struct thermistor *DAQ_channel_get_thermistor(DAQ_channel_no no) {
	return DAQ_channel[no].th;
}

struct photodiode *DAQ_channel_get_photodiode(DAQ_channel_no no) {
	return DAQ_channel[no].ph;
}

_Bool DAQ_channel_get_flag_save(DAQ_channel_no no) {
	return DAQ_channel[no].flag_save;
}

_Bool DAQ_channel_get_flag_th_limit(DAQ_channel_no no) {
	return DAQ_channel[no].flag_th_limit;
}

uint32_t DAQ_channel_get_th_limit(DAQ_channel_no no) {
	return DAQ_channel[no].th_limit;
}

_Bool DAQ_channel_get_flag_ph_limit(DAQ_channel_no no) {
	return DAQ_channel[no].flag_ph_limit;
}

uint32_t DAQ_channel_get_ph_limit(DAQ_channel_no no) {
	return DAQ_channel[no].ph_limit;
}

//ONOFF
void DAQ_channel_off(DAQ_channel_no no) {
	DAQ_channel_set_flag_enable(no, false);
	HAL_GPIO_WritePin(DAQ_channel_get_GPIO_TypeDef(no), DAQ_channel_get_GPIO_Pin(no), GPIO_PIN_SET); //transistor open -> channel closed
}

void DAQ_channel_on(DAQ_channel_no no) {
	DAQ_channel_set_flag_enable(no, true);
	HAL_GPIO_WritePin(DAQ_channel_get_GPIO_TypeDef(no), DAQ_channel_get_GPIO_Pin(no), GPIO_PIN_RESET); //transistor closed -> channel open
}


//CHANGE
void DAQ_CHANGE_temperature_limit(DAQ_channel_no no) {
	DAQ_channel[no].th_limit = MENU_CHANGE_value(DAQ_channel[no].th_limit);
	DAQ_channel[no].th->temperature_max_value = ((float)DAQ_channel[no].th_limit/100);
	DAQ_channel[no].th->ADC_max_value = ntc3950_Celcius_to_ADC(DAQ_channel[no].th->temperature_max_value, ADC1read[8]);
}

void DAQ_CHANGE_power_limit(DAQ_channel_no no) {
	DAQ_channel[no].ph_limit = MENU_CHANGE_value(DAQ_channel[no].ph_limit);
	DAQ_channel[no].ph->power_max_value =  ((float)DAQ_channel[no].ph_limit/100);
	DAQ_channel[no].ph->ADC_max_value = photodiode_power_to_ADC(DAQ_channel[no].ph->power_max_value, ADC1read[8]);

}

void DAQ_CHANGE_enable(DAQ_channel_no no) {
	ST7735_WriteString(2, 2+(30*0), "Channel has been turned: ", Font_7x10, WHITE, BLACK);

	if(DAQ_channel_get_flag_enable(no)){
		DAQ_channel_off(no);
		ST7735_WriteString(2, 2+(30*2), "OFF", Font_16x26, RED, BLACK);
	}
	else {
		DAQ_channel_on(no);
		ST7735_WriteString(2, 2+(30*2), "ON", Font_16x26, GREEN, BLACK);
	}
	DAQ_channel_set_flag_enable(no, false);
}

void DAQ_CHANGE_save(DAQ_channel_no no) {
	ST7735_WriteString(2, 2+(30*2), "Settings saved", Font_16x26, GREEN, BLACK);

	DAQ_channel_set_flag_save(no, false);
}
_Bool DAQ_IsLimit(DAQ_channel_no no) {
	if (ADC1read[no+4] >= DAQ_channel[no].ph->ADC_max_value || ADC1read[no] <= DAQ_channel[no].th->ADC_max_value) {
		return true;
	}
	else
	return false;
}

