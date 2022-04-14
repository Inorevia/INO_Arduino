#ifndef INO_flexCAN_H
#define INO_flexCAN_H

//#include "fsl_common.h"

#define TX_MESSAGE_BUFFER_INDEX (10)
#define RX_MESSAGE_BUFFER_INDEX (9)

void initCAN();
void readCAN();

void rotate_left_Motor();
void stop_Motor();
void askPump();

#endif
