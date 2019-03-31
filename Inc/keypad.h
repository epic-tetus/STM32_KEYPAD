#include "stm32f1xx_hal.h"

#ifndef keypad
#define keypad

#define KEYPAD_3X4 1
#define KEYPAD_4X4 0

#define ROW_PORT GPIOA
#define R1_Pin GPIO_PIN_0
#define R2_Pin GPIO_PIN_1
#define R3_Pin GPIO_PIN_2
#define R4_Pin GPIO_PIN_3

#define COL_PORT GPIOA
#define C1_Pin GPIO_PIN_4
#define C2_Pin GPIO_PIN_5
#define C3_Pin GPIO_PIN_6
#define C4_Pin GPIO_PIN_7

// OUTPUT
static uint8_t Row_Pin[4] = {
	R1_Pin,
	R2_Pin,
	R3_Pin,
	R4_Pin
};

// INPUT
static uint8_t Column_Pin[4] = {
	C1_Pin,
	C2_Pin,
	C3_Pin,
	C4_Pin
};


#if KEYPAD_3X4

#define ROWS 4
#define COLS 3

static uint8_t Keys[12];

#elif KEYPAD_4X4

#define ROWS 4
#define COLS 4

static uint8_t Keys[16];

#endif

void Keypad_Init(void);
char GetKey(void);

#endif
