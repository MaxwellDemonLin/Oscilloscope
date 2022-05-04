#include "BSP_ADC.h"
#include "adc.h"

extern uint16_t ADC_Value_buffer1[2][SAVE_SPACE];
void select_channel(uint8_t ch)
{

	  /* USER CODE BEGIN ADC1_Init 0 */

	  /* USER CODE END ADC1_Init 0 */

	  ADC_ChannelConfTypeDef sConfig = {0};

	  /* USER CODE BEGIN ADC1_Init 1 */
	  HAL_ADC_DeInit(&hadc1);
	  /* USER CODE END ADC1_Init 1 */
	  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
	  */
	  hadc1.Instance = ADC1;
	  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
	  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
	  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
	  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	  hadc1.Init.LowPowerAutoWait = DISABLE;
	  hadc1.Init.LowPowerAutoPowerOff = DISABLE;
	  hadc1.Init.ContinuousConvMode = DISABLE;
	  hadc1.Init.NbrOfConversion = 1;
	  hadc1.Init.DiscontinuousConvMode = DISABLE;
	  hadc1.Init.ExternalTrigConv = ADC_EXTERNALTRIG_T1_TRGO2;
	  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISINGFALLING;
	  hadc1.Init.DMAContinuousRequests = ENABLE;
	  hadc1.Init.Overrun = ADC_OVR_DATA_PRESERVED;
	  hadc1.Init.SamplingTimeCommon1 = ADC_SAMPLETIME_1CYCLE_5;
	  hadc1.Init.OversamplingMode = DISABLE;
	  hadc1.Init.TriggerFrequencyMode = ADC_TRIGGER_FREQ_HIGH;
	  if (HAL_ADC_Init(&hadc1) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  /** Configure Regular Channel
	  */
	  switch(ch)
	  {
	  	  case 1: sConfig.Channel = ADC_CHANNEL_1; break;
	  	  case 2: sConfig.Channel = ADC_CHANNEL_2; break;
	  	  case 3: sConfig.Channel = ADC_CHANNEL_3; break;
	  	  case 4: sConfig.Channel = ADC_CHANNEL_4; break;
	  	  case 5: sConfig.Channel = ADC_CHANNEL_5; break;
	  	  case 6: sConfig.Channel = ADC_CHANNEL_6; break;
	  	  case 7: sConfig.Channel = ADC_CHANNEL_7; break;
	  	  case 8: sConfig.Channel = ADC_CHANNEL_8; break;
	  }
	  sConfig.Rank = ADC_REGULAR_RANK_1;
	  sConfig.SamplingTime = ADC_SAMPLINGTIME_COMMON_1;
	  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  /** Configure Regular Channel
	  */
	  /* USER CODE BEGIN ADC1_Init 2 */
	  HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&ADC_Value_buffer1, SAVE_SPACE*2);
	  /* USER CODE END ADC1_Init 2 */
}
void select_both(void)
{
	HAL_ADC_DeInit(&hadc1);
	MX_ADC1_Init();
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&ADC_Value_buffer1, SAVE_SPACE*2);
}
