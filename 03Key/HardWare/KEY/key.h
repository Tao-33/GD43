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
#define KEY1_PIN        GPIO_PIN_2
#define KEY2_PIN        GPIO_PIN_3
#define KEY3_PIN        GPIO_PIN_4
#define KEY4_PIN        GPIO_PIN_5

// KEY端口定义
#define KEY_PORT        GPIOE
#define KEY_CLK         RCU_GPIOE
 
/************************ 变量定义 ************************/


/************************ 函数定义 ************************/

void KEY_Init(void);									//按键初始化
uint8_t KEY_Stat(uint32_t port, uint16_t pin);		//按键状态扫描
				    
#endif


/****************************End*****************************/

