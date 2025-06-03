#ifndef __KEY_H
#include "HeaderFiles.h"

// KEY引脚定义
#define KEY1_PIN        GPIO_PIN_2
#define KEY2_PIN        GPIO_PIN_3
#define KEY3_PIN        GPIO_PIN_4
#define KEY4_PIN        GPIO_PIN_5

// KEY端口定义
#define KEY_PORT        GPIOE
#define KEY_CLK         RCU_GPIOE

void Key_Init(void);									//按键初始化
uint8_t KEY_State(uint32_t port, uint16_t pin);		//按键状态扫描

#define __KEY_H
#endif

