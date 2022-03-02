/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    adc.h
  * @brief   This file contains all the function prototypes for
  *          the adc.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ADC_H__
#define __ADC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#define ADC_BUF_LEN 4095 // Resolution of ADC
#define TEMP30_CAL_ADDR ((uint16_t*) ((uint32_t) 0x1FFF7A2A)) //Raw data acquired at temperature of 30 °C VDDA = 3.3 V
															  //ST did a measurement for us when manufacturing the chip,
															  //using a precise external reference voltage on the VREF+ pin,
				 	 	 	 	 	 	 	 	 	 	 	  //and stored the resulting ADC reading into the system memory

#define VCAL 3.3	//The voltage used as external reference at calibration. Put as 330 instead 3.3V to avoid float, vmeasured would be in 10mV units

/* USER CODE END Includes */

extern ADC_HandleTypeDef hadc1;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_ADC1_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __ADC_H__ */

