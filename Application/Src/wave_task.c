#include "wave_task.h"
#include "main.h"
#include "OLED.h"
#include "BSP_ADC.h"
#include "menu.h"
#include "wave.h"
#include "tim.h"

void input_select(void);
void choose_channal();
void cal_show_point();
void set_sample(void);
//V_input=-(ADC_Value_buffer1[mode_set.adc_buffer_flag][i]/4096*3.3-1.65)*2

uint8_t show_point_y[64];
extern mode_set_t mode_set;
wave_info_t wave_info;



void wave_task(void)
{
	static uint8_t clear_state=0;
	set_sample();
	if(clear_state)
	{
		for(uint8_t i=0;i<100;i=i+2)
		{
			if(show_point_y[i/2]>18&&show_point_y[i/2]<111&&show_point_y[i/2+1]>18&&show_point_y[i/2+1]<111)
			{
				OLED_ClearLine(i, show_point_y[i/2], i+2, show_point_y[i/2+1]);
			}
		}
		OLED_Clear_rect(110,16, 128, 110);
		clear_state=0;
	}
	if(mode_set.spectrum_state==1)
	{
		return;
	}
	auto_scale(ADC_Value_buffer1[mode_set.adc_buffer_flag],mode_set.channal_mode[0].input_gain);
	mode_set.calc_flag=1;
	cal_show_point();
	mode_set.calc_flag=0;
	if(mode_set.stop_flag)
	{

		mode_set.adc_buffer_flag=(mode_set.adc_buffer_flag+1)%2;
		mode_set.stop_flag=0;
	}
	if(!mode_set.stop_state&&htim1.State==HAL_TIM_STATE_READY)
	{
		HAL_TIM_Base_Start(&htim1);
	}

	for(uint8_t i=0;i<100;i=i+2)
	{
		if(show_point_y[i/2]>18&&show_point_y[i/2]<111&&show_point_y[i/2+1]>18&&show_point_y[i/2+1]<111)
		{
			OLED_DrawLine(i, show_point_y[i/2], i+2, show_point_y[i/2+1], 1);
		}
	}
	clear_state=1;
	OLED_DrawLine(110, 64+ mode_set.vol_offset, 128, 64+ mode_set.vol_offset, 1);
	int inter;
	int decimal;
	if(wave_info.center_voltage>10)
	{
		OLED_ShowNum(110, 54+ mode_set.vol_offset,(int)wave_info.center_voltage,2,8,1 );
	}
	else
	{
		//get_one_decimal(wave_info.center_voltage,&inter,& decimal);
		inter=wave_info.center_voltage;
		decimal=((int)(wave_info.center_voltage*10))%10;
		OLED_ShowNum(110, 54+ mode_set.vol_offset,inter,1,8,1 );
		OLED_ShowString(115, 54+ mode_set.vol_offset,".",8,1 );
		OLED_ShowNum(120, 54+ mode_set.vol_offset,decimal,1,8,1 );
	}
	wave_info.dc=get_dc_voltage(ADC_Value_buffer1[mode_set.adc_buffer_flag],mode_set.channal_mode[0].input_gain);
	wave_info.Vpp=get_pp_voltage(ADC_Value_buffer1[mode_set.adc_buffer_flag],mode_set.channal_mode[0].input_gain);

}
void set_sample(void)
{
	choose_channal();
	input_select();
	set_sample_rate(get_sample_rate());
}

void choose_channal()
{
	if(mode_set.channal_state!=mode_set.channal_selct)
	{
		mode_set.channal_state = mode_set.channal_selct;
		switch(mode_set.channal_selct)
		{
			case 0:select_channel(1);break;
			case 1:select_channel(7);break;
		}
	}
}
void input_select(void)
{
	if(mode_set.channal_mode[0].input_gain==TWO_TIMES)
	{
		HAL_GPIO_WritePin(GPIOA ,GPIO_PIN_8,GPIO_PIN_RESET);
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,22);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOA ,GPIO_PIN_8,GPIO_PIN_SET);
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,30);
	}

	if(mode_set.channal_mode[1].input_gain==TWO_TIMES)
	{
		HAL_GPIO_WritePin(GPIOC ,GPIO_PIN_6,GPIO_PIN_RESET);
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4,22);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOC ,GPIO_PIN_6,GPIO_PIN_SET);
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4,30);
	}
}
void cal_show_point()
{
	uint16_t max_data;
	uint16_t add;
	uint8_t j=0;
	uint8_t start_data;
	if(mode_set.channal_selct==CHANNAL_ONE)
	{
		max_data= SAVE_SPACE - ONE_TIME_ZOOM / 2 * mode_set.channal_mode[0].time_gain+mode_set.time_pos ;
		add =  (SAVE_SPACE-mode_set.channal_mode[0].time_gain*ONE_TIME_ZOOM )/ 64;
		if(mode_set.channal_mode[0].input_gain==TWO_TIMES)
		{
			for(uint16_t i = ONE_TIME_ZOOM / 2 * mode_set.channal_mode[0].time_gain+mode_set.time_pos ; i < max_data ; i = i + add )
			{
			//	show_point_y[j]=(-(ADC_Value_buffer1[mode_set.adc_buffer_flag][i]/4096.00f*3.3)-1.65f)*(48/mode_set.vol_scl)+mode_set.vol_pos;
				show_point_y[j]=(((ADC_Value_buffer1[mode_set.adc_buffer_flag][i]-2048)/2048.00f)*3.3*48/(wave_info.half_range)+mode_set.vol_pos+ mode_set.vol_offset);
				j++;
			}
		}
		else
		{
			for(uint16_t i = ONE_TIME_ZOOM / 2 * mode_set.channal_mode[0].time_gain + mode_set.time_pos  ; i < max_data ; i = i + add )
			{
			//	show_point_y[j]=(-(ADC_Value_buffer1[mode_set.adc_buffer_flag][i]/4096.00f*3.3)-1.65f)*(48/mode_set.vol_scl)+mode_set.vol_pos;
				show_point_y[j]=(((ADC_Value_buffer1[mode_set.adc_buffer_flag][i]-2048)/2048.00f)*3.3*5*48/(wave_info.half_range)+ mode_set.vol_pos+mode_set.vol_offset);
				j++;
			}
		}
	}
	else if(mode_set.channal_selct==CHANNAL_TWO)
	{
		max_data= SAVE_SPACE - ONE_TIME_ZOOM / 2 * mode_set.channal_mode[1].time_gain+mode_set.time_pos ;
		add =  (SAVE_SPACE-mode_set.channal_mode[1].time_gain*ONE_TIME_ZOOM )/ 64;
		if(mode_set.channal_mode[1].input_gain==TWO_TIMES)
		{
			for(uint16_t i = ONE_TIME_ZOOM / 2 * mode_set.channal_mode[1].time_gain + mode_set.time_pos  ; i < max_data ; i = i + add )
			{
			//	show_point_y[j]=(-(ADC_Value_buffer1[mode_set.adc_buffer_flag][i]/4096.00f*3.3)-1.65f)*(48/mode_set.vol_scl)+mode_set.vol_pos;
				show_point_y[j]=(((ADC_Value_buffer1[mode_set.adc_buffer_flag][i]-2048)/2048.00f)*3.3*48/(wave_info.half_range)+ mode_set.vol_offset+ mode_set.vol_pos);
				j++;
			}
		}
		else
		{
			for(uint16_t i = ONE_TIME_ZOOM / 2 * mode_set.channal_mode[1].time_gain + mode_set.time_pos ; i < max_data ; i = i + add )
			{
			//	show_point_y[j]=(-(ADC_Value_buffer1[mode_set.adc_buffer_flag][i]/4096.00f*3.3)-1.65f)*(48/mode_set.vol_scl)+mode_set.vol_pos;
				show_point_y[j]=(((ADC_Value_buffer1[mode_set.adc_buffer_flag][i]-2048)/2048.00f)*3.3*5*48/(wave_info.half_range)+ mode_set.vol_offset+ mode_set.vol_pos);
				j++;
			}
		}
	}
}

