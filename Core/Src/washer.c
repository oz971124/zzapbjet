#include "washer.h"


extern int get_button(GPIO_TypeDef *GPIO, uint16_t GPIO_Pin, uint8_t button_number);
extern void led_water_level(int water_level);
extern void led_all_off(void);
extern void ultrasonic_water_level_measurement(void);
extern void i2c_lcd_washer(int wash, int rinse, int dry, char *mode);
extern void wash_rinse_dry_motor_start(void);
extern void FND_print(int value);

extern void wash_duration_processing(void);
extern void rinse_duration_processing(void);
extern void dry_duration_processing(void);
extern void run_time_processing(void);

extern volatile uint16_t CCR_Value;
extern volatile int water_level;
extern volatile int TIM10_10ms_counter;

extern volatile int wash_duration;
extern volatile int rinse_duration;
extern volatile int dry_duration;

extern void complete_sound(void);
extern void bbig(void);

extern TIM_HandleTypeDef htim4;

volatile int auto_manual_flag = 0;		// auto(basic) 0 | manual : 1
volatile int stop_start_flag = 0;		// stop : 0 | start : 1 | pause : 2
volatile int wash_rinse_dry_flag = 0;	// 0 : wash | 1 : rinse | 2 : dry
volatile int mode_flag = 0;				// 0 : basic | 1 : bedding | 2 : wool | 3 : speed

volatile int run_time = 0;
volatile int wash_strength = 0;				// 0 : NULL | 1 : duty 40 | 2 : duty 70 | 3 : duty 100
volatile int rinse_time = 0;				// 0 : NULL | time : 1 ~ 5
volatile int dry_strength = 0;				// 0 : NULL | 1 : duty 40 | 2: duty 60 | 3 : duty 80 | 4 : duty 100
char mode[4][5] = {"BASI", "BEDD", "WOOL", "SPED"};

//volatile int wash_duration = 0;
//volatile int rinse_duration = 0;
//volatile int dry_duration = 0;

void washer_main(void)
{

	// CCR_Value = __HAL_TIM_GET_COMPARE(&htim4, TIM_CHANNEL_1);

	// BTN0 : START / PAUSE
	if (get_button(BUTTON0_GPIO_Port, BUTTON0_Pin, 0) == BUTTON_PRESS)
	{
		if (auto_manual_flag == 0)
		{
			if (stop_start_flag == 0)
			{
				stop_start_flag = 1;
				ultrasonic_water_level_measurement();

				if (mode_flag == 0)			// basic mode
				{
					wash_strength = 2;
					rinse_time = 2;
					dry_strength = 3;
				}
				else if (mode_flag == 1)	// bedding mode
				{
					wash_strength = 2;
					rinse_time = 3;
					dry_strength = 3;
				}
				else if (mode_flag == 2)	// wool mode
				{
					wash_strength = 1;
					rinse_time = 2;
					dry_strength = 1;
				}
				else						// speed mode
				{
					wash_strength = 2;
					rinse_time = 1;
					dry_strength = 3;
				}

				wash_duration_processing();
				rinse_duration_processing();
				dry_duration_processing();
				run_time_processing();

				i2c_lcd_washer(wash_strength, rinse_time, dry_strength, mode[mode_flag]);

			}
			else if (stop_start_flag == 1)			// PAUSE
			{
				stop_start_flag = 2;
				HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, 1);
				HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, 1);
			}
			else if (stop_start_flag == 2)									// RESTART
			{
				stop_start_flag = 1;
			}
		}

		if (auto_manual_flag == 1)
		{
			if (wash_strength != 0)
			{
				wash_rinse_dry_flag = 0;
			}
			else if (rinse_time != 0)
			{
				wash_rinse_dry_flag = 1;
			}
			else if (dry_strength != 0)
			{
				wash_rinse_dry_flag = 2;
			}

			if (stop_start_flag == 0)
			{
				stop_start_flag = 1;
				ultrasonic_water_level_measurement();

				wash_duration_processing();
				rinse_duration_processing();
				dry_duration_processing();
				run_time_processing();

				i2c_lcd_washer(wash_strength, rinse_time, dry_strength, mode[mode_flag]);
			}
			else if (stop_start_flag == 1)
			{
				stop_start_flag = 2;
				HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, 1);
				HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, 1);
			}
			else if (stop_start_flag == 2)
			{
				stop_start_flag = 1;
			}
		}
		bbig();
		printf("WAS : %d | RIN : %d | DRY : %d\n", wash_strength, rinse_time, dry_strength);
		printf("am : %d\n", auto_manual_flag);
		printf("ss : %d\n", stop_start_flag);
		printf("wrd : %d\n", wash_rinse_dry_flag);
		printf("mf : %d\n", mode_flag);
	}

	// BTN1 : WASH
	if (get_button(BUTTON1_GPIO_Port, BUTTON1_Pin, 1) == BUTTON_PRESS)
	{
		if (stop_start_flag == 0)
		{
			auto_manual_flag = 1;

			wash_strength++;
			if (wash_strength == 4) wash_strength = 1;

		}
		else if (stop_start_flag == 2)
		{
			wash_strength++;
			if (wash_strength == 4) wash_strength = 1;
		}
		i2c_lcd_washer(wash_strength, rinse_time, dry_strength, mode[mode_flag]);
		bbig();
		printf("WAS : %d | RIN : %d | DRY : %d\n", wash_strength, rinse_time, dry_strength);
		printf("am : %d\n", auto_manual_flag);
		printf("ss : %d\n", stop_start_flag);
		printf("wrd : %d\n", wash_rinse_dry_flag);
		printf("mf : %d\n", mode_flag);
	}

	// BTN2 : RINSE
	if (get_button(BUTTON2_GPIO_Port, BUTTON2_Pin, 2) == BUTTON_PRESS)
	{
		if (stop_start_flag == 0)
		{
			auto_manual_flag = 1;

			rinse_time++;
			if (rinse_time == 6) rinse_time = 1;
		}
		else if (stop_start_flag == 2)
		{
			rinse_time++;
			if (rinse_time == 6) rinse_time = 1;
		}
//		rinse_duration_processing();
		i2c_lcd_washer(wash_strength, rinse_time, dry_strength, mode[mode_flag]);
		bbig();
		// run_time += 10;
		printf("WAS : %d | RIN : %d | DRY : %d\n", wash_strength, rinse_time, dry_strength);
		printf("am : %d\n", auto_manual_flag);
					printf("ss : %d\n", stop_start_flag);
					printf("wrd : %d\n", wash_rinse_dry_flag);
					printf("mf : %d\n", mode_flag);
	}

	// BTN3 : DRY
	if (get_button(BUTTON3_GPIO_Port, BUTTON3_Pin, 3) == BUTTON_PRESS)
	{
		if (stop_start_flag == 0)
		{
			auto_manual_flag = 1;

			dry_strength++;
			if (dry_strength == 5) dry_strength = 1;
		}
		else if (stop_start_flag == 2)
		{
			dry_strength++;
			if (dry_strength == 5) dry_strength = 1;
		}
//		dry_duration_processing();
		i2c_lcd_washer(wash_strength, rinse_time, dry_strength, mode[mode_flag]);
		bbig();
		printf("WAS : %d | RIN : %d | DRY : %d\n", wash_strength, rinse_time, dry_strength);
		printf("am : %d\n", auto_manual_flag);
					printf("ss : %d\n", stop_start_flag);
					printf("wrd : %d\n", wash_rinse_dry_flag);
					printf("mf : %d\n", mode_flag);
	}

	// BTN4 : MODE
	if (get_button(USER_Btn_GPIO_Port, USER_Btn_Pin, 4) == BUTTON_PRESS)
	{
		mode_flag++;
		mode_flag %= 4;
		i2c_lcd_washer(wash_strength, rinse_time, dry_strength, mode[mode_flag]);
		bbig();

		printf("WAS : %d | RIN : %d | DRY : %d\n", wash_strength, rinse_time, dry_strength);
		printf("am : %d\n", auto_manual_flag);
					printf("ss : %d\n", stop_start_flag);
					printf("wrd : %d\n", wash_rinse_dry_flag);
					printf("mf : %d\n", mode_flag);
	}

	// START
	if (stop_start_flag == 1)
	{
		wash_rinse_dry_motor_start();
		led_water_level(water_level);
	}

	// timer
	if (stop_start_flag == 1)
	{
		if (run_time > 0)
		{

			if (TIM10_10ms_counter >= 100)
			{
				run_time--;
				printf("LEFT TIME : %d\n", run_time);
				printf("wrd_flag : %d\n", wash_rinse_dry_flag);
				if (wash_rinse_dry_flag == 0)
				{
					wash_duration--;
					// FND_print(wash_duration);
					printf("wash duration : %d\n", wash_duration);
					HAL_GPIO_WritePin(HW479_2_GPIO_Port, HW479_2_Pin, 1);	// red
					HAL_GPIO_WritePin(HW479_1_GPIO_Port, HW479_1_Pin, 0);
					HAL_GPIO_WritePin(HW479_3_GPIO_Port, HW479_3_Pin, 0);

					if (wash_duration <= 0)
					{
						if (rinse_time != 0) wash_rinse_dry_flag = 1;
						else if (dry_strength != 0) wash_rinse_dry_flag = 2;
					}
				}
				else if (wash_rinse_dry_flag == 1)
				{
					rinse_duration--;
					printf("rinse duration : %d\n", rinse_duration);
					HAL_GPIO_WritePin(HW479_3_GPIO_Port, HW479_3_Pin, 1);	// green
					HAL_GPIO_WritePin(HW479_1_GPIO_Port, HW479_1_Pin, 0);
					HAL_GPIO_WritePin(HW479_2_GPIO_Port, HW479_2_Pin, 0);
					if (rinse_duration <= 0)
					{
						if (dry_strength != 0) wash_rinse_dry_flag = 2;
					}
				}
				else
				{
					dry_duration--;
					printf("dry duration : %d\n", dry_duration);
					HAL_GPIO_WritePin(HW479_1_GPIO_Port, HW479_1_Pin, 1);	// blue
					HAL_GPIO_WritePin(HW479_2_GPIO_Port, HW479_2_Pin, 0);
					HAL_GPIO_WritePin(HW479_3_GPIO_Port, HW479_3_Pin, 0);

				}
				TIM10_10ms_counter = 0;
			}

		}
		else											// time 0 : stop
		{
			stop_start_flag = 0;
			auto_manual_flag = 0;
			wash_rinse_dry_flag = 0;
			mode_flag = 0;

			wash_strength = 0;
			rinse_time = 0;
			dry_strength = 0;
			water_level = 0;

			wash_duration = 0;
			rinse_duration = 0;
			dry_duration = 0;

			HAL_GPIO_WritePin(HW479_1_GPIO_Port, HW479_1_Pin, 0);
			HAL_GPIO_WritePin(HW479_2_GPIO_Port, HW479_2_Pin, 0);
			HAL_GPIO_WritePin(HW479_3_GPIO_Port, HW479_3_Pin, 0);

			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, 1);
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, 1);
			i2c_lcd_washer(wash_strength, rinse_time, dry_strength, mode[mode_flag]);
			printf("WAS : %d | RIN : %d | DRY : %d\n", wash_strength, rinse_time, dry_strength);
			printf("am : %d\n", auto_manual_flag);
			printf("ss : %d\n", stop_start_flag);
			printf("wrd : %d\n", wash_rinse_dry_flag);
			printf("mf : %d\n", mode_flag);
			led_all_off();
			complete_sound();
		}
	}

	FND_print(run_time);


}
