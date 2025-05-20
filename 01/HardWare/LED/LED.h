/************************************************************
 * 版权：2025CIMC Copyright。 
 * 文件：led.h
 * 作者: Lingyu Meng
 * 平台: 2025CIMC IHD-V04
 * 版本: Lingyu Meng     2025/2/16     V0.01    original
************************************************************/
#ifndef __LED_H
#define __LED_H

/************************* 头文件 *************************/

#include "HeaderFiles.h"

/************************* 宏定义 *************************/

//定义第一颗LED状态函数
#define    LED1_OFF()      gpio_bit_reset(GPIOA, GPIO_PIN_4) 	 // 低电平   关灯 
#define    LED1_ON()       gpio_bit_set(GPIOA, GPIO_PIN_4)       // 高电平   开灯

//定义第二颗LED状态函数
#define    LED2_OFF()      gpio_bit_reset(GPIOA, GPIO_PIN_5) 	 // 低电平   关灯 
#define    LED2_ON()       gpio_bit_set(GPIOA, GPIO_PIN_5)       // 高电平   开灯

//定义第三颗LED状态函数
#define    LED3_OFF()      gpio_bit_reset(GPIOA, GPIO_PIN_6) 	 // 低电平   关灯 
#define    LED3_ON()       gpio_bit_set(GPIOA, GPIO_PIN_6)       // 高电平   开灯 

//定义第四颗LED状态函数
#define    LED4_OFF()      gpio_bit_reset(GPIOA, GPIO_PIN_7) 	 // 低电平   关灯 
#define    LED4_ON()       gpio_bit_set(GPIOA, GPIO_PIN_7)       // 高电平   开灯
 
/************************ 变量定义 ************************/


/************************ 函数定义 ************************/

void LED_Init(void);     // LED 初始化
				    
#endif


/****************************End*****************************/

