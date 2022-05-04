#include "spectrum.h"
#include "main.h"
#include "wave.h"
#include "wave_task.h"
#include "menu.h"
#include <string.h>
#include "Adafruit_ZeroFFT.h"


extern TIM_HandleTypeDef htim1;

#define SPECTRUM_START_X 1
#define SPECTRUM_START_Y 1

#define GRAPH_START_X 1
#define GRAPH_START_Y 35
#define GRAPH_WIDTH 64
#define GRAPH_HEIGHT 100
#define SCALE 16

#define SPECTRUM_RESOLUTION 2
#define SPECTRUM_LENGTH (128 / SPECTRUM_RESOLUTION)
#define SPECTRUM_BEGIN (FFT_POINT/2 - SPECTRUM_LENGTH)
#define FFT_VALUE_MAX 64
void display_spectrum(uint8_t *y);
void clear_spectrum(uint8_t *y);
static void generate_spectrum(uint16_t FFTValue[FFT_POINT], uint8_t spectrum[SPECTRUM_LENGTH]);
void spectrum_task(void);
extern mode_set_t mode_set;
extern wave_info_t wave_info;
uint16_t FFTValue[FFT_POINT];
uint8_t graph[64] = {0};
void spectrum_task(void)
{
	static uint8_t clear_state=0;
	mode_set.calc_flag=1;
    memcpy(FFTValue,ADC_Value_buffer1[mode_set.adc_buffer_flag],2*FFT_POINT);
    mode_set.calc_flag=0;
	if(mode_set.stop_flag)
	{
		mode_set.adc_buffer_flag=(mode_set.adc_buffer_flag+1)%2;
		mode_set.stop_flag=0;
	}
    ZeroFFT((int16_t *)FFTValue);
    wave_info.frequency=get_frequency(FFTValue,get_sample_rate());
	if(clear_state)
	{
		clear_spectrum(graph);
		clear_state=0;
	}
	if(mode_set.spectrum_state==0)
	{
		return;
	}
    generate_spectrum(FFTValue, graph);
    display_spectrum(graph);
    clear_state=1;
}
static void generate_spectrum(uint16_t FFTValue[FFT_POINT], uint8_t spectrum[SPECTRUM_LENGTH])
{
	uint8_t i;
	for (i = 0; i < SPECTRUM_LENGTH; i++)
	{
		spectrum[i] = SPECTRUM_START_Y + (GRAPH_HEIGHT - 1) * (FFT_VALUE_MAX - FFTValue[i+SPECTRUM_BEGIN]) / FFT_VALUE_MAX;
	}

}

void display_spectrum(uint8_t *y)
{
    uint8_t i;

    for (i = 0; i < SPECTRUM_LENGTH - 1; i++)
    {
        OLED_DrawLine(i * 2, y[i], (i+1) * 2, y[i+1],1);
    }
}
void clear_spectrum(uint8_t *y)
{
    uint8_t i;

    for (i = 0; i < SPECTRUM_LENGTH - 1; i++)
    {
        OLED_ClearLine(i * 2, y[i], (i+1) * 2, y[i+1]);
    }
}
