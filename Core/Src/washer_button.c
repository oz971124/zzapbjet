#include "washer_button.h"

// 초기 버튼 상태 table
char button_status[BUTTON_NUMBER] = {BUTTON_RELEASE, BUTTON_RELEASE, BUTTON_RELEASE, BUTTON_RELEASE, BUTTON_RELEASE};

// get_button(gpio, pin, button)
// 눌렀다 떼면 BUTTON_RELEASE를 리턴
int get_button(GPIO_TypeDef *GPIO, uint16_t GPIO_Pin, uint8_t button_number)
{
	unsigned char curr_state;
	curr_state = HAL_GPIO_ReadPin(GPIO, GPIO_Pin);

	// 버튼이 눌러졌으나 처음 상태 = noise
	if (curr_state == BUTTON_PRESS && button_status[button_number] == BUTTON_RELEASE)
	{
		HAL_Delay(80);	// noise가 지나가기를 기다림
		button_status[button_number] = BUTTON_PRESS;	// 현재 버튼 상태를 저장
		return BUTTON_RELEASE;	// 버튼이 눌러진 상태지만 아직 noise 상태로 인정
	}
	// 이전에 버튼이 눌려진 상태고 지금은 버튼을 뗀 상태이면
	else if (curr_state == BUTTON_RELEASE && button_status[button_number] == BUTTON_PRESS)
	{
		button_status[button_number] = BUTTON_RELEASE;	// button_status table을 초기화
		HAL_Delay(80);
		return BUTTON_PRESS;	// 버튼을 1번 눌렀다 뗀 것으로 인정
	}

	return BUTTON_RELEASE;
}
