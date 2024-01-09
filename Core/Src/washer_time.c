#include "washer_time.h"

extern volatile int water_level;

extern int wash_strength;				// 0 : duty 40 | 1: duty 70 | 2 : duty 100
extern volatile int rinse_time;					// 0 ~ 4
extern volatile int dry_strength;				// 0 : duty 40 | 1: duty 60 | 2 : duty 80 | 3 : duty 100
extern volatile int run_time;

volatile int wash_duration = 0;
volatile int rinse_duration = 0;
volatile int dry_duration = 0;

void wash_duration_processing(void)
{
	if (wash_strength == 0) wash_duration = 0;
	else wash_duration = water_level * WASH;
}

void rinse_duration_processing(void)
{
	rinse_duration = water_level * (rinse_time) * RINSE;
}

void dry_duration_processing(void)
{
	if (dry_strength == 0) dry_duration = 0;
	else dry_duration = DRY;
}

void run_time_processing(void)
{
	run_time = wash_duration + rinse_duration + dry_duration;
}

