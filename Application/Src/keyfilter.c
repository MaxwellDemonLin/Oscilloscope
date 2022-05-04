#include "keyfilter.h"
#include "stm32g0xx_it.h"
#include "stm32g0xx_hal.h"
#include "BSP_ADC.h"
#include "wave_task.h"
#include "menu.h"
#include "main.h"
#include "adc.h"
extern TIM_HandleTypeDef htim1;

extern mode_set_t mode_set;
#define FILTER_TIMES  1

void key_filter_task(void)
{
	static uint8_t key_a4_count=0;
	static uint8_t key_a5_count=0;
	static uint8_t key_b3_count=0;


	if(key_a4_it)
	{
		if(!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4))
		{
			key_a4_count++;
		}
		else
		{

			key_a4_it=0;
			key_a4_count=0;
		}
	}

	if(key_a5_it)
	{
		if(!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5))
		{
			key_a5_count++;
		}
		else
		{

			key_a5_it=0;
			key_a5_count=0;
		}
	}

	if(key_b3_it)
	{
		if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3))
		{
			key_b3_count++;
		}
		else
		{
			key_b3_it=0;
			key_b3_count=0;
		}
	}


	if(key_a4_count==FILTER_TIMES)
	{
		if(mode_set.stop_state==0)
		{
			HAL_TIM_Base_Stop(&htim1);
			mode_set.stop_state=1;
		}
		else if(mode_set.stop_state==1)
		{
			mode_set.stop_state=0;
		}
		key_a4_count=0;
		key_a4_it=0;
	}

	if(key_a5_count==FILTER_TIMES)
	{
		mode_set.spectrum_state=mode_set.spectrum_state^1;
		key_a5_count=0;
		key_a5_it=0;
	}

	if(key_b3_count==FILTER_TIMES)
	{
		mode_set.refresh_state=1;
		mode_set.select_falg=(mode_set.select_falg+1)%2;
		key_b3_count=0;
		key_b3_it=0;
	}
}
