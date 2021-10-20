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

//void menufunc1()
//{
//  UG_WindowShow( &window_1 );
//  UG_Update();
////  button1_1->str =
////  UG_OBJECT* obj = _UG_SearchObject( UG_WINDOW* wnd, UG_U8 type, UG_U8 id );
//}
//

void DAQ_channel_init( float ph_power, float th_temp_C, uint8_t channel_no) {
	switch(channel_no) {
	case 0:
		photodiode_init(&photodiode[0], ph_power);
		thermistor_init(&thermistor[0], th_temp_C);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0,GPIO_PIN_RESET); //transistor closed -> channel open
		flag_channel[0] = 1;
		break;

	case 1:
		photodiode_init(&photodiode[1], ph_power);
		thermistor_init(&thermistor[1], th_temp_C);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1,GPIO_PIN_RESET);
		flag_channel[1] = 1;
		break;

	case 2:
		photodiode_init(&photodiode[2], ph_power);
		thermistor_init(&thermistor[2], th_temp_C);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2,GPIO_PIN_RESET);
		flag_channel[2] = 1;
		break;

	case 3:
		photodiode_init(&photodiode[3], ph_power);
		thermistor_init(&thermistor[3], th_temp_C);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3,GPIO_PIN_RESET);
		flag_channel[3] = 1;
		break;
	}
}
//
/* -------------------------------------------------------------------------------- */
/* -- CHANNEL 1 -- */
/* -------------------------------------------------------------------------------- */
void func_A1() {
//enable
}
void func_A2() {
	MENU_CHANGE_value(&thermistor[0]);
}

void func_A3() {
//set photodiode limit
}

void func_A4() {
//save values to eeprom
}

/* -------------------------------------------------------------------------------- */
/* -- CHANNEL 2 -- */
/* -------------------------------------------------------------------------------- */
void func_B1(){

}

void func_B2() {

}

void func_B3() {

}

void func_B4() {

}

/* -------------------------------------------------------------------------------- */
/* -- CHANNEL 3 -- */
/* -------------------------------------------------------------------------------- */
void func_C1() {

}
void func_C2() {

}

void func_C3() {

}

void func_C4() {

}

/* -------------------------------------------------------------------------------- */
/* -- CHANNEL 4 -- */
/* -------------------------------------------------------------------------------- */
void func_D1(){

}

void func_D2() {

}

void func_D3() {

}

void func_D4() {

}


void func_display(void) {
	ST7735_FillScreen(BLACK);
	while( (encoder_enter(&encoder_1)) == false) {
		display_values();
	}
}

void MENU_CHANGE_cursor(struct thermistor *th) {


	while(encoder_enter(&encoder_1) == false) {

		if (encoder_step_clockwise(&encoder_1) == true)
		{
			if((th->place_value == 0)) {
				th->place_value = 8;
			}
			else{
				(th->place_value)--;
			}
		}
		else if (encoder_step_counterclockwise(&encoder_1) == true)
		{
			if( (th->place_value == 8) ) {
				th->place_value = 0;
			}
			else {
				(th->place_value)++;
			}

		}

		MENU_SHOW_cursor(th);
	}
}

void MENU_CHANGE_value(struct thermistor *th) {
	UG_FillScreen( C_BLACK );
	MENU_SHOW_value(th->temperature_C_max);
	MENU_SHOW_cursor(th);
	MENU_CHANGE_cursor(th);

	if(th->place_value != 8){
		while(encoder_enter(&encoder_1) == false) {

			if (encoder_step_clockwise(&encoder_1) == true)
			{
				th->temperature_C_max = MENU_CALC_value(th->temperature_C_max, 1, th->place_value);
				MENU_SHOW_value(th->temperature_C_max);
			}
			if (encoder_step_counterclockwise(&encoder_1) == true)
			{
				th->temperature_C_max = MENU_CALC_value(th->temperature_C_max, -1,  th->place_value);
				MENU_SHOW_value(th->temperature_C_max);
			}
		}
		MENU_CHANGE_value(th);
	}
	else {

		///???????????????????????????
	}


}


uint32_t MENU_CALC_value(uint32_t value_in, int8_t direction, uint8_t dec) {
	uint32_t value_out = 0;

	switch (dec)
	{
	case 0:
		value_out = value_in + (direction * 1);
		break;
	case 1:
		value_out = value_in + (direction * 10);
		break;
	case 2:
		value_out = value_in + (direction * 100);
		break;
	case 3:
		value_out = value_in + (direction * 1000);
		break;
	case 4:
		value_out = value_in + (direction * 10000);
		break;
	case 5:
		value_out = value_in + (direction * 100000);
		break;
	case 6:
		value_out = value_in + (direction * 1000000);
		break;
	case 7:
		value_out = value_in + (direction * 10000000);
		break;
	default:
		break;
	}
	if (value_out < 0) value_out = 0;
	if (value_out > 99999999) value_out = 99999999;
	return value_out;
}

void MENU_SHOW_value(uint32_t value) {
	char buffer[20];
	uint8_t cijfer[8];

	if (value <= 99999)
	{
		for (uint8_t i = 0; i < 8; i++)
		{
			cijfer[i] = (uint8_t) (value % 10) + 48;
			value /= 10;
		}
		sprintf(buffer, "%c%c%c %c%c%c.%c%c", cijfer[7], cijfer[6], cijfer[5], cijfer[4], cijfer[3], cijfer[2], cijfer[1], cijfer[0]);
		UG_FillFrame(0, gui1.font.font_height+(0*gui1.font.font_height), UG_GetXDim(), (gui1.font.font_height)+(gui1.font.font_height+(0*gui1.font.font_height)), C_BLACK);
		UG_PutString(2, gui1.font.font_height+(0*gui1.font.font_height), buffer );

	}
	else {
		UG_PutString( 2, 50, "   Error");

	}

}

void MENU_SHOW_cursor(struct thermistor *th) {
	uint8_t cursor_position = 0;

//	uint8_t font_width = gui1.font.char_width+gui1.font.char_h_space;
//	uint8_t font_height = gui1.font.char_height+gui1.font.char_v_space;

	switch (th->place_value)
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

	if(th->place_value != th->previous_place_value) {
		UG_FillFrame(0, gui1.font.font_height+(1*gui1.font.font_height), UG_GetXDim(), gui1.font.font_height+(2*gui1.font.font_height), C_BLACK);
		UG_PutString( cursor_position, gui1.font.font_height+(1*gui1.font.font_height), "^" );
		th->previous_place_value = th->place_value;
	}
	else if(th->place_value == 8) {
		UG_PutString( cursor_position, gui1.font.font_height+(1*gui1.font.font_height), "<Back>" );
	}
	else {
		UG_PutString( cursor_position, gui1.font.font_height+(1*gui1.font.font_height), "^" );
	}

}
