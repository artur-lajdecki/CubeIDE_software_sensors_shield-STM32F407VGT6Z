/**
  ******************************************************************************
  * @file    adc.h
  * @brief   This file contains all the function prototypes for
  *          the adc.c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ADC_H__
#define __ADC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern ADC_HandleTypeDef hadc1;

/* USER CODE BEGIN Private defines */
//void ADC1_Select_CH4 (void);
//void ADC1_Select_CH5 (void);
//void ADC1_Select_CH6 (void);
//void ADC1_Select_CH7 (void);
//void ADC1_Select_VREFINT (void);
//
//void ADC2_Select_CH0 (void);
//void ADC2_Select_CH1 (void);
//void ADC2_Select_CH2 (void);
//void ADC2_Select_CH3 (void);

//Put it inside main function or interrupt
//	  ADC1_Select_CH4();
//	  HAL_ADC_Start(&hadc1);
//	  HAL_ADC_PollForConversion(&hadc1, 1000);
//	  ADC1read[0] = HAL_ADC_GetValue(&hadc1);
//	  HAL_ADC_Stop(&hadc1);
//
//	  ADC1_Select_CH5();
//	  HAL_ADC_Start(&hadc1);
//	  HAL_ADC_PollForConversion(&hadc1, 1000);
//	  ADC1read[1] = HAL_ADC_GetValue(&hadc1);
//	  HAL_ADC_Stop(&hadc1);
//
//	  ADC1_Select_CH6();
//	  HAL_ADC_Start(&hadc1);
//	  HAL_ADC_PollForConversion(&hadc1, 1000);
//	  ADC1read[2] = HAL_ADC_GetValue(&hadc1);
//	  HAL_ADC_Stop(&hadc1);
//
//	  ADC1_Select_CH7();
//	  HAL_ADC_Start(&hadc1);
//	  HAL_ADC_PollForConversion(&hadc1, 1000);
//	  ADC1read[3] = HAL_ADC_GetValue(&hadc1);
//	  HAL_ADC_Stop(&hadc1);
//
//	  ADC1_Select_VREFINT();
//	  HAL_ADC_Start(&hadc1);
//	  HAL_ADC_PollForConversion(&hadc1, 1000);
//	  ADC1read[4] = HAL_ADC_GetValue(&hadc1);
//	  HAL_ADC_Stop(&hadc1);
//
//	  ADC2_Select_CH0();
//	  HAL_ADC_Start(&hadc2);
//	  HAL_ADC_PollForConversion(&hadc2, 1000);
//	  ADC2read[0] = HAL_ADC_GetValue(&hadc2);
//	  HAL_ADC_Stop(&hadc2);
//
//	  ADC2_Select_CH1();
//	  HAL_ADC_Start(&hadc2);
//	  HAL_ADC_PollForConversion(&hadc2, 1000);
//	  ADC2read[1] = HAL_ADC_GetValue(&hadc2);
//	  HAL_ADC_Stop(&hadc2);
//
//	  ADC2_Select_CH2();
//	  HAL_ADC_Start(&hadc2);
//	  HAL_ADC_PollForConversion(&hadc2, 1000);
//	  ADC2read[2] = HAL_ADC_GetValue(&hadc2);
//	  HAL_ADC_Stop(&hadc2);
//
//	  ADC2_Select_CH3();
//	  HAL_ADC_Start(&hadc2);
//	  HAL_ADC_PollForConversion(&hadc2, 1000);
//	  ADC2read[3] = HAL_ADC_GetValue(&hadc2);
//	  HAL_ADC_Stop(&hadc2);
/* USER CODE END Private defines */

void MX_ADC1_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __ADC_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
