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
	systick_config();     // 时钟配置

	LED_Init();          // LED 初始化
}
/************************************************************ 
 * Function :       Init_LED_Stat
 * Comment  :       系统初始化时用LED显示状态
 * Parameter:       null
 * Return   :       null
 * Author   :       Lingyu Meng
 * Date     :       2025-03-10 V0.1 original
************************************************************/

void Init_LED_Stat(void)
{
	//功能说明：
	//当系统上电后，执行下面的程序
	//LED1~4间隔1秒依次点亮后关断
	//用来指示系统上电后进入用户程序的动作
	
	LED1_ON();
    delay_1ms(1000);
	LED2_ON();
    delay_1ms(1000);
	LED3_ON();
    delay_1ms(1000);
	LED4_ON();
    delay_1ms(1000);
	LED1_OFF();
	LED2_OFF();
	LED3_OFF();
	LED4_OFF();

}
/************************************************************ 
 * Function :       UsrFunction
 * Comment  :       用户程序功能: LED1闪烁
 * Parameter:       null
 * Return   :       null
 * Author   :       Lingyu Meng
 * Date     :       2025-02-30 V0.1 original
************************************************************/

void UsrFunction(void)
{
	//Init_LED_Stat();
	
	while(1)
	{
		LED_Flash();
	
	}
}


/****************************End*****************************/

