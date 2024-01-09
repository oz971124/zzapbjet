#include "main.h"			// for GPIO handling

#define BUTTON_RELEASE 1	// 버튼을 뗀 상태 normal : High
#define BUTTON_PRESS 0		// 버튼을 누른 상태 Active-low
#define BUTTON_NUMBER 5		// 버튼 갯수 : 5

int get_button(GPIO_TypeDef *GPIO, uint16_t GPIO_Pin, uint8_t button_number);
