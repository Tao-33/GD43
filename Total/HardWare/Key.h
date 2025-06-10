#ifndef __KEY_H
#include "HeaderFiles.h"

// KEY引脚定义
#define KEY1_PIN        GPIO_PIN_0
#define KEY2_PIN        GPIO_PIN_7
#define KEY3_PIN        GPIO_PIN_9
#define KEY4_PIN        GPIO_PIN_11
#define KEY5_PIN        GPIO_PIN_13
#define KEY6_PIN        GPIO_PIN_15

// KEY端口定义
#define KEY_PORT         GPIOE
#define KEY_CLK1         RCU_GPIOB
#define KEY_CLK2         RCU_GPIOE
enum Button_IDs {
	btn1_id,
	btn2_id,
	btn3_id,
	btn4_id,
	btn5_id,
	btn6_id,
};
void Key_Init(void);									//按键初始化
uint8_t KEY_State(uint32_t port, uint16_t pin);		//按键状态扫描
uint8_t read_button_GPIO(uint8_t button_id);

#define __KEY_H
#endif

