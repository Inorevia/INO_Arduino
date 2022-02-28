#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MIMXRT1021.h"
#include "fsl_debug_console.h"
//#include "fsl_flexcan.h"
#include "delay.h"
#include "INO_flexCAN.h"
#include "ino_core_pins.h"

void blinkUSERLED();


int main(void) {

    BOARD_ConfigMPU();
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    BOARD_InitDebugConsole();
#endif

    initDelay();
    initCAN();

    while(1) {
    	PRINTF(" --- 1 --- \n");
        rotate_left_Motor();
    	PRINTF(" --- 2 --- \n");
        delay(500U);
    	PRINTF(" --- 3 --- \n");
        readCAN();
    	PRINTF(" --- 4 --- \n");
        stop_Motor();
    	PRINTF(" --- 5 --- \n");

        blinkUSERLED();
    }
    return 0 ;
}

void blinkUSERLED(){

	static bool g_pinSet = false;

    if (g_pinSet)	{
        digitalWrite(ADD_LED_PIN, LOW);
        g_pinSet = false;
    }
    else	{
    	digitalWrite(ADD_LED_PIN, HIGH);
        g_pinSet = true;
    }
	delay(100U);
}
