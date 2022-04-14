#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MIMXRT1021.h"
#include "fsl_debug_console.h"
#include "fsl_flexcan.h"
#include "INO_flexCAN.h"

flexcan_config_t flexcanConfig;
flexcan_rx_mb_config_t mbConfig;
flexcan_frame_t txFrame;
flexcan_frame_t rxFrame;

// txFrame.type   = kFLEXCAN_FrameTypeData;
// txFrame.format = kFLEXCAN_FrameFormatStandard;

#define SetMsg(x0,x1,x2,x3,x4,x5,x6,x7) \
  txFrame.format = kFLEXCAN_FrameFormatStandard;	\
  txFrame.type   = kFLEXCAN_FrameTypeData;	\
  txFrame.id = FLEXCAN_ID_STD(0x109); \
  txFrame.length = 8; \
  txFrame.dataByte0 = x0; \
  txFrame.dataByte1 = x1; \
  txFrame.dataByte2 = x2; \
  txFrame.dataByte3 = x3; \
  txFrame.dataByte4 = x4; \
  txFrame.dataByte5 = x5; \
  txFrame.dataByte6 = x6; \
  txFrame.dataByte7 = x7;

void sendCAN();

void initCAN(){

    /* Avoiding CAN_CLOCK_CHECK_NO_AFFECTS error in case semihosting console is used */
    CLOCK_EnableClock(kCLOCK_Lpuart1);

    FLEXCAN_GetDefaultConfig(&flexcanConfig);
    FLEXCAN_Init(CAN1, &flexcanConfig, 40000000UL);

    FLEXCAN_Enable(CAN1, true);

    FLEXCAN_SetTxMbConfig(CAN1, TX_MESSAGE_BUFFER_INDEX, true);
    FLEXCAN_SetRxMbConfig(CAN1, RX_MESSAGE_BUFFER_INDEX, &mbConfig, true);

     mbConfig.format    = kFLEXCAN_FrameFormatStandard;
     mbConfig.type    = kFLEXCAN_FrameTypeData;
     mbConfig.id    = FLEXCAN_ID_STD(0x00);
}


void rotate_left_Motor(){
    SetMsg(0x02, 0x00, 0x00, 0x00, 0x00, 0x28, 0x00, 0x2B);
    sendCAN();
}

void askPump(){
    SetMsg(0x00, 0x00, 0x00, 0x00, 0x00, 0x5A, 0x52, 0xCC);
    sendCAN();
}

void readCAN(){

//	while (!FLEXCAN_GetMbStatusFlags(CAN1, 1 << RX_MESSAGE_BUFFER_INDEX));

    FLEXCAN_ReadRxMb(CAN1, RX_MESSAGE_BUFFER_INDEX, &rxFrame);
    FLEXCAN_ClearMbStatusFlags(CAN1, 1 << RX_MESSAGE_BUFFER_INDEX);
}

void stop_Motor(){

    SetMsg(0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04);
    sendCAN();
}

void sendCAN(){

	FLEXCAN_WriteTxMb(CAN1, TX_MESSAGE_BUFFER_INDEX, &txFrame);

	while (!FLEXCAN_GetMbStatusFlags(CAN1, 1 << TX_MESSAGE_BUFFER_INDEX));

	FLEXCAN_ClearMbStatusFlags(CAN1, 1 << TX_MESSAGE_BUFFER_INDEX);
}
