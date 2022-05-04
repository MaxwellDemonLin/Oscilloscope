/*
 * sample.h
 *
 *  Created on: Jan 23, 2021
 *      Author: 氢化脱氯次氯酸
 */

#ifndef __SAMPLE_H_
#define __SAMPLE_H_

#include "stm32fg0xx_hal.h"

#define SAMPLE_POINTS 768

uint32_t get_sample_rate(void);
void inc_sample_rate(void);
void dec_sample_rate(void);
void set_sample_rate(uint32_t sample_rate);
void start_sample(uint16_t *ADCValue);
void ADCValue_split(uint16_t *ADCValue_raw, uint16_t ADCValue[][SAMPLE_POINTS]);
void copy_2darray_uint16(uint16_t array1[][SAMPLE_POINTS], uint16_t array2[][SAMPLE_POINTS], uint16_t length1, uint16_t length2);

#endif /* __SAMPLE_H_ */
