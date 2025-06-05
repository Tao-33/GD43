#ifndef __SERIAL_H
#define __SERIAL_H
#include "HeaderFiles.h"
//这是两个缓存的数据
extern uint8_t Serial_TxPacket[4];				//FF 01 02 03 04 FE
extern uint8_t Serial_RxPacket[4];
extern uint8_t Serial_RxValue[4];
extern uint8_t Serial_RxFlag;//接收标志位
void  Serial_Init(void);
uint8_t Serial_GetRxFlag(void);
void Serial_SendPacket(void);


#endif


