/*
 * graph.h
 *
 *  Created on: Jan 22, 2021
 *      Author: 氢化脱氯次氯酸
 */

#ifndef __WAVE_H_
#define __WAVE_H_

#include "stm32g0xx_hal.h"
#include "menu.h"
typedef struct
{
	float center_voltage;
	float max_voltage;
	float min_voltage;
} Y_Axis;

float get_pp_voltage(uint16_t *ADCValue,input_gain_e gain);
float get_dc_voltage(uint16_t *ADCValue, input_gain_e gain);
float get_voltage_div(void);
void auto_scale(uint16_t *ADCValue,input_gain_e gain);
void manual_inc_scale(void);
void manual_dec_scale(void);
void manual_inc_offset(void);
void manual_dec_offset(void);
uint16_t trigger(uint16_t *ADCValue, uint16_t total_points);
uint32_t get_frequency(uint16_t *FFTValue, uint32_t sample_rate);

extern Y_Axis volt_on_y_axis;

#endif /* __WAVE_H_ */
