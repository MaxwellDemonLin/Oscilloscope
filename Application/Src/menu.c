#include "wave_task.h"
#include "main.h"
#include "menu.h"
#include "OLED.h"
#include "wave.h"
mode_set_t mode_set;
extern wave_info_t wave_info;
void show_sample_rate(uint8_t state);
void wave_info_plot(void);
void dis_float(u8 x,u8 y,float f,u8 size1,u8 mode);
void menu_init()
{
	  OLED_DrawLine(0,16, 128, 16, 1);
	  OLED_DrawLine(0,111, 128, 111, 1);
	  OLED_ShowString(0, 6, "CH1", 8, 1);
	  OLED_ShowString(20, 6, "x2", 8, 1);
	  OLED_ShowString(42, 6, "Vp", 8, 1);
	  OLED_ShowString(57, 6, "Vs", 8, 1);
	  OLED_ShowString(72, 6, "Tp", 8, 1);
	  OLED_ShowString(87, 6, "Ts", 8, 1);


	  OLED_ShowString(120, 6, "k", 8, 1);
	  show_sample_rate(1);


	  mode_set.channal_selct=CHANNAL_ONE;
	  mode_set.channal_state=1;
	  mode_set.channal_mode[0].input_gain=TWO_TIMES;
	  mode_set.channal_mode[0].time_gain=0;
	  mode_set.channal_mode[1].input_gain=TWO_TIMES;
	  mode_set.channal_mode[1].time_gain=0;
	  mode_set.select_falg=COMFIRM;
	  mode_set.current_mode=CHANGE_CH;
	  mode_set.vol_pos=64;
	  mode_set.vol_scl=3.3;
	  mode_set.vol_offset=0;
	  mode_set.stop_state=0;
	  mode_set.vol_scl_offset=1;
	  mode_set.spectrum_state=0;
	  mode_set.refresh_state=0;
}

void show_sample_rate(uint8_t state)
{
	uint16_t sample=get_sample_rate()/1000;
	if(sample<10)
	{
		OLED_ShowNum(116, 6,sample, 1, 8, state);
	}
	else if(sample<100)
	{
		OLED_ShowNum(106, 6,sample, 2, 8, state);
	}
	else
	{
		OLED_ShowNum(100, 6,sample, 3, 8, state);
	}
}
void show_menu()
{
	uint8_t state=0;
	  OLED_DrawLine(0,16, 128, 16, 1);
	  OLED_DrawLine(0,111, 128, 111, 1);
	if(mode_set.refresh_state)
	{
		OLED_Clear_rect(0,0,128,15);
		OLED_ShowString(120, 6, "k", 8, 1);
		if(mode_set.select_falg==COMFIRM)
			state=1;
		else state=0;
		ui_plot(state);
		mode_set.refresh_state=0;
	}
	wave_info_plot();
}

void ui_plot(uint8_t state)
{
	switch(mode_set.current_mode)
	{
		case CHANGE_CH:
		{
			switch(mode_set.channal_selct)
			{
			case CHANNAL_ONE:
				OLED_ShowString(0, 6, "CH1", 8, state);
				break;
			case CHANNAL_TWO:
				OLED_ShowString(0, 6, "CH2", 8, state);
				break;
			}

			switch(mode_set.channal_mode[1].input_gain)
			{
			case TWO_TIMES:
				OLED_ShowString(20, 6, "x2", 8, 1);
				break;
			case TEN_TIMES:
				OLED_ShowString(20, 6, "x10", 8, 1);
				break;
			}

			  OLED_ShowString(42, 6, "Vp", 8, 1);
			  OLED_ShowString(57, 6, "Vs", 8, 1);

			  OLED_ShowString(72, 6, "Tp", 8, 1);
			  OLED_ShowString(87, 6, "Ts", 8, 1);
			  show_sample_rate(1);
			  break;
		}

		case CHANGE_INPUT_GAIN:
		{
			switch(mode_set.channal_selct)
			{
			case CHANNAL_ONE:
				OLED_ShowString(0, 6, "CH1", 8, 1);
				break;
			case CHANNAL_TWO:
				OLED_ShowString(0, 6, "CH2", 8, 1);
				break;
			}
			switch(mode_set.channal_mode[mode_set.channal_selct].input_gain)
			{
			case TWO_TIMES:
				OLED_ShowString(20, 6, "x2", 8, state);
				break;
			case TEN_TIMES:
				OLED_ShowString(20, 6, "x10", 8, state);
				break;
			}
			  OLED_ShowString(42, 6, "Vp", 8, 1);
			  OLED_ShowString(57, 6, "Vs", 8, 1);

			  OLED_ShowString(72, 6, "Tp", 8, 1);
			  OLED_ShowString(87, 6, "Ts", 8, 1);
			  show_sample_rate(1);
			  break;
		}

		case CHANGE_Ts:
		{
			switch(mode_set.channal_selct)
			{
			case CHANNAL_ONE:
				OLED_ShowString(0, 6, "CH1", 8, 1);
				break;
			case CHANNAL_TWO:
				OLED_ShowString(0, 6, "CH2", 8, 1);
				break;
			}

			switch(mode_set.channal_mode[1].input_gain)
			{
			case TWO_TIMES:
				OLED_ShowString(20, 6, "x2", 8, 1);
				break;
			case TEN_TIMES:
				OLED_ShowString(20, 6, "x10", 8, 1);
				break;
			}

			  OLED_ShowString(42, 6, "Vp", 8, 1);
			  OLED_ShowString(57, 6, "Vs", 8, 1);

			  OLED_ShowString(72, 6, "Tp", 8, 1);
			  OLED_ShowString(87, 6, "Ts", 8, state);
			  show_sample_rate(1);
			  break;
		}

		case CHANGE_Vp:
		{
			switch(mode_set.channal_selct)
			{
			case CHANNAL_ONE:
				OLED_ShowString(0, 6, "CH1", 8, 1);
				break;
			case CHANNAL_TWO:
				OLED_ShowString(0, 6, "CH2", 8, 1);
				break;
			}

			switch(mode_set.channal_mode[1].input_gain)
			{
			case TWO_TIMES:
				OLED_ShowString(20, 6, "x2", 8, 1);
				break;
			case TEN_TIMES:
				OLED_ShowString(20, 6, "x10", 8, 1);
				break;
			}

			  OLED_ShowString(42, 6, "Vp", 8, state);
			  OLED_ShowString(57, 6, "Vs", 8, 1);

			  OLED_ShowString(72, 6, "Tp", 8, 1);
			  OLED_ShowString(87, 6, "Ts", 8, 1);
			  show_sample_rate(1);
			  break;
		}

		case CHANGE_Tp:
		{
			switch(mode_set.channal_selct)
			{
			case CHANNAL_ONE:
				OLED_ShowString(0, 6, "CH1", 8, 1);
				break;
			case CHANNAL_TWO:
				OLED_ShowString(0, 6, "CH2", 8, 1);
				break;
			}

			switch(mode_set.channal_mode[1].input_gain)
			{
			case TWO_TIMES:
				OLED_ShowString(20, 6, "x2", 8, 1);
				break;
			case TEN_TIMES:
				OLED_ShowString(20, 6, "x10", 8, 1);
				break;
			}

			  OLED_ShowString(42, 6, "Vp", 8, 1);
			  OLED_ShowString(57, 6, "Vs", 8, 1);

			  OLED_ShowString(72, 6, "Tp", 8, state);
			  OLED_ShowString(87, 6, "Ts", 8, 1);
			  show_sample_rate(1);
			  break;
		}

		case CHANGE_Vs:
		{
			switch(mode_set.channal_selct)
			{
			case CHANNAL_ONE:
				OLED_ShowString(0, 6, "CH1", 8, 1);
				break;
			case CHANNAL_TWO:
				OLED_ShowString(0, 6, "CH2", 8, 1);
				break;
			}

			switch(mode_set.channal_mode[1].input_gain)
			{
			case TWO_TIMES:
				OLED_ShowString(20, 6, "x2", 8, 1);
				break;
			case TEN_TIMES:
				OLED_ShowString(20, 6, "x10", 8, 1);
				break;
			}

			  OLED_ShowString(42, 6, "Vp", 8, 1);
			  OLED_ShowString(57, 6, "Vs", 8, state);

			  OLED_ShowString(72, 6, "Tp", 8, 1);
			  OLED_ShowString(87, 6, "Ts", 8, 1);

			  show_sample_rate(1);
			  break;
		}
		case CHANGE_Rate:
		{
			switch(mode_set.channal_selct)
			{
			case CHANNAL_ONE:
				OLED_ShowString(0, 6, "CH1", 8, 1);
				break;
			case CHANNAL_TWO:
				OLED_ShowString(0, 6, "CH2", 8, 1);
				break;
			}

			switch(mode_set.channal_mode[1].input_gain)
			{
			case TWO_TIMES:
				OLED_ShowString(20, 6, "x2", 8, 1);
				break;
			case TEN_TIMES:
				OLED_ShowString(20, 6, "x10", 8, 1);
				break;
			}

			  OLED_ShowString(42, 6, "Vp", 8, 1);
			  OLED_ShowString(57, 6, "Vs", 8, 1);

			  OLED_ShowString(72, 6, "Tp", 8, 1);
			  OLED_ShowString(87, 6, "Ts", 8, 1);

			  show_sample_rate(state);
			  break;
		}
	}
}
void wave_info_plot(void)
{
	wave_info.dc=get_dc_voltage(ADC_Value_buffer1[mode_set.adc_buffer_flag],mode_set.channal_mode[0].input_gain);
	wave_info.Vpp=get_pp_voltage(ADC_Value_buffer1[mode_set.adc_buffer_flag],mode_set.channal_mode[0].input_gain);

	dis_float(0,115,wave_info.dc,8, 1);
	OLED_ShowString(25, 115, "DC", 8, 1);

	dis_float(50,115,wave_info.Vpp,8, 1);
	OLED_ShowString(72, 115, "Vpp", 8, 1);

	OLED_Clear_rect(100, 119, 119, 120);
	dis_float(100,115,wave_info.frequency/1000,8,1);
	OLED_ShowString(120, 115, "k", 8, 1);
}

void dis_float(u8 x,u8 y,float f,u8 size1,u8 mode)
{
	uint8_t inter=f;
	uint8_t decimal=((int)(f*10))%10;
	if(f>9.9)
	{
		OLED_ShowNum(x, y, (int)f, 2, size1, mode);
	}
	else
	{
		OLED_ShowNum(x, y, inter, 1, size1, mode);
		OLED_ShowString(x+size1, y, ".", size1, mode);
		OLED_ShowNum(x+2*size1, y, decimal, 1, size1, mode);
	}
}

