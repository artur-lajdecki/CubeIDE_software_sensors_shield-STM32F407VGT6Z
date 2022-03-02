/*
 * averaging.c
 *
 *  Created on: Feb 27, 2022
 *      Author: Artur
 */

#include "averaging.h"

/**
* @brief Get the average of N-X ADC samples
* @param Numbre of ADC samples to be averaged
* @param Numbre of ADC samples to be averaged
* @retval The average value
*/
uint16_t ADC_GetSampleAvgNDeleteX(uint8_t N , uint8_t X) {
	uint32_t avg_sample =0x00;
	uint16_t adc_sample[8]={0,0,0,0,0,0,0,0};
	uint8_t index=0x00;

	for (index=0x00; index<N; index++) {
		/* Store ADC samples */
		//adc_sample[index] = ADC_GetConversionValue(ADC1);
	}

	/* Sort the N-X ADC samples */
	Sort_tab(adc_sample,N);

	/* Add the N ADC samples */
	for (index=X/2; index<N-X/2; index++) {
	avg_sample += adc_sample[index];
	}

	/* Compute the average of N-X ADC sample */
	avg_sample /= N-X;

	/* Return average value */
	return avg_sample;
}

/**
* @brief Sort the N ADC samples
* @param ADC samples to be sorted
* @param Numbre of ADC samples to be sorted
* @retval None
*/
void Sort_tab(uint16_t tab[], uint8_t lenght) {
	uint8_t l= 0x00, exchange = 0x01;
	uint16_t tmp = 0x00;

	/* Sort tab */
	while(exchange==1) {
		exchange=0;
		for(l=0; l<lenght-1; l++) {
			if( tab[l] > tab[l+1] ) {
				tmp = tab[l];
				tab[l] = tab[l+1];
				tab[l+1] = tmp;
				exchange=1;
			}
		}
	}
}
