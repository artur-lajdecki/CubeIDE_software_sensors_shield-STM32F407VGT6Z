/*
 * averaging.h
 *
 *  Created on: Feb 27, 2022
 *      Author: Artur
 */

#ifndef INC_AVERAGING_H_
#define INC_AVERAGING_H_

#include <stdint.h>

uint16_t ADC_GetSampleAvgNDeleteX(uint8_t N , uint8_t X);
void Sort_tab(uint16_t tab[], uint8_t lenght);

#endif /* INC_AVERAGING_H_ */
