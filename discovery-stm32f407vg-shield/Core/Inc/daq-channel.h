/*
 * daq-channel.h
 *
 *  Created on: 21 Oct 2021
 *      Author: Artur
 */

#ifndef INC_DAQ_CHANNEL_H_
#define INC_DAQ_CHANNEL_H_

#include "stm32f4xx_hal.h"
#include "stdbool.h"

#include "ntc3950.h"
#include "photodiode.h"
#include "ST7735.h"

#include "menu_definition.h"

#include "main.h"


#define NUMBER_OF_CHANNELS		4

#define CHANNEL_1_GPIO_TypeDef		GPIOD
#define CHANNEL_1_GPIO_Pin			GPIO_PIN_0

#define CHANNEL_2_GPIO_TypeDef		GPIOD
#define CHANNEL_2_GPIO_Pin			GPIO_PIN_1

#define CHANNEL_3_GPIO_TypeDef		GPIOD
#define CHANNEL_3_GPIO_Pin			GPIO_PIN_2

#define CHANNEL_4_GPIO_TypeDef		GPIOD
#define CHANNEL_4_GPIO_Pin			GPIO_PIN_3

typedef enum  {
	DAQ_CH1,
	DAQ_CH2,
	DAQ_CH3,
	DAQ_CH4
} DAQ_channel_no;

struct DAQ_channel {
	uint8_t index;

	GPIO_TypeDef* CHANNEL_GPIOx;
	uint16_t  CHANNEL_GPIO_Pin;

	_Bool flag_enable;


	struct thermistor *th;

	struct photodiode *ph;

	_Bool flag_save;

	_Bool flag_th_limit;
	uint32_t th_limit;

	_Bool flag_ph_limit;
	uint32_t ph_limit;
};

struct DAQ_channel DAQ_channel[NUMBER_OF_CHANNELS];

//struct DAQ_channel *DAQ_channel_SelectChannel(DAQ_channel_no no);


//INIT
void DAQ_channel_init(DAQ_channel_no no, GPIO_TypeDef* CHANNEL_GPIOx,
		uint16_t  CHANNEL_GPIO_Pin, struct thermistor *th, struct photodiode *ph);

//SET
void DAQ_channel_set_index(DAQ_channel_no no, uint8_t i);

void DAQ_channel_set_GPIO_TypeDef(DAQ_channel_no no, GPIO_TypeDef* CHANNEL_GPIOx);
void DAQ_channel_set_GPIO_Pin(DAQ_channel_no no, uint16_t  CHANNEL_GPIO_Pin);

void DAQ_channel_set_flag_enable(DAQ_channel_no no, _Bool flag);
void DAQ_channel_set_thermistor(DAQ_channel_no no, struct thermistor *th);
void DAQ_channel_set_photodiode(DAQ_channel_no no, struct photodiode *ph);
void DAQ_channel_set_flag_save(DAQ_channel_no no, _Bool flag);

void DAQ_channel_set_flag_th_limit(DAQ_channel_no no, _Bool flag);
void DAQ_channel_set_th_limit(DAQ_channel_no no, uint32_t th_limit);

void DAQ_channel_set_flag_ph_limit(DAQ_channel_no no, _Bool flag);
void DAQ_channel_set_ph_limit(DAQ_channel_no no, uint32_t ph_limit);

//GET
uint8_t DAQ_channel_get_index(DAQ_channel_no no);

GPIO_TypeDef *DAQ_channel_get_GPIO_TypeDef(DAQ_channel_no no);
uint16_t DAQ_channel_get_GPIO_Pin(DAQ_channel_no no);

_Bool DAQ_channel_get_flag_enable(DAQ_channel_no no);
struct thermistor *DAQ_channel_get_thermistor(DAQ_channel_no no);
struct photodiode *DAQ_channel_get_photodiode(DAQ_channel_no no);
_Bool DAQ_channel_get_flag_save(DAQ_channel_no no);

_Bool DAQ_channel_get_flag_th_limit(DAQ_channel_no no);
uint32_t DAQ_channel_get_th_limit(DAQ_channel_no no);

_Bool DAQ_channel_get_flag_ph_limit(DAQ_channel_no no);
uint32_t DAQ_channel_get_ph_limit(DAQ_channel_no no);

//ONOFF
void DAQ_channel_off(DAQ_channel_no no);
void DAQ_channel_on(DAQ_channel_no no);

//CHANGE VALUES
void DAQ_CHANGE_temperature_limit(DAQ_channel_no no);
void DAQ_CHANGE_power_limit(DAQ_channel_no no);
void DAQ_CHANGE_enable(DAQ_channel_no no);
void DAQ_CHANGE_save(DAQ_channel_no no);

//CHECK LIMIT
_Bool DAQ_IsLimit(DAQ_channel_no);
#endif /* INC_DAQ_CHANNEL_H_ */
