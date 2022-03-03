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
#include "daq-channel.h"

/* Private define */
#define PGM_STR(X) ((char[]) { X })


//char CH1_status_string[];
//char CH2_status_string[];
//char CH3_status_string[];
//char CH4_status_string[];

uint8_t current_channel;

struct menu_flags {
	_Bool flag_encoder_event;

	_Bool flag_clear_screen;
	_Bool flag_show_menu;

	_Bool flag_function;
	_Bool flag_change_finish;

	_Bool flag_CHANGE_temperature;
	_Bool flag_CHANGE_power;

	_Bool flag_CHANGE_value;
	_Bool flag_CHANGE_cursor;
	_Bool flag_CHANGE_digit;

	_Bool flag_display_measurements;
};

struct menu_flags menu_flags;

struct cursor {
	uint8_t place_value; //Place of a cursor
	uint8_t previous_place_value;
};

struct cursor c;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Function prototypes, name aligned, lowercase names */

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

void MENU_flags_reset(void);

void MENU_CHANGE_cursor(struct cursor *c);

uint32_t MENU_CHANGE_value(uint32_t value);

uint32_t MENU_CHANGE_digit(uint32_t value);

void MENU_SHOW_value(uint32_t value);

void MENU_SHOW_cursor(struct cursor *c);

uint32_t MENU_CALC_value(uint32_t value_in, int8_t direction, uint8_t dec);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* INC_MENU_DEFINITION_H_ */
