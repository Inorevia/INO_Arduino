#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MIMXRT1021.h"
#include "fsl_debug_console.h"
#include "fsl_flexcan.h"

#define TX_MESSAGE_BUFFER_INDEX (10)
#define RX_MESSAGE_BUFFER_INDEX (9)

volatile uint32_t g_systickCounter;
volatile uint32_t log1;
volatile uint32_t log2;
volatile uint32_t log3;
volatile uint32_t log4;
volatile bool g_pinSet = false;

void SysTick_Handler(void)
{
    if (g_systickCounter != 0U)
    {
        g_systickCounter--;
    }
}

void SysTick_DelayTicks(uint32_t n)
{
    g_systickCounter = n;
    while (g_systickCounter != 0U)
    {
    }
}

int main(void) {

    BOARD_ConfigMPU();
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    BOARD_InitDebugConsole();
#endif

    /* Avoiding CAN_CLOCK_CHECK_NO_AFFECTS error in case semihosting console is used */
    CLOCK_EnableClock(kCLOCK_Lpuart1);

    if (SysTick_Config(SystemCoreClock / 1000U))
    {
        while (1)
        {
        }
    }

    PRINTF("Hello World\n");

    flexcan_config_t flexcanConfig;
    flexcan_rx_mb_config_t mbConfig;
    flexcan_frame_t txFrame;
    flexcan_frame_t rxFrame;
    flexcanConfig.clkSrc               = kFLEXCAN_ClkSrc0;
//    flexcanConfig.bitRate              = 1000000U;
    flexcanConfig.baudRate = 1000000U;
    flexcanConfig.enableIndividMask    = false;
    flexcanConfig.enableLoopBack = false;
    flexcanConfig.enableSelfWakeup     = true;
    flexcanConfig.enableIndividMask    = false;
    flexcanConfig.disableSelfReception = false;
    flexcanConfig.enableListenOnlyMode = false;

    FLEXCAN_GetDefaultConfig(&flexcanConfig);
    FLEXCAN_Init(CAN1, &flexcanConfig, 40000000UL);

    FLEXCAN_Enable(CAN1, true);

    FLEXCAN_SetTxMbConfig(CAN1, TX_MESSAGE_BUFFER_INDEX, true);

    txFrame.format = kFLEXCAN_FrameFormatStandard;
    txFrame.type   = kFLEXCAN_FrameTypeData;
    txFrame.id     = FLEXCAN_ID_STD(0x01);
    txFrame.length = 8;



        mbConfig.format    = kFLEXCAN_FrameFormatStandard;
        mbConfig.type    = kFLEXCAN_FrameTypeData;
        mbConfig.id    = FLEXCAN_ID_STD(0x00);

    volatile static int i = 0 ;
    while(1) {
        i++ ;
        PRINTF(" -- 1 -- \n");

        txFrame.dataWord0 = CAN_WORD0_DATA_BYTE_0(0x02) |
    						CAN_WORD0_DATA_BYTE_1(0x00) |
    						CAN_WORD0_DATA_BYTE_2(0x00) |
    						CAN_WORD0_DATA_BYTE_3(0x00);
        txFrame.dataWord1 = CAN_WORD1_DATA_BYTE_4(0x00) |
    						CAN_WORD1_DATA_BYTE_5(0x18) |
    						CAN_WORD1_DATA_BYTE_6(0x00) |
    						CAN_WORD1_DATA_BYTE_7(0x1B);

        FLEXCAN_WriteTxMb(CAN1, TX_MESSAGE_BUFFER_INDEX, &txFrame);
        PRINTF(" 2 -- FLEXCAN_GetMbStatusFlags  %d\r\n", FLEXCAN_GetMbStatusFlags(CAN1, 1 << TX_MESSAGE_BUFFER_INDEX));

        log1 = FLEXCAN_GetMbStatusFlags(CAN1, 1 << TX_MESSAGE_BUFFER_INDEX);
        while (!FLEXCAN_GetMbStatusFlags(CAN1, 1 << TX_MESSAGE_BUFFER_INDEX));

        log2 = FLEXCAN_GetMbStatusFlags(CAN1, 1 << TX_MESSAGE_BUFFER_INDEX);

        PRINTF(" 3 -- FLEXCAN_GetMbStatusFlags  %d\r\n", FLEXCAN_GetMbStatusFlags(CAN1, 1 << TX_MESSAGE_BUFFER_INDEX));


        FLEXCAN_ClearMbStatusFlags(CAN1, 1 << TX_MESSAGE_BUFFER_INDEX);
        PRINTF(" -- 4 -- \n");

        PRINTF(" 5 -- FLEXCAN_GetMbStatusFlags  %d\r\n", FLEXCAN_GetMbStatusFlags(CAN1, 1 << TX_MESSAGE_BUFFER_INDEX));

        SysTick_DelayTicks(10000U);

        FLEXCAN_SetRxMbConfig(CAN1, RX_MESSAGE_BUFFER_INDEX, &mbConfig, true);
        PRINTF(" -- 6 -- \n");

        log3 = FLEXCAN_GetMbStatusFlags(CAN1, 1 << RX_MESSAGE_BUFFER_INDEX);
//		while (!FLEXCAN_GetMbStatusFlags(CAN1, 1 << RX_MESSAGE_BUFFER_INDEX));
        PRINTF(" -- 7 -- \n");

        FLEXCAN_ReadRxMb(CAN1, RX_MESSAGE_BUFFER_INDEX, &rxFrame);
        FLEXCAN_ClearMbStatusFlags(CAN1, 1 << RX_MESSAGE_BUFFER_INDEX);


                txFrame.dataWord0 = CAN_WORD0_DATA_BYTE_0(0x03) |
            						CAN_WORD0_DATA_BYTE_1(0x00) |
            						CAN_WORD0_DATA_BYTE_2(0x00) |
            						CAN_WORD0_DATA_BYTE_3(0x00);
                txFrame.dataWord1 = CAN_WORD1_DATA_BYTE_4(0x00) |
            						CAN_WORD1_DATA_BYTE_5(0x00) |
            						CAN_WORD1_DATA_BYTE_6(0x00) |
            						CAN_WORD1_DATA_BYTE_7(0x04);



                FLEXCAN_WriteTxMb(CAN1, TX_MESSAGE_BUFFER_INDEX, &txFrame);
                PRINTF(" -- 8 -- \n");

                FLEXCAN_ClearMbStatusFlags(CAN1, 1 << TX_MESSAGE_BUFFER_INDEX);
                PRINTF(" -- 9 -- \n");

                __asm volatile ("nop");

                SysTick_DelayTicks(10000U);

    }
    return 0 ;
}
