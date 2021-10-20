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

#ifndef __SYSTEM_H
#define __SYSTEM_H

/* Include headers */

#include "stm32f4xx.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <menu.h>
#include <string.h>

//#include "i2c-lcd.h"
#include "i2c-eeprom.h"
#include "ntc3950.h"
#include "photodiode.h"


// graphical user interface headers
#include "menu_definition.h"
#include <encoder.h>
#include <GFX_FUNCTIONS.h>
#include <ST7735.h>
#include <ugui.h>



/* Private define */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Function prototypes, name aligned, lowercase names */

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif

