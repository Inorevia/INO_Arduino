#ifndef INO_CORE_PINS_H
#define INO_CORE_PINS_H

#include "fsl_common.h"
#include "board.h"

#define HIGH	1U
#define LOW		0U

//#define INPUT		0
//#define OUTPUT		1
//#define INPUT_PULLUP	2
//#define INPUT_PULLDOWN   3
//#define OUTPUT_OPENDRAIN 4
//#define INPUT_DISABLE   5
//#define LSBFIRST	0
//#define MSBFIRST	1
//#define _BV(n)		(1<<(n))
//#define CHANGE		4
//#define FALLING		2
//#define RISING		3


#define ADD_LED_GPIO    BOARD_USER_LED_GPIO
#define ADD_LED_PIN		BOARD_USER_LED_GPIO_PIN

void anaglogWrite(uint8_t pin, int val);
uint16_t analogRead(uint8_t pin);

void digitalWrite(uint8_t pin, unsigned char val);
bool digitalRead(uint8_t pin);

#endif
