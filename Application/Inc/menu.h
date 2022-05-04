#ifndef MENU_H
#define MENU_H

typedef enum
{
	TEN_TIMES=0,
	TWO_TIMES,
}input_gain_e;

typedef struct
{
	uint8_t time_gain;//0-5
	input_gain_e input_gain;
}channal_mode_t;

typedef enum
{
	CHANGE_CH=0,
	CHANGE_INPUT_GAIN,
	CHANGE_Vp,
	CHANGE_Vs,
	CHANGE_Tp,
	CHANGE_Ts,
	CHANGE_Rate,
	NUM,
}menu_mode_e;

typedef enum
{
	COMFIRM=0,
	SELECT,
}select_mode_e;

typedef enum
{
	CHANNAL_ONE=0,
	CHANNAL_TWO,
}channal_mode_e;

typedef struct
{
	channal_mode_e channal_selct;//0 channal 1, 1 channal 2,2 channal
	channal_mode_e channal_state;
	channal_mode_t channal_mode[2];
	select_mode_e select_falg;//1时 选择模式，0时确认模式
	uint8_t refresh_state;
	uint8_t spectrum_state;
	menu_mode_e current_mode;
	int16_t vol_pos;
	int16_t vol_offset;
	float vol_scl_offset;
	int16_t time_pos;
	uint8_t stop_state;
	uint8_t adc_buffer_flag;
	uint8_t calc_flag;
	uint8_t stop_flag;
	float vol_scl;
}mode_set_t;

void menu_init();
#endif

