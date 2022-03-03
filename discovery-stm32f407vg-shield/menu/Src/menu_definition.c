/*
 * menu_definition.c
 *
 *  Created on: May 28, 2021
 *      Author: Artur
 */
#include <menu.h>
#include <system.h>
#include "stdbool.h"
#include "menu_definition.h"
#include "ntc3950.h"
#include "photodiode.h"
#include "main.h"

const struct menuitem  menu_link;
const struct menuitem  menu_link_1;
const struct menuitem  menu_link_2;
const struct menuitem  menu_link_3;

const struct menuitem  menu_link_A1;
const struct menuitem  menu_link_B1;
const struct menuitem  menu_link_C1;
const struct menuitem  menu_link_D1;

const struct menuitem  menu_link_D5 = {PGM_STR("<Back>"), Menu_Back, &menu_link_D1, 0, 0};
const struct menuitem  menu_link_D4 = {PGM_STR("Save to EEPROM"), func_D4, &menu_link_D1, 0, &menu_link_D5};
const struct menuitem  menu_link_D3 = {PGM_STR("Set max P_opt"), func_D3, &menu_link_D1, 0, &menu_link_D4};
const struct menuitem  menu_link_D2 = {PGM_STR("Set max temp_C"), func_D2, &menu_link_D1, 0, &menu_link_D3};
const struct menuitem  menu_link_D1 = {PGM_STR("Enable"), func_D1, &menu_link, 0, &menu_link_D2};

const struct menuitem  menu_link_C5 = {PGM_STR("<Back>"), Menu_Back, &menu_link_C1, 0, 0};
const struct menuitem  menu_link_C4 = {PGM_STR("Save to EEPROM"), func_C4, &menu_link_C1, 0, &menu_link_C5};
const struct menuitem  menu_link_C3 = {PGM_STR("Set max P_opt"), func_C3, &menu_link_C1, 0, &menu_link_C4};
const struct menuitem  menu_link_C2 = {PGM_STR("Set max temp_C"), func_C2, &menu_link_C1, 0, &menu_link_C3};
const struct menuitem  menu_link_C1 = {PGM_STR("Enable"), func_C1, &menu_link, 0, &menu_link_C2};

const struct menuitem  menu_link_B5 = {PGM_STR("<Back>"), Menu_Back, &menu_link_B1, 0, 0};
const struct menuitem  menu_link_B4 = {PGM_STR("Save to EEPROM"), func_B4, &menu_link_B1, 0, &menu_link_B5};
const struct menuitem  menu_link_B3 = {PGM_STR("Set max P_opt"), func_B3, &menu_link_B1, 0, &menu_link_B4};
const struct menuitem  menu_link_B2 = {PGM_STR("Set max temp_C"), func_B2, &menu_link_B1, 0, &menu_link_B3};
const struct menuitem  menu_link_B1 = {PGM_STR("Enable"), func_B1, &menu_link, 0, &menu_link_B2};

const struct menuitem  menu_link_A5 = {PGM_STR("<Back>"), Menu_Back, &menu_link_A1, 0, 0};
const struct menuitem  menu_link_A4 = {PGM_STR("Save to EEPROM"), func_A4, &menu_link_A1, 0, &menu_link_A5};
const struct menuitem  menu_link_A3 = {PGM_STR("Set max P_opt"), func_A3, &menu_link_A1, 0, &menu_link_A4};
const struct menuitem  menu_link_A2 = {PGM_STR("Set max temp_C"), func_A2, &menu_link_A1, 0, &menu_link_A3};
const struct menuitem  menu_link_A1 = {PGM_STR("Enable"), func_A1, &menu_link, 0, &menu_link_A2};

const struct menuitem menu_link_4 = {PGM_STR("Display"), &func_display, &menu_link_3, 0, 0};
const struct menuitem menu_link_3 = {PGM_STR("CH4"), 0, &menu_link_2, &menu_link_D1, &menu_link_4};
const struct menuitem menu_link_2 = {PGM_STR("CH3"), 0, &menu_link_1, &menu_link_C1, &menu_link_3};
const struct menuitem menu_link_1 = {PGM_STR("CH2"), 0, &menu_link, &menu_link_B1, &menu_link_2};
const struct menuitem  menu_link = {PGM_STR("CH1"), 0, 0,  &menu_link_A1, &menu_link_1};

//
/* -------------------------------------------------------------------------------- */
/* -- CHANNEL 1 -- */
/* -------------------------------------------------------------------------------- */

void func_A1() {
	menu_flags.flag_clear_screen = true;
	menu_flags.flag_function = true;
	DAQ_channel_set_flag_enable(DAQ_CH1, true);
}
void func_A2() {
	menu_flags.flag_clear_screen = true;
	menu_flags.flag_function = true;
	DAQ_channel_set_flag_th_limit(DAQ_CH1, true);
}

void func_A3() {
	menu_flags.flag_clear_screen = true;
	menu_flags.flag_function = true;
	DAQ_channel_set_flag_ph_limit(DAQ_CH1, true);
}

void func_A4() {
	menu_flags.flag_clear_screen = true;
	menu_flags.flag_function = true;
	DAQ_channel_set_flag_save(DAQ_CH1, true);
}

/* -------------------------------------------------------------------------------- */
/* -- CHANNEL 2 -- */
/* -------------------------------------------------------------------------------- */
void func_B1(){
	menu_flags.flag_clear_screen = true;
	menu_flags.flag_function = true;
	DAQ_channel_set_flag_enable(DAQ_CH2, true);
}

void func_B2() {
	menu_flags.flag_clear_screen = true;
	menu_flags.flag_function = true;
	DAQ_channel_set_flag_th_limit(DAQ_CH2, true);
}

void func_B3() {
	menu_flags.flag_clear_screen = true;
	menu_flags.flag_function = true;
	DAQ_channel_set_flag_ph_limit(DAQ_CH2, true);
}

void func_B4() {
	menu_flags.flag_clear_screen = true;
	menu_flags.flag_function = true;
	DAQ_channel_set_flag_save(DAQ_CH2, true);
}

/* -------------------------------------------------------------------------------- */
/* -- CHANNEL 3 -- */
/* -------------------------------------------------------------------------------- */
void func_C1() {
	menu_flags.flag_clear_screen = true;
	menu_flags.flag_function = true;
	DAQ_channel_set_flag_enable(DAQ_CH3, true);
}
void func_C2() {
	menu_flags.flag_clear_screen = true;
	menu_flags.flag_function = true;
	DAQ_channel_set_flag_th_limit(DAQ_CH3, true);
}

void func_C3() {
	menu_flags.flag_clear_screen = true;
	menu_flags.flag_function = true;
	DAQ_channel_set_flag_ph_limit(DAQ_CH3, true);
}

void func_C4() {
	menu_flags.flag_clear_screen = true;
	menu_flags.flag_function = true;
	DAQ_channel_set_flag_save(DAQ_CH3, true);
}

/* -------------------------------------------------------------------------------- */
/* -- CHANNEL 4 -- */
/* -------------------------------------------------------------------------------- */
void func_D1(){
	menu_flags.flag_clear_screen = true;
	menu_flags.flag_function = true;
	DAQ_channel_set_flag_enable(DAQ_CH4, true);
}

void func_D2() {
	menu_flags.flag_clear_screen = true;
	menu_flags.flag_function = true;
	DAQ_channel_set_flag_th_limit(DAQ_CH4, true);
}

void func_D3() {
	menu_flags.flag_clear_screen = true;
	menu_flags.flag_function = true;
	DAQ_channel_set_flag_ph_limit(DAQ_CH4, true);
}

void func_D4() {
	menu_flags.flag_clear_screen = true;
	menu_flags.flag_function = true;
	DAQ_channel_set_flag_save(DAQ_CH4, true);
}

/* -------------------------------------------------------------------------------- */
/* -- DISPLAY VALUES -- */
/* -------------------------------------------------------------------------------- */
void func_display(void) {
	menu_flags.flag_clear_screen = true;
	menu_flags.flag_function = true;
	menu_flags.flag_display_measurements = true;
}


void MENU_flags_reset(void) {
	menu_flags.flag_encoder_event = true;

	menu_flags.flag_clear_screen = false;
	menu_flags.flag_show_menu = false;

	menu_flags.flag_function = false;
	menu_flags.flag_change_finish = false;

	menu_flags.flag_CHANGE_value = false;
	menu_flags.flag_CHANGE_cursor = false;
	menu_flags.flag_CHANGE_digit = false;

	menu_flags.flag_display_measurements = false;
}
//------------------------------------------
void MENU_CHANGE_cursor(struct cursor *c) {

	if (encoder_step_clockwise(&encoder_1) == true) {
		if((c->place_value == 0)) {
			c->place_value = 8;
		}
		else {
			(c->place_value)--;
		}
	}
	else if (encoder_step_counterclockwise(&encoder_1) == true) {
		if( (c->place_value == 8) ) {
			c->place_value = 0;
		}
		else {
			(c->place_value)++;
		}

	}

	MENU_SHOW_cursor(c);

}

uint32_t MENU_CHANGE_digit(uint32_t value) {

	if (encoder_step_clockwise(&encoder_1) == true) {
		value = MENU_CALC_value(value, 1, c.place_value);
		MENU_SHOW_value(value);
	}
	else if (encoder_step_counterclockwise(&encoder_1) == true) {
		value = MENU_CALC_value(value, -1,  c.place_value);
		MENU_SHOW_value(value);
	}

	return value;
}

uint32_t MENU_CHANGE_value(uint32_t value) {

	MENU_SHOW_value(value);

	if(menu_flags.flag_CHANGE_cursor) {
		MENU_CHANGE_cursor(&c);
	}
	if(menu_flags.flag_CHANGE_digit) {
		value = MENU_CHANGE_digit(value);
	}

	if(c.place_value != 8 && encoder_enter(&encoder_1)) {
		if(menu_flags.flag_CHANGE_cursor){
			menu_flags.flag_CHANGE_cursor = false;
			menu_flags.flag_CHANGE_digit = true;
		}
		else if(menu_flags.flag_CHANGE_digit){
			menu_flags.flag_CHANGE_digit = false;
			menu_flags.flag_CHANGE_cursor = true;
		}

	}
	if( c.place_value == 8 && encoder_enter(&encoder_1)) {
		menu_flags.flag_CHANGE_cursor = false;
		menu_flags.flag_CHANGE_digit = false;
		menu_flags.flag_CHANGE_value = false;
		menu_flags.flag_function = true;
		menu_flags.flag_show_menu = true;
		menu_flags.flag_change_finish = true;
		c.place_value = 2;
	}
	return value;
}

uint32_t MENU_CALC_value(uint32_t value_in, int8_t direction, uint8_t dec) {
	int32_t value_out = 0;

	switch (dec)
	{
	case 0:
		value_out = value_in + ( (int32_t) direction * 1);
		break;
	case 1:
		value_out = value_in + ( (int32_t) direction * 10);
		break;
	case 2:
		value_out = value_in + ( (int32_t) direction * 100);
		break;
	case 3:
		value_out = value_in + ( (int32_t) direction * 1000);
		break;
	case 4:
		value_out = value_in + ( (int32_t) direction * 10000);
		break;
	case 5:
		value_out = value_in + ( (int32_t) direction * 100000);
		break;
	case 6:
		value_out = value_in + ( (int32_t) direction * 1000000);
		break;
	case 7:
		value_out = value_in + ( (int32_t) direction * 10000000);
		break;
	default:
		break;
	}
	if (value_out < 0) value_out = 0;
	if (value_out > 99999999) value_out = 99999999;
	return (uint32_t) value_out;
}

void MENU_SHOW_value(uint32_t value) {
	char buffer[20];
	uint8_t cijfer[8];

	if (value <= 99999999)
	{
		for (uint8_t i = 0; i < 8; i++)
		{
			cijfer[i] = (uint8_t) (value % 10) + 48;
			value /= 10;
		}
		sprintf(buffer, "%c%c%c %c%c%c.%c%c", cijfer[7], cijfer[6], cijfer[5], cijfer[4], cijfer[3], cijfer[2], cijfer[1], cijfer[0]);
		UG_FillFrame(2, gui1.font.font_height, UG_GetXDim(), 2*gui1.font.font_height, C_BLACK);
		UG_PutString(2, gui1.font.font_height, buffer );

	}

}

void MENU_SHOW_cursor(struct cursor *c) {
	uint8_t cursor_position = 0;

	switch (c->place_value)
	{
	case 0:
		cursor_position = 2+(9*gui1.font.font_width);
		break;
	case 1:
		cursor_position = 2+(8*gui1.font.font_width);
		break;
	case 2:
		cursor_position = 2+(6*gui1.font.font_width);
		break;
	case 3:
		cursor_position = 2+(5*gui1.font.font_width);
		break;
	case 4:
		cursor_position = 2+(4*gui1.font.font_width);
		break;
	case 5:
		cursor_position = 2+(2*gui1.font.font_width);
		break;
	case 6:
		cursor_position = 2+(1*gui1.font.font_width);
		break;
	case 7:
		cursor_position = 2+(0*gui1.font.font_width);
		break;
	case 8:
		cursor_position = 2+(0*gui1.font.font_width);
		break;
	default:
		break;
	}

	if(c->place_value != c->previous_place_value) {
		UG_FillFrame(0, 2*gui1.font.font_height, UG_GetXDim(), 3*gui1.font.font_height, C_BLACK);
		UG_PutString( cursor_position, 2*gui1.font.font_height, "^" );
		c->previous_place_value = c->place_value;
	}
	else if(c->place_value == 8) {
		UG_PutString( cursor_position, gui1.font.font_height+(1*gui1.font.font_height), "<Back>" );
	}
	else {
		UG_PutString( cursor_position, gui1.font.font_height+(1*gui1.font.font_height), "^" );
	}

}
