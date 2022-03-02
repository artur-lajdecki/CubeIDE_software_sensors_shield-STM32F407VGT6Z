/*
 * FIRFilter.h
 *
 *  Created on: Feb 27, 2022
 *      Author: Artur
 */

#ifndef INC_FIRFILTER_H_
#define INC_FIRFILTER_H_



#endif /* INC_FIRFILTER_H_ */

#ifndef FIR_FILTER_H
#define FIR_FILTER_H

#include <stdint.h>

#define FIR_FILTER_LENGTH 10

typedef struct {
	float 	buf[FIR_FILTER_LENGTH];
	uint8_t bufIndex;

	float out;
} FIRFilter;

void FIRFilter_Init(FIRFilter *fir);
float FIRFilter_Update(FIRFilter *fir, float inp);

#endif
