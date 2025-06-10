/************************************************************
 * 版权：2025CIMC Copyright。 
 * 文件：key.c
 * 作者: Lingyu Meng
 * 平台: 2025CIMC IHD-V04
 * 版本: Lingyu Meng     2025/2/16     V0.01    original
************************************************************/

/************************* 头文件 *************************/

#include "Button1.h"
#include "gd32f4xx.h"                   // Device header
#include "Button.h"
/************************ 全局变量定义 ************************/

/************************************************************ 
 * Function :       KEY_Init
 * Comment  :       用于初始化LED端口
 * Parameter:       null
 * Return   :       null
 * Author   :       Lingyu Meng
 * Date     :       2025-02-30 V0.1 original
************************************************************/
struct Button btn1;
struct Button btn2;
struct Button btn3;
struct Button btn4;
struct Button btn5;
struct Button btn6;
void KEY1_Init(void)
{
    rcu_periph_clock_enable(KEY_CLK1);								// 初始化KEY总线时钟
    gpio_mode_set(KEY_CLK1, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP,
                 KEY1_PIN );		//配置GPIO模式为上拉输入
		
}
void KEY2_Init(void)
{
    rcu_periph_clock_enable(KEY_CLK2);								// 初始化KEY总线时钟
   gpio_mode_set(KEY_CLK2, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP,
                 KEY2_PIN|KEY3_PIN|KEY4_PIN|KEY5_PIN|KEY6_PIN );		//配置GPIO模式为上拉输入
}

/************************************************************ 
 * Function :       KEY_Stat
 * Comment  :       用于读取按键状态
 * Parameter:       按键端口和引脚
 * Return   :       按键状态：1为按键按下，0为按键未按下
 * Author   :       Lingyu Meng
 * Date     :       2025-02-30 V0.1 original
************************************************************/
uint8_t KEY_Stat(uint32_t port, uint16_t pin)
{
    if(gpio_input_bit_get(port, pin) == RESET)					//读取GPIO状态，如果按键被按下了
    {
        delay_1ms(20);											//延时消抖
        if(gpio_input_bit_get(port, pin) == RESET)				//再读一次GPIO，按键真的被按下了吗？
        {
            //while(gpio_input_bit_get(port, pin) == RESET);		//等待按键释放
            return 1;											//返回按键状态1
        }
    }
    return 0;
}
/****************************End*****************************/
//用这个
uint8_t read_button_GPIO(uint8_t button_id)
{
	switch(button_id)
	{
		case btn1_id:
			return gpio_input_bit_get(GPIOB,KEY1_PIN);
		case btn2_id:
			return gpio_input_bit_get(GPIOE,KEY2_PIN);
		case btn3_id:
			return gpio_input_bit_get(GPIOE,KEY3_PIN);
		case btn4_id:
			return gpio_input_bit_get(GPIOE,KEY4_PIN);
		case btn5_id:
			return gpio_input_bit_get(GPIOE,KEY5_PIN);
		case btn6_id:
			return gpio_input_bit_get(GPIOE,KEY6_PIN);
		default:
			return 0;
	}
}
