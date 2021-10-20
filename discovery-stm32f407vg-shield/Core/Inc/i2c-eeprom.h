
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef INC_I2_EEPROM_H_
#define INC_I2C_EEPROM_H_


#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stdint.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */



/* USER CODE BEGIN Private defines */
void EEPROM_Write (uint16_t page, uint16_t offset, uint8_t *data, uint16_t size);
void EEPROM_Read (uint16_t page, uint16_t offset, uint8_t *data, uint16_t size);
void EEPROM_PageErase (uint16_t page);

void EEPROM_Write_NUM (uint16_t page, uint16_t offset, float  fdata);
float EEPROM_Read_NUM (uint16_t page, uint16_t offset);

/* USER CODE END Private defines */

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

//void eeprom_write(uint16_t position, uint8_t data);
//
//uint8_t eeprom_read (uint16_t position);
//
//void eeprom_write_string(uint16_t position, char *data);
//
//void eeprom_read_string(uint16_t position);
//
//void eeprom_write_string(uint16_t position, char *data);
//
//void eeprom_read_string(uint16_t position);

#endif /* INC_I2C_EEPROM_H_ */
