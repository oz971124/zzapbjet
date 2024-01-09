#include "washer_led.h"

extern int get_button(GPIO_TypeDef *GPIO, uint16_t GPIO_Pin, uint8_t button_number);
extern volatile int water_level;

void led_all_off(void)
{
	HAL_GPIO_WritePin(GPIOD, 0xff, 0);
}

void led_water_level(void)
{
	led_all_off();
	switch (water_level)
	{
		case 1 :
			HAL_GPIO_WritePin(GPIOD, 0x03, 1);
			break;
		case 2 :
			HAL_GPIO_WritePin(GPIOD, 0x0f, 1);
			break;
		case 3 :
			HAL_GPIO_WritePin(GPIOD, 0x3f, 1);
			break;
		case 4 :
			HAL_GPIO_WritePin(GPIOD, 0xff, 1);
			break;
	}
}

void led_processing(void)
{
	if (get_button(BUTTON0_GPIO_Port, BUTTON0_Pin, 0) == BUTTON_PRESS)
	{
		printf("BTN0\n");
	}
	if (get_button(BUTTON1_GPIO_Port, BUTTON1_Pin, 1) == BUTTON_PRESS)
	{
		printf("BTN1\n");
	}
	if (get_button(BUTTON2_GPIO_Port, BUTTON2_Pin, 2) == BUTTON_PRESS)
	{
		printf("BTN2\n");
	}
	if (get_button(BUTTON3_GPIO_Port, BUTTON3_Pin, 3) == BUTTON_PRESS)
	{
		printf("BTN3\n");
	}
}
