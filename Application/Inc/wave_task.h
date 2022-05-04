#ifndef __WAVE_TASK_H
#define __WAVE_TASK_H
#define MAX_TIME_GAIN  (SAVE_SPACE/ONE_TIME_ZOOM)-1
#define ONE_TIME_ZOOM  64
#define ONE_TIME_SHIFT 3
void wave_task(void);
void show_menu();



typedef struct
{
	float dc;
	float frequency;
	float Vpp;
	float half_range;
	float max_voltage;
	float min_voltage;
	float center_voltage;
}wave_info_t;




#endif

