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

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */


	/*
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

	float current_value_thermistor[4]; //ADC values are recalculated for sending through USART
	float current_value_photodiode[4]; //ADC values are recalculated for sending through USART

	uint8_t error_msg[] = "COM error.\n\r"; //If error in received message has been detected

	uint8_t Received[13]; //Buffer for received USART data (DMA)

	uint8_t data[8][20]; //Buffer for data to send (DMA)

	uint8_t data_write = 90; //??

	char data_read0[10]; //??

	 struct USART_frame {
		 uint8_t redundancy;
		 uint32_t CMD;
		 uint8_t data;
	 };

	 enum USART_flag {
		 thermistor_1_max_temp = 0,
		 thermistor_2_max_temp = 2,
		 thermistor_3_max_temp = 4,
		 thermistor_4_max_temp = 6,

		 photodiode_1_max_pow = 8,
		 photodiode_2_max_pow = 10,
		 photodiode_3_max_pow = 12,
		 photodiode_4_max_pow = 14,

		 channel_1_enable = 16,
		 channel_2_enable = 18,
		 channel_3_enable = 20,
		 channel_4_enable = 22
	 };

	 //struct USART_frame
	 _Bool flag_USART; //flag which enables sending data in the main while loop
	 _Bool flag_eeprom[4];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
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
  HAL_UART_Receive_DMA(&huart1, Received, 13);

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
/* -- Initialise channels (enable & max values for ph and th) -- */
/* -------------------------------------------------------------------------------- */
HAL_Delay(500);
DAQ_channel_init( 500.0, 25, DAQ_CH1);
DAQ_channel_init( 200.0, 107.8, DAQ_CH2);
DAQ_channel_init( 300.0, 107.8, DAQ_CH3);
DAQ_channel_init( 400.0, 107.8, DAQ_CH4);

//To set the maximum values manually:
// thermistor_1.ADC_max_val = 'value from 0 to 4095'
// photodiode_1.ADC_max_val = 'value from 0 to 4095'
 thermistor[0].ADC_max_val = 2500;
 photodiode[0].ADC_max_val = 2500;

 thermistor[1].ADC_max_val = 2500;
 photodiode[1].ADC_max_val = 2500;

 thermistor[2].ADC_max_val = 2500;
 photodiode[2].ADC_max_val = 2500;

 thermistor[3].ADC_max_val = 2500;
 photodiode[3].ADC_max_val = 2500;
//
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	menu_encoder_event();

//	display_values();

//	send_thermistors_data();
//	send_photodiodes_data();

	//flag_USART = false;



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

		uint8_t text[8][12];

		for (int i = 0; i<4; i++) {
			sprintf(text[i], "|T%d>%d  ", i, ADC1read[i]);
			ST7735_WriteString(25, 0+(30*i), text[i], Font_7x10, WHITE, BLACK);

			sprintf(text[i], "|L%d<%d  ", i, thermistor[i].ADC_max_val);
			ST7735_WriteString(95, 0+(30*i), text[i], Font_7x10, WHITE, BLACK);

			sprintf(text[i], "|P%d>%d  ", i, ADC1read[i+4]);
			ST7735_WriteString(25, 15+(30*i), text[i], Font_7x10, WHITE, BLACK);

			sprintf(text[i], "|L%d<%d  ", i, photodiode[i].ADC_max_val);
			ST7735_WriteString(95, 15+(30*i), text[i], Font_7x10, WHITE, BLACK);
		}

//		for (int i = 4; i<8; i++) {
//			sprintf(text[i], "|P%d>%d  ", i, ADC1read[i]);
//			ST7735_WriteString(25, 0+(15*i), text[i], Font_7x10, WHITE, BLACK);
//
//			sprintf(text[i], "|L%d>%d  ", i, photodiode[i-4].ADC_max_val);
//			ST7735_WriteString(95, 0+(15*i), text[i], Font_7x10, WHITE, BLACK);
//		}


}


void send_thermistors_data(void) {
	// DANE Z TERMISTOROW
	current_value_thermistor[0] = ntc3950_ADC_to_Celcius(ADC1read[0], ADC1read[8]);
	sprintf(data[0], "01010101%3.2f\r\n", current_value_thermistor[0]);
	HAL_UART_Transmit_DMA(&huart1, (uint8_t*) data[0], strlen(data[0]));

	current_value_thermistor[1] = ntc3950_ADC_to_Celcius(ADC1read[1], ADC1read[8]);
	sprintf(data[1], "01010102%3.2f\r\n", current_value_thermistor[1]);
	HAL_UART_Transmit_DMA(&huart1, (uint8_t*) data[1], strlen(data[1]));

	current_value_thermistor[2] = ntc3950_ADC_to_Celcius(ADC1read[2], ADC1read[8]);
	sprintf(data[2], "01010103%3.2f\r\n", current_value_thermistor[2]);
	HAL_UART_Transmit_DMA(&huart1, (uint8_t*) data[2], strlen(data[2]));

	current_value_thermistor[3] = ntc3950_ADC_to_Celcius(ADC1read[3], ADC1read[8]);
	sprintf(data[3], "01010104%3.2f\r\n", current_value_thermistor[3]);
	HAL_UART_Transmit_DMA(&huart1, (uint8_t*) data[3], strlen(data[3]));
}

void send_photodiodes_data(void) {
	// DANE Z FOTODIOD
	current_value_photodiode[0] = photodiode_ADC_to_power(ADC1read[4], ADC1read[8]);
	sprintf(data[4], "01010105%3.2f\r\n", current_value_photodiode[0]);
	HAL_UART_Transmit_DMA(&huart1, (uint8_t*) data[4], strlen(data[4]));

	current_value_photodiode[1] = photodiode_ADC_to_power(ADC1read[5], ADC1read[8]);
	sprintf(data[5], "01010106%3.2f\r\n", current_value_photodiode[1]);
	HAL_UART_Transmit_DMA(&huart1, (uint8_t*) data[5], strlen(data[5]));

	current_value_photodiode[2] = photodiode_ADC_to_power(ADC1read[6], ADC1read[8]);
	sprintf(data[6], "01010107%3.2f\r\n", current_value_photodiode[2]);
	HAL_UART_Transmit_DMA(&huart1, (uint8_t*) data[6], strlen(data[6]));

	current_value_photodiode[3] = photodiode_ADC_to_power(ADC1read[7], ADC1read[8]);
	sprintf(data[7], "01010108%3.2f\r\n", current_value_photodiode[3]);
	HAL_UART_Transmit_DMA(&huart1, (uint8_t*) data[7], strlen(data[7]));
}

//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
//// Jeżeli przerwanie pochodzi od timera 10
//	if(htim->Instance == TIM10) {
//		flag_USART = true;
//	}
//}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
//	static float result = 0;
//
//	 if(Received[0] == '1' && Received[1] == '0' && Received[2] == '1' && Received[3] == '0' && Received[4] == '1' && Received[5] == '0' && Received[6] == '1')
//	 {
//
//		 switch(Received[7])
//		 {
//		 case '1':
//
//			 for(int i=8; i<13; i++){
//				 result = result * 10 + ( Received[i] - '0' );
//				 }
//
//			 thermistor[0].temperature_C_max = result/100;
//			 result = 0;
//
//			 flag_eeprom[0] = 1;
//
//		     break;
//
//		 case '2':
//
//			 for(int i=8; i<13; i++){
//				 result = result * 10 + ( Received[i] - '0' );
//				 }
//
//			 thermistor[1].temperature_C_max = result/100;
//			 result = 0;
//
//			 flag_eeprom[1] = 1;
//
//		     break;
//
//		 case '3':
//
//			 for(int i=8; i<13; i++){
//				 result = result * 10 + ( Received[i] - '0' );
//				 }
//
//			 thermistor[2].temperature_C_max = result/100;
//			 result = 0;
//
//			 flag_eeprom[2] = 1;
//
//		     break;
//
//		 case '4':
//
//			 for(int i=8; i<13; i++){
//				 result = result * 10 + ( Received[i] - '0' );
//				 }
//
//			 thermistor[3].temperature_C_max = result/100;
//			 result = 0;
//
//			 flag_eeprom[3] = 1;
//
//			 break;
//
//		 case '5':
//
//			 if(flag_channel[0] == 0)
//			 {
//				 flag_channel[0] = 1; //channel open/high
//				 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0,GPIO_PIN_RESET); //transistor closed
//			 }
//			 else if(flag_channel[0] == 1)
//			 {
//				 flag_channel[0] = 0; //channel closed/low
//				 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0,GPIO_PIN_SET);  //transistor open
//			 }
//			 break;
//
//		 case '6':
//
//			 if(flag_channel[1] == 0)
//			 {
//				 flag_channel[1] = 1;
//				 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1,GPIO_PIN_RESET);
//			 }
//			 else if(flag_channel[1] == 1)
//			 {
//				 flag_channel[1] = 0;
//				 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1,GPIO_PIN_SET);
//			 }
//			 break;
//
//		 case '7':
//
//			 if(flag_channel[2] == 0)
//			 {
//				 flag_channel[2] = 1;
//				 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2,GPIO_PIN_RESET);
//			 }
//			 else if(flag_channel[2] == 1)
//			 {
//				 flag_channel[2] = 0;
//				 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2,GPIO_PIN_SET);
//			 }
//			 break;
//
//		 case '8':
//
//			 if(flag_channel[3] == 0)
//			 {
//				 flag_channel[3] = 1;
//				 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3,GPIO_PIN_RESET);
//			 }
//			 else if(flag_channel[3] == 1)
//			 {
//				 flag_channel[3] = 0;
//				 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3,GPIO_PIN_SET);
//			 }
//			 break;
//
//		 default:
//
//		     break;
//		 }
//	 }
//	 else
//	 {
//		 HAL_UART_Transmit_DMA(&huart1, (uint8_t*)error_msg, 12);
//	 }


	 HAL_UART_Receive_DMA(&huart1, Received, 13); // Ponowne włączenie nasłuchiwania
}


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {

	 if(ADC1read[4] >= photodiode[0].ADC_max_val || ADC1read[0] >= thermistor[0].ADC_max_val)
	 {
		 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0,GPIO_PIN_SET);
		 flag_channel[0] = 0;

	 }
	 if(ADC1read[5] >= photodiode[1].ADC_max_val || ADC1read[1] >= thermistor[1].ADC_max_val)
	 {
		 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1,GPIO_PIN_SET);
		 flag_channel[1] = 0;

	 }
	 if(ADC1read[6] >= photodiode[2].ADC_max_val || ADC1read[2] >= thermistor[2].ADC_max_val)
	 {
		 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2,GPIO_PIN_SET);
		 flag_channel[2] = 0;
	 }
	 if(ADC1read[7] >= photodiode[3].ADC_max_val || ADC1read[3] >= thermistor[3].ADC_max_val)
	 {
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3,GPIO_PIN_SET);
		flag_channel[3] = 0;
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
