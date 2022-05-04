#include "wave.h"
#include "tim.h"
#include "main.h"
#include "menu.h"
#include "Adafruit_ZeroFFT.h"
#include "wave_task.h"

static float v_scale_list[] = {0.1, 0.5, 0.8, 1, 1.2, 1.5, 1.8, 2, 2.5, 4, 5,7};
static uint8_t v_scale_index;
Y_Axis volt_on_y_axis;
float ADCtoVOL(uint16_t *ADCValue, input_gain_e gain);
static void get_max_min_pp_value(uint16_t *ADCValue, uint16_t *a_max_value, uint16_t *a_min_value, uint16_t *a_pp_value);
static void get_dc_value(uint16_t *ADCValue, uint16_t *a_dc_value);
static float voltage_range_auto_select(float amp_voltage);
static uint8_t spectrum_max(uint16_t *FFTValue, uint8_t ignore_dc);
float ADC_Val_toVOL(uint16_t *ADCValue, input_gain_e gain);
uint32_t get_frequency(uint16_t *FFTValue, uint32_t sample_rate);


#define NUM_OF_SAMPLE_RATES 8

// List of sample rates.
static uint32_t sample_rate_list[NUM_OF_SAMPLE_RATES] = {3200, 8000, 16000, 32000, 80000, 160000, 320000,640000};

// Index of sample rate list
static int8_t sample_rate_index = 5;  // Default sample rate: 10kHz

extern wave_info_t wave_info;
extern mode_set_t mode_set;
/**
  * @brief       Calculate max/min/peak-peak values of ADCValue.
  * @param[in]   ADCValue  Array of sampled ADC values (one channel).
  * @param[out]  a_max_value  Pointer to max ADC value.
  * @param[out]  a_min_value  Pointer to min ADC value.
  * @param[out]  a_pp_value  Pointer to peak-peak ADC value.
  * @note        If any of them isn't needed, just pass NULL.(except ADCValue)
  * @retval      None
  */
static void get_max_min_pp_value(uint16_t *ADCValue, uint16_t *a_max_value, uint16_t *a_min_value, uint16_t *a_pp_value)
{
	uint16_t i;
	uint16_t a_temp_max_value = ADCValue[0], a_temp_min_value = ADCValue[0];

	for (i = 1; i < SAVE_SPACE; i++)
	{
		if (ADCValue[i] > a_temp_max_value)
			a_temp_max_value = ADCValue[i];
		if (ADCValue[i] < a_temp_min_value)
			a_temp_min_value = ADCValue[i];
	}

	if (a_max_value != NULL)
		*a_max_value = a_temp_max_value;
	if (a_min_value != NULL)
		*a_min_value = a_temp_min_value;
	if (a_pp_value != NULL)
		*a_pp_value = a_temp_max_value - a_temp_min_value;
}

/**
  * @brief       Calculate dc component of ADCValue.
  * @param[in]   ADCValue  Array of sampled ADC values.
  * @param[out]  a_dc_value  Pointer to dc ADC value.
  * @retval      None
  */
static void get_dc_value(uint16_t *ADCValue, uint16_t *a_dc_value)
{
	uint16_t i;
	uint32_t a_sum = 0;
	for (i = 0; i < SAVE_SPACE; i++)
		a_sum += ADCValue[i];
	*a_dc_value = a_sum / SAVE_SPACE;
}

/**
  * @brief      Calculate Vpp of the signal.
  * @param[in]  ADCValue  Array of sampled ADC values (one channel).
  * @retval     Vpp of the input signal.
  */
float get_pp_voltage(uint16_t *ADCValue,input_gain_e gain)
{
	uint16_t a_pp_value;
	get_max_min_pp_value(ADCValue, NULL, NULL, &a_pp_value);
	return ADC_Val_toVOL(&a_pp_value,gain);
}

/**
  * @brief      Calculate Vdc of the signal.
  * @param[in]  ADCValue  Array of sampled ADC values (one channel).
  * @retval     Vdc of the input signal.
  */
float get_dc_voltage(uint16_t *ADCValue, input_gain_e gain)
{
	uint16_t a_dc_value;
	get_dc_value(ADCValue, &a_dc_value);
	return ADCtoVOL(&a_dc_value,gain);
}


float ADCtoVOL(uint16_t *ADCValue, input_gain_e gain)
{
	float volatge;
	if(gain==TWO_TIMES)
	{
		volatge=((2048-(float)*ADCValue)/2048)*3.3;
	}
	else
	{
		volatge=((2048-(float)*ADCValue)/2048)*3.3*5;
	}
	return volatge;
}

float ADC_Val_toVOL(uint16_t *ADCValue, input_gain_e gain)
{
	float volatge;
	if(gain==TWO_TIMES)
	{
		volatge=(((float)*ADCValue)/2048)*3.3;
	}
	else
	{
		volatge=(((float)*ADCValue)/2048)*3.3*5;
	}
	return volatge;
}


void auto_scale(uint16_t *ADCValue,input_gain_e gain)
{
	uint16_t a_max_value, a_min_value, a_pp_value;
	get_max_min_pp_value(ADCValue, &a_max_value, &a_min_value, &a_pp_value);

	wave_info.max_voltage = ADCtoVOL(&a_min_value,gain);
	wave_info.min_voltage = ADCtoVOL(&a_max_value,gain);
	wave_info.center_voltage= (wave_info.max_voltage-wave_info.min_voltage)/2+wave_info.min_voltage;
	wave_info.half_range=voltage_range_auto_select(ADC_Val_toVOL(&a_pp_value,gain))/2*mode_set.vol_scl_offset;

	mode_set.vol_pos=64+(wave_info.center_voltage/wave_info.half_range)*48;
}


static float voltage_range_auto_select(float v_amplitude)
{
	uint8_t i = 0;
	for (i = 0; i < sizeof(v_scale_list) / sizeof(float); i++)
		if (v_amplitude < v_scale_list[i])
		{
			return v_scale_list[i];
		}
}

/**
  * @brief  Get the current sample rate.
  * @retval Current sample rate
  */
uint32_t get_sample_rate(void)
{
	return sample_rate_list[sample_rate_index];
}

/**
  * @brief  Increase sample rate to the next level.
  * @retval None
  */
void inc_sample_rate(void)
{
	if (sample_rate_index < NUM_OF_SAMPLE_RATES - 1)
		sample_rate_index++;
	else
		sample_rate_index =  NUM_OF_SAMPLE_RATES - 1;
}

/**
  * @brief  Decrease sample rate to the previous level.
  * @retval None
  */
void dec_sample_rate(void)
{
	if (sample_rate_index > 0 && sample_rate_index < NUM_OF_SAMPLE_RATES)
		sample_rate_index--;
	else
		sample_rate_index = 0;
}

/**
  * @brief      Set sample_rate as TIM2 output PWM frequency.
  * @param[in]  sample_rate  Current sample rate
  * @retval     None
  */
void set_sample_rate(uint32_t sample_rate)
{
	__HAL_TIM_SET_AUTORELOAD(&htim1, 64000000 / sample_rate - 1);
}
/**
  * @brief      Find the frequency that has the max amplitude, return the corresponding index.
  * @param[in]  FFTValue  FFT result of the signal (one channel).
  * @param[in]  ignore_dc  Ignore DC & low-frequency components.
  *                        This parameter can be one of the following values:
  *                           @arg 1   FFTValue[0] and FFTValue[1] are not considered.
  *                           @arg 0   FFTValue[0] and FFTValue[1] are considered.
  * @retval     FFT index that has the max FFTValue.
  */
static uint8_t spectrum_max(uint16_t *FFTValue, uint8_t ignore_dc)
{
    uint8_t i;
    uint8_t temp_max_index = ignore_dc ? 2 : 0;

    for (i = ignore_dc ? 3 : 1; i <= FFT_POINT / 2; i++)
        if (FFTValue[i] > FFTValue[temp_max_index])
            temp_max_index = i;

    return temp_max_index;
}

/**
  * @brief      Calculate base frequency.
  * @param[in]  FFTValue  FFT result of the signal (one channel).
  * @param[in]  sample_rate  ADC sample rate.
  * @retval     Base frequency of the input signal.
  */
uint32_t get_frequency(uint16_t *FFTValue, uint32_t sample_rate)
{
    return FFT_BIN(spectrum_max(FFTValue, 1), sample_rate, FFT_POINT);
}
