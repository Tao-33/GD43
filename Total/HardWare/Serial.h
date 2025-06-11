#ifndef __SERIAL_H
#define __SERIAL_H
#include "HeaderFiles.h"
//这是两个缓存的数据
//extern uint8_t data_recv;


extern volatile uint8_t data_recv ;
extern volatile uint8_t data_ready ;
extern uint8_t Serial_TxPacket[4];				//FF 01 02 03 04 FE
extern uint8_t Serial_RxPacket[4];
extern uint8_t Serial_RxValue[4];
extern uint8_t Serial_RxFlag;//接收标志位
void  Serial_Init(void);
void gd_eval_com_init(void);
uint8_t Serial_GetRxFlag(void);
void Serial_SendPacket(void);
void Serial_SendData(uint8_t Byte);
void Serial_SendArray(uint8_t *Array, uint16_t Length);
void Serial_SendString(char *String);


#endif


