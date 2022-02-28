#include "ino_core_pins.h"
#include "fsl_gpio.h"


GPIO_Type* getGPIObase_FromPinNumber(uint8_t pin);

void anaglogWrite(uint8_t pin, int val){

}

uint16_t analogRead(uint8_t pin){

}

void digitalWrite(uint8_t pin, unsigned char val){
	if(val == LOW){
		val = 0U;
	}
	else if (val == HIGH){
		val = 1U;
	}
	GPIO_PinWrite(getGPIObase_FromPinNumber(pin), pin, val);

}

bool digitalRead(uint8_t pin){

}

GPIO_Type* getGPIObase_FromPinNumber(uint8_t pin){

	GPIO_Type * retVal = 0;

	switch(pin){

		case ADD_LED_PIN:	retVal = ADD_LED_GPIO;
		break;
	}

	return retVal;
}
