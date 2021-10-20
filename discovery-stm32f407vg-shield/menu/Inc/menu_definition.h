/*
 * Copyright (c) 2021 Artur Lajdecki
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * This file is part of Application.
 *
 * Author:          Artur Lajdecki <249116@student.pwr.edu.pl>
 */

#ifndef INC_MENU_DEFINITION_H_
#define INC_MENU_DEFINITION_H_

/* Include headers */
#include "stm32f4xx.h"
#include "ntc3950.h"
#include "stdbool.h"

/* Private define */
#define PGM_STR(X) ((char[]) { X })


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Function prototypes, name aligned, lowercase names */
//_Bool flag_channel[4];

extern _Bool flag_channel[4];

_Bool flag_channel[4];

enum DAQ_channels {
	DAQ_CH1, DAQ_CH2, DAQ_CH3, DAQ_CH4
};

//struct DAQ{
//	_Bool flag_channel_en;
//
//};

//Prototypes of menu functions
void func_A1();
void func_A2();
void func_A3();
void func_A4();

void func_B1();
void func_B2();
void func_B3();
void func_B4();

void func_C1();
void func_C2();
void func_C3();
void func_C4();

void func_D1();
void func_D2();
void func_D3();
void func_D4();

void func_display(void);

void MENU_CHANGE_cursor(struct thermistor *th);

void MENU_CHANGE_value(struct thermistor *th);

void MENU_SHOW_value(uint32_t value);

void MENU_SHOW_cursor(struct thermistor *th);

uint32_t MENU_CALC_value(uint32_t value_in, int8_t direction, uint8_t dec);


void DAQ_channel_init( float ph_power, float th_temp_C, uint8_t channel_no);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* INC_MENU_DEFINITION_H_ */
