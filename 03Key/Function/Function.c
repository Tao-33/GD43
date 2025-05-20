/************************************************************
 * 版权：2025CIMC Copyright。 
 * 文件：Function.c
 * 作者: Lingyu Meng
 * 平台: 2025CIMC IHD-V04
 * 版本: Lingyu Meng     2025/2/16     V0.01    original
************************************************************/


/************************* 头文件 *************************/

#include "Function.h"

/************************* 宏定义 *************************/


/************************ 变量定义 ************************/


/************************ 函数定义 ************************/



/************************************************************ 
 * Function :       System_Init
 * Comment  :       用于初始化MCU
 * Parameter:       null
 * Return   :       null
 * Author   :       Lingyu Meng
 * Date     :       2025-02-30 V0.1 original
************************************************************/

void System_Init(void)
{
	systick_config();	// 时钟配置
	
	LED_Init();			// LED初始化
	
	KEY_Init();			// KEY初始化
}


/************************************************************ 
 * Function :       UsrFunction
 * Comment  :       用户程序功能: 按键控制LED点亮
 * Parameter:       null
 * Return   :       null
 * Author   :       Lingyu Meng
 * Date     :       2025-02-30 V0.1 original
************************************************************/

void UsrFunction(void)
{
	
	while(1)
	{
		// 检测Key1：LED1 点亮
        if(KEY_Stat(KEY_PORT,KEY1_PIN))
        {
            LED1_ON();
			
        }
        
        // 检测Key21：LED2 点亮
        else if(KEY_Stat(KEY_PORT,KEY2_PIN))
        {
			LED2_ON();
            
        }
        
        // 检测Key31：LED3 点亮
        else if(KEY_Stat(KEY_PORT,KEY3_PIN))
        {
			LED3_ON();
            
        }
        
        // 检测Key41：LED4 点亮
        else if(KEY_Stat(KEY_PORT,KEY4_PIN))
        {
			LED4_ON();
            
        }
		// 默认状态：LED全灭
		else{
			LED_Off();
		}
	}
}


/****************************End*****************************/

