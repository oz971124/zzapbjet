#include "washer_dcmotor.h"

extern TIM_HandleTypeDef htim4;
extern volatile int wash_rinse_dry_flag;
extern volatile int wash_strength;				// 0 : NULL | 1 : duty 40 | 2 : duty 70 | 3 : duty 100
extern volatile int rinse_time;					// 0 : NULL | time : 1 ~ 5
extern volatile int dry_strength;				// 0 : NULL | 1 : duty 40 | 2: duty 60 | 3 : duty 80 | 4 : duty 100

volatile uint16_t CCR_Value = 0;			// fan speed

void wash_rinse_dry_motor_start(void)
{
	if (wash_rinse_dry_flag == 0)		// wash
	{
		CCR_Value = __HAL_TIM_GET_COMPARE(&htim4, TIM_CHANNEL_1);

		if (wash_strength == 1)
		{
			CCR_Value = 40;
		}
		else if (wash_strength == 2)
		{
			CCR_Value = 70;
		}
		else
		{
			CCR_Value = 100;
		}
		__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, CCR_Value);	// CCR_Value set
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, 1);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, 0);
	}
	else if (wash_rinse_dry_flag == 1)		// rinse
	{
		CCR_Value = __HAL_TIM_GET_COMPARE(&htim4, TIM_CHANNEL_1);
		CCR_Value = 70;
		__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, CCR_Value);	// CCR_Value set
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, 0);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, 1);
	}
	else									// dry
	{
		CCR_Value = __HAL_TIM_GET_COMPARE(&htim4, TIM_CHANNEL_1);

		if (dry_strength == 1)
		{
			CCR_Value = 40;
		}
		else if (dry_strength == 2)
		{
			CCR_Value = 60;
		}
		else if (dry_strength == 3)
		{
			CCR_Value = 80;
		}
		else
		{
			CCR_Value = 100;
		}
		__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, CCR_Value);	// CCR_Value set
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, 1);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, 0);
	}
}
