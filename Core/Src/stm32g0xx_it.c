/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32g0xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32g0xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "wave_task.h"
#include "menu.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
uint8_t key_b3_it=0;
uint8_t key_a4_it=0;
uint8_t key_a5_it=0;

extern uint16_t ADC_Value_buffer1[2][SAVE_SPACE];
extern uint8_t ADC_buffer_flag;

extern mode_set_t mode_set;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim1;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_adc1;
extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim14;
/* USER CODE BEGIN EV */
void counter_clockwise_event(void);
void clockwise(void);
/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M0+ Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVC_IRQn 0 */

  /* USER CODE END SVC_IRQn 0 */
  /* USER CODE BEGIN SVC_IRQn 1 */

  /* USER CODE END SVC_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32G0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32g0xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line 2 and line 3 interrupts.
  */
void EXTI2_3_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI2_3_IRQn 0 */

  /* USER CODE END EXTI2_3_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
  /* USER CODE BEGIN EXTI2_3_IRQn 1 */

  /* USER CODE END EXTI2_3_IRQn 1 */
}

/**
  * @brief This function handles EXTI line 4 to 15 interrupts.
  */
void EXTI4_15_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI4_15_IRQn 0 */

  /* USER CODE END EXTI4_15_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
  HAL_GPIO_EXTI_IRQHandler(OLED_DC_Pin);
  /* USER CODE BEGIN EXTI4_15_IRQn 1 */

  /* USER CODE END EXTI4_15_IRQn 1 */
}

/**
  * @brief This function handles DMA1 channel 1 interrupt.
  */
void DMA1_Channel1_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel1_IRQn 0 */

  /* USER CODE END DMA1_Channel1_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_adc1);
  /* USER CODE BEGIN DMA1_Channel1_IRQn 1 */

  /* USER CODE END DMA1_Channel1_IRQn 1 */
}

/**
  * @brief This function handles ADC1 interrupt.
  */
void ADC1_IRQHandler(void)
{
  /* USER CODE BEGIN ADC1_IRQn 0 */

  /* USER CODE END ADC1_IRQn 0 */
  HAL_ADC_IRQHandler(&hadc1);
  /* USER CODE BEGIN ADC1_IRQn 1 */

  /* USER CODE END ADC1_IRQn 1 */
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}

/**
  * @brief This function handles TIM14 global interrupt.
  */
void TIM14_IRQHandler(void)
{
  /* USER CODE BEGIN TIM14_IRQn 0 */

  /* USER CODE END TIM14_IRQn 0 */
  HAL_TIM_IRQHandler(&htim14);
  /* USER CODE BEGIN TIM14_IRQn 1 */

  /* USER CODE END TIM14_IRQn 1 */
}

/* USER CODE BEGIN 1 */
uint8_t compare=0;
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	static uint8_t clock_state=0;
	static uint8_t counter_clock_state=0;
	if(htim==&htim2)
	{
		if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_1)
		{
			if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4))//Rising edge
			{
				if(counter_clock_state)
				{
					counter_clockwise_event();
					counter_clock_state=0;
				}
			}
			else
			{
				if(clock_state)
				{
					clockwise();
					clock_state=0;
				}
			}
		}
		if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_2)
		{
			if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4))//Falling edge
			{
				clock_state=1;
			}
			else
			{
				counter_clock_state=1;
			}
		}
	}
}

void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin==GPIO_PIN_3)
	{
		key_b3_it=1;
	}
	if(GPIO_Pin==GPIO_PIN_4)
	{
		key_a4_it=1;
	}
	if(GPIO_Pin==GPIO_PIN_5)
	{
		key_a5_it=1;
	}
}

void counter_clockwise_event(void)
{
	mode_set.refresh_state=1;
	if(mode_set.select_falg==SELECT)
	{
		if(mode_set.current_mode<NUM-1)
		{
			mode_set.current_mode++;
		}
	}
	else
	{
		switch (mode_set.current_mode)
		{
			case CHANGE_CH:
			{
				mode_set.channal_selct=(mode_set.channal_selct+1)%2;

				break;
			}
			case CHANGE_INPUT_GAIN:
			{
				if(mode_set.channal_selct!=2)
				{
					//通道模式和对应�?�道的结构体序号�????????�????????

					mode_set.channal_mode[mode_set.channal_selct].input_gain=(mode_set.channal_mode[mode_set.channal_selct].input_gain+1)%2;
				}
				else
				{
					mode_set.channal_mode[1].input_gain=(mode_set.channal_mode[1].input_gain+1)%2;
					mode_set.channal_mode[0].input_gain=(mode_set.channal_mode[0].input_gain+1)%2;
				}
				break;
			}
			case CHANGE_Vp:
			{
				if(mode_set.vol_pos<116)
				{
					mode_set.vol_offset++;
				}
				break;
			}

			case CHANGE_Ts:
			{
				if(mode_set.channal_selct!=2)
				{
					if(mode_set.channal_mode[mode_set.channal_selct].time_gain>0)
					mode_set.channal_mode[mode_set.channal_selct].time_gain--;
				}
				else
				{

				}
				break;
			}
			case CHANGE_Tp:
			{
				if(mode_set.channal_selct!=2)
				{
					if( ONE_TIME_ZOOM / 2 * mode_set.channal_mode[mode_set.channal_selct].time_gain + mode_set.time_pos-ONE_TIME_SHIFT>0)
					{
						mode_set.time_pos-=ONE_TIME_SHIFT;
					}
				}
				break;

			}
			case CHANGE_Vs:
			{
				if(mode_set.vol_scl_offset<1.5)
				{
					mode_set.vol_scl_offset+=0.1;
				}
				break;
			}
			case CHANGE_Rate:
			{
				inc_sample_rate();
				break;
			}
		}
	}
}

void clockwise(void)
{
	mode_set.refresh_state=1;
	if(mode_set.select_falg==SELECT)
	{
		if(mode_set.current_mode!=0)
		{
			mode_set.current_mode--;
		}
	}
	else
	{
		switch (mode_set.current_mode)
		{
			case CHANGE_CH:
			{
				mode_set.channal_selct=(mode_set.channal_selct+1)%2;

				break;
			}
			case CHANGE_INPUT_GAIN:
			{
				if(mode_set.channal_selct!=2)
				{
					//通道模式和对应�?�道的结构体序号�????????�????????

					mode_set.channal_mode[mode_set.channal_selct].input_gain=(mode_set.channal_mode[mode_set.channal_selct].input_gain-1)%2;
				}
				else
				{
					mode_set.channal_mode[1].input_gain=(mode_set.channal_mode[1].input_gain-1)%2;
					mode_set.channal_mode[0].input_gain=(mode_set.channal_mode[0].input_gain-1)%2;
				}
				break;
			}
			case CHANGE_Vp:
			{
				if(mode_set.vol_pos>32)
				{
					mode_set.vol_offset--;
				}
				break;
			}

			case CHANGE_Ts:
			{
				if(mode_set.channal_selct!=2)
				{
					if(mode_set.channal_mode[mode_set.channal_selct].time_gain<MAX_TIME_GAIN)
					mode_set.channal_mode[mode_set.channal_selct].time_gain++;
				}
				else
				{

				}
				break;
			}
			case CHANGE_Tp:
			{
				if(mode_set.channal_selct!=2)
				{
					if( SAVE_SPACE - ONE_TIME_ZOOM / 2 * mode_set.channal_mode[0].time_gain + mode_set.time_pos + ONE_TIME_SHIFT < SAVE_SPACE)
					{
						mode_set.time_pos+=ONE_TIME_SHIFT;
					}
				}
				break;

			}
			case CHANGE_Vs:
			{
				if(mode_set.vol_scl_offset>0.5)
				{
					mode_set.vol_scl_offset-=0.1;
				}
				break;
			}
			case CHANGE_Rate:
			{
				dec_sample_rate();
				break;
			}
		}
	}
}



uint32_t count1=0;
uint32_t count2=0;
float hz=0;
int time;
extern int test;
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	if(	mode_set.calc_flag)
	{
		mode_set.stop_flag=1;
		HAL_TIM_Base_Stop(&htim1);
	}
	else
	{
		mode_set.adc_buffer_flag=0;
	}
}

void  HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc)
{
	if(	mode_set.calc_flag)
	{
		mode_set.stop_flag=1;
		HAL_TIM_Base_Stop(&htim1);
	}
	else
	{
		mode_set.adc_buffer_flag=1;
	}
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	static uint8_t flag=0;
	if(htim==&htim14)
	{
		if(compare>65)
		{
			flag=0;
		}
		if(compare==0)
		{
			flag=1;
		}

		if(flag)
		{
			compare++;
		}
		else
		{
			compare--;
		}
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3,compare);
	}
}
/* USER CODE END 1 */

