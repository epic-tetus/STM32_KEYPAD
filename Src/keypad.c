#include "keypad.h"

#if KEYPAD_3X4

static uint8_t Keys[12] = {
	'1', '2', '3',
	'4', '5', '6',
	'7', '8', '9',
	'*', '0', '#'
};

#elif KEYPAD_4X4

static uint8_t Keys[16] = {
	'1', '2', '3','A',
	'4', '5', '6','B',
	'7', '8', '9','C',
	'*', '0', '#','D'
};

#endif

uint8_t Key = 0;

void Keypad_Init(void){
	GPIO_InitTypeDef GPIO_InitStruct;

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = R1_Pin|R2_Pin|R3_Pin|R4_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(ROW_PORT, &GPIO_InitStruct);
	
	#if KEYPAD_3X4
	GPIO_InitStruct.Pin = C1_Pin|C2_Pin|C3_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(COL_PORT, &GPIO_InitStruct);
	#elif KEYPAD_4X4
	GPIO_InitStruct.Pin = C1_Pin|C2_Pin|C3_Pin|C4_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(COL_PORT, &GPIO_InitStruct);
	#endif
	
	for(uint8_t i = 0; i < ROWS; i++){
		HAL_GPIO_WritePin(ROW_PORT, Row_Pin[i], GPIO_PIN_SET);
	}
}

char GetKey(void){
	for(uint8_t i = 0; i < ROWS; i++){
		HAL_GPIO_WritePin(ROW_PORT, Row_Pin[i], GPIO_PIN_RESET);
		for(uint8_t j = 0; j < COLS; j++){
			if(!HAL_GPIO_ReadPin(COL_PORT, Column_Pin[j]))
			{
				while(!HAL_GPIO_ReadPin(COL_PORT, Column_Pin[j]));
				#if KEYPAD_3X4
				Key = Keys[i * 3 + j];
				#elif KEYPAD_4X4
				Key = Keys[i * 4 + j];
				#endif
				return Key;
			}
		}
		HAL_GPIO_WritePin(ROW_PORT, Row_Pin[i], GPIO_PIN_SET);
	}
	return '\0';
}
