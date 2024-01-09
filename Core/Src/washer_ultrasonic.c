#include "washer_ultrasonic.h"

extern volatile int TIM10_10ms_ultrasonic;

volatile int distance;	// 거리를 측정한 펄스 갯수를 저장하는 변수
volatile int ic_cpt_finish_flag = 0;	// 초음파 거리 측정 완료 indicator 변수
volatile int water_level = 0;

// Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c 에서
// HAL_TIM_IC_CaptureCallback 복붙
// 초음파 센서의 ECHO핀의 상승 엣지와 하강 엣지 발생 시 이곳으로 들어 옴
volatile uint8_t  is_first_capture = 0;	// 0 : 상승 엣지 / 1 : 하강 엣지

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if (htim -> Instance == TIM3)
	{
		if (is_first_capture == 0)	// 상승 엣지일 때
		{
			__HAL_TIM_SET_COUNTER(htim, 0);		// clear HW counter
			is_first_capture = 1;	// 상승 엣지를 만났다는 flag
		}
		else if (is_first_capture == 1)	// 하강 엣지일 때
		{
			is_first_capture = 0;	// 다음 echo 펄스를 count 하기 위해 변수 초기화
			distance = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);	// 현재까지 count한 펄스 수를 일거옴
			ic_cpt_finish_flag = 1;	// 초음파 측정 완료
		}
	}
}

void ultrasonic_water_level_measurement(void)
{

	int dis;	// 거리를 측정한 펄스 갯수를 저장하는 변수

	TIM10_10ms_ultrasonic = 0;
	while (TIM10_10ms_ultrasonic <= 101)
	{
		if (TIM10_10ms_ultrasonic >= 100)	// 1초
		{

			make_trigger();
			char ultra_buff[20];
			if (ic_cpt_finish_flag)	// 초음파 측정이 완료 되었으면
			{
				ic_cpt_finish_flag = 0;
				dis = distance;
				dis = dis * 0.034 / 2;	// 1us 0.034cm 이동하므로 곱해주고 왕복이므로 편도를 구하려면 나누기 2해야함
				printf("dis : %dcm\n", dis);
			}
		}
	}

	if (dis > 100)
	{
		water_level = 4;
	}
	else if (dis > 50)
	{
		water_level = 3;
	}
	else if (dis > 20)
	{
		water_level = 2;
	}
	else
	{
		water_level = 1;
	}
	printf("WATER LEVEL : %d\n", water_level);
}

void make_trigger(void)
{
	HAL_GPIO_WritePin(ULTRASONIC_TRIGGER_GPIO_Port, ULTRASONIC_TRIGGER_Pin, 0);	// 매개 변수 값들은 main.h에 저장되어 있음
	delay_us(2);
	HAL_GPIO_WritePin(ULTRASONIC_TRIGGER_GPIO_Port, ULTRASONIC_TRIGGER_Pin, 1);	// 매개 변수 값들은 main.h에 저장되어 있음
	delay_us(10);
	HAL_GPIO_WritePin(ULTRASONIC_TRIGGER_GPIO_Port, ULTRASONIC_TRIGGER_Pin, 0);	// 매개 변수 값들은 main.h에 저장되어 있음
}
