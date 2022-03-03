/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//includes all user defined headers
#include "system.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define ADC_VREFINT_NUMBER 8
#define THERMISTORS_FIR_NUMBER 4
#define PHOTODIODES_FIR_NUMBER 4
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
_Bool FIR_flag = false;
FIRFilter moving_average_thermistors[THERMISTORS_FIR_NUMBER];
FIRFilter moving_average_photodiodes[PHOTODIODES_FIR_NUMBER];

	/*
	 * ---- INFO ----
	 *
	 * THERMISTORS
	 * ADC1read[0]  - thermistor[0]
	 * ADC1read[1]  - thermistor[1]
	 * ADC1read[2]  - thermistor[2]
	 * ADC1read[3]  - thermistor[3]
	 *
	 * PHOTODIODES
	 * ADC1read[4]  - photodiode[0]
	 * ADC1read[5]  - photodiode[1]
	 * ADC1read[6]  - photodiode[2]
	 * ADC1read[7]  - photodiode[3]
	 *
	 * VREFINT
	 * ADC1read[8]  - vref internal channel
	 */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
_Bool Average_IsLimit(DAQ_channel_no);
void menu_encoder_event(void);
void display_values(void);
void calculate_thermistors_data(void);
void calculate_photodiodes_data(void);
void send_thermistors_data(void);
void send_photodiodes_data(void);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_USART1_UART_Init();
  MX_I2C2_Init();
  MX_SPI3_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
/* -------------------------------------------------------------------------------- */
/* -- TIMERS START -- */
/* -------------------------------------------------------------------------------- */
  HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);
 // HAL_TIM_Base_Start_IT(&htim10);

/* -------------------------------------------------------------------------------- */
/* -- USART Rx DMA START -- */
/* -------------------------------------------------------------------------------- */
//  HAL_UART_Receive_DMA(&huart1, Received, 13);

/* -------------------------------------------------------------------------------- */
/* -- CREATE ENCODER -- */
/* -------------------------------------------------------------------------------- */
  encoder_struct_init(&encoder_1, &htim1);

/* -------------------------------------------------------------------------------- */
/* -- LCD ST7735 SCREEN INIT -- */
/* -------------------------------------------------------------------------------- */
  ST7735_Init(1);

/* -------------------------------------------------------------------------------- */
/* -- MENU INIT -- */
/* -------------------------------------------------------------------------------- */
  GUI_init();
  Menu_Show();

/* -------------------------------------------------------------------------------- */
/* -- ADC1 START 9 channels -- */
/* -------------------------------------------------------------------------------- */
  HAL_ADC_Start_DMA(&hadc1, (uint32_t*)ADC1read, 9);   // frequency > 10kHz( 0.1 ms/100us )


/* -------------------------------------------------------------------------------- */
/* -- Initialise channels  -- */
/* -------------------------------------------------------------------------------- */
  DAQ_channel_init(DAQ_CH1, CHANNEL_1_GPIO_TypeDef, CHANNEL_1_GPIO_Pin, &thermistor[0], &photodiode[0]);
  DAQ_channel_init(DAQ_CH2, CHANNEL_2_GPIO_TypeDef, CHANNEL_2_GPIO_Pin, &thermistor[1], &photodiode[1]);
  DAQ_channel_init(DAQ_CH3, CHANNEL_3_GPIO_TypeDef, CHANNEL_3_GPIO_Pin, &thermistor[2], &photodiode[2]);
  DAQ_channel_init(DAQ_CH4, CHANNEL_4_GPIO_TypeDef, CHANNEL_4_GPIO_Pin, &thermistor[3], &photodiode[3]);

  HAL_Delay(500);

  DAQ_channel_set_th_limit(DAQ_CH1, 2500);
  DAQ_channel_set_ph_limit(DAQ_CH1, 50000);

  DAQ_channel_set_th_limit(DAQ_CH2, 2500);
  DAQ_channel_set_ph_limit(DAQ_CH2, 50000);

  DAQ_channel_set_th_limit(DAQ_CH3, 2500);
  DAQ_channel_set_ph_limit(DAQ_CH3, 50000);

  DAQ_channel_set_th_limit(DAQ_CH4, 2500);
  DAQ_channel_set_ph_limit(DAQ_CH4, 50000);


  for(uint8_t i = 0; i < THERMISTORS_FIR_NUMBER; i++) {
	  FIRFilter_Init(&moving_average_thermistors[i]);
  }
  for(uint8_t i = 0; i < PHOTODIODES_FIR_NUMBER; i++) {
  	  FIRFilter_Init(&moving_average_photodiodes[i]);
  }

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  menu_flags.flag_encoder_event = true;
  uint32_t value = 0;
  while (1)
  {
	if(menu_flags.flag_function && !menu_flags.flag_CHANGE_value && !menu_flags.flag_change_finish && encoder_enter(&encoder_1))  {
		menu_flags.flag_function = false;
		menu_flags.flag_display_measurements = false;
		menu_flags.flag_show_menu = true;
	}

	if(!menu_flags.flag_function && !menu_flags.flag_CHANGE_value) {
		menu_encoder_event();
	}

	if(menu_flags.flag_clear_screen) {
		ST7735_FillScreen(BLACK);
		menu_flags.flag_clear_screen = false;
	}

	if(menu_flags.flag_show_menu) {
		ST7735_FillScreen(BLACK);
		Menu_Show();
		menu_flags.flag_show_menu = false;
	}

	if(menu_flags.flag_function) {

		for(uint8_t i = 0; i<NUMBER_OF_CHANNELS; i++) {
			if(DAQ_channel_get_flag_enable(i)) {
				DAQ_CHANGE_enable(i);
				DAQ_channel_set_flag_enable(i, false);
			}

			else if(DAQ_channel_get_flag_th_limit(i)) {

				if(menu_flags.flag_change_finish) {
					DAQ_channel_set_th_limit(i,value);
					menu_flags.flag_change_finish = false;
					menu_flags.flag_CHANGE_value = false;
					menu_flags.flag_CHANGE_cursor = false;
					menu_flags.flag_CHANGE_temperature = false;

				}
				else {
					value = DAQ_channel_get_th_limit(i);
					menu_flags.flag_CHANGE_value = true;
					menu_flags.flag_CHANGE_cursor = true;
					menu_flags.flag_CHANGE_temperature = true;
					menu_flags.flag_clear_screen = true;
				}

				menu_flags.flag_function = false;

			}

			else if(DAQ_channel_get_flag_ph_limit(i)) {
				if(menu_flags.flag_change_finish) {
					DAQ_channel_set_ph_limit(i,value);
					menu_flags.flag_change_finish = false;
					menu_flags.flag_CHANGE_value = false;
					menu_flags.flag_CHANGE_cursor = false;
					menu_flags.flag_CHANGE_power = false;

				}
				else {
					value = DAQ_channel_get_ph_limit(i);
					menu_flags.flag_CHANGE_value = true;
					menu_flags.flag_CHANGE_cursor = true;
					menu_flags.flag_CHANGE_power = true;
					menu_flags.flag_clear_screen = true;
				}

				menu_flags.flag_function = false;
			}

			else if(DAQ_channel_get_flag_save(i)) {
				DAQ_CHANGE_save(i);
			}
		}

		if(menu_flags.flag_display_measurements) {
			display_values();
		}
	}

	if(menu_flags.flag_CHANGE_value){
		value = MENU_CHANGE_value(value);

	}


	if(FIR_flag) {
		for(int channel_no = 0; channel_no<NUMBER_OF_CHANNELS; channel_no++) {
			FIRFilter_Update(&moving_average_thermistors[channel_no], ADC1read[channel_no]);
			FIRFilter_Update(&moving_average_photodiodes[channel_no], ADC1read[channel_no+4]);
		}

		FIR_flag = false;
	}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void menu_encoder_event(void) {

	  if( encoder_step_clockwise(&encoder_1) == true) {
		Menu_SelectNext();
	  }
	  if(encoder_step_counterclockwise(&encoder_1) == true) {
		Menu_SelectPrev();
	  }
	  if(encoder_enter(&encoder_1) == true) {
	  		Menu_Click();
	  }
}

void display_values(void) {

	for(int i = 0; i<4; i++) {
		photodiode[i].power_value = photodiode_ADC_to_power(moving_average_photodiodes[i].out, ADC1read[8]);
	}
	for(int i = 0; i<4; i++) {
		thermistor[i].temperature_value = ntc3950_ADC_to_Celcius(moving_average_thermistors[i].out, ADC1read[8]);
	}

	char text[8][12];
	for (int i = 0; i<4; i++) {
		sprintf(text[i], "T%d:%.2fC < %.2fC", i, thermistor[i].temperature_value, thermistor[i].temperature_max_value);
		ST7735_WriteString(2, 2+(30*i), text[i], Font_7x10, WHITE, BLACK);

		sprintf(text[i], "P%d:%.2fmW < %.2fmW", i, photodiode[i].power_value, photodiode[i].power_max_value);
		ST7735_WriteString(2, 17+(30*i), text[i], Font_7x10, WHITE, BLACK);
	}

}

_Bool Average_IsLimit(DAQ_channel_no no) {
	if (moving_average_photodiodes[no].out >= DAQ_channel[no].ph->ADC_max_value || moving_average_thermistors[no].out <= DAQ_channel[no].th->ADC_max_value) {
		return true;
	}
	else
	return false;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
//	 HAL_UART_Receive_DMA(&huart1, Received, 13); // Ponowne włączenie nasłuchiwania
}


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {

	FIR_flag = true;

	for(int channel_no = 0; channel_no<NUMBER_OF_CHANNELS; channel_no++) {

		if(Average_IsLimit(channel_no))
			 {
				DAQ_channel_off(channel_no);
			 }
	}

}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

