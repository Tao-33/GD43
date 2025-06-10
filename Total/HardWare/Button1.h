/************************************************************
 * 版权：2025CIMC Copyright。 
 * 文件：key.h
 * 作者: Lingyu Meng
 * 平台: 2025CIMC IHD-V04
 * 版本: Lingyu Meng     2025/2/16     V0.01    original
************************************************************/
#ifndef __KEY_H
#define __KEY_H

/************************* 头文件 *************************/

#include "HeaderFiles.h"

/************************* 宏定义 *************************/

// KEY引脚定义
#define KEY1_PIN        GPIO_PIN_0
#define KEY2_PIN        GPIO_PIN_7
#define KEY3_PIN        GPIO_PIN_9
#define KEY4_PIN        GPIO_PIN_11
#define KEY5_PIN        GPIO_PIN_13
#define KEY6_PIN        GPIO_PIN_15
enum Button_IDs {
	btn1_id,
	btn2_id,
	btn3_id,
	btn4_id,
	btn5_id,
	btn6_id,
};
// KEY端口定义
#define KEY_PORT        GPIOE
#define KEY_CLK1         RCU_GPIOB
#define KEY_CLK2         RCU_GPIOE
/************************ 变量定义 ************************/


/************************ 函数定义 ************************/
uint8_t read_button_GPIO(uint8_t button_id);
void KEY1_Init(void);									//按键初始化
uint8_t KEY_Stat(uint32_t port, uint16_t pin);		//按键状态扫描
void KEY2_Init(void);				    
#endif


/****************************End*****************************/

