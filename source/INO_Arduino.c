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

int main(void) {

    BOARD_ConfigMPU();
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    BOARD_InitDebugConsole();
#endif

    if (SysTick_Config(SystemCoreClock / 1000U))
    {
        while (1)
        {
        }
    }

    initCAN();

    volatile static int i = 0 ;
    while(1) {
        i++ ;

        rotate_left_Motor();
        delay(10000U);

        readCAN();

        stop_Motor();

		delay(10000U);
    }
    return 0 ;
}
