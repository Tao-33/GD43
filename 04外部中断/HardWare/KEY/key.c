/************************************************************
 * 版权：2025CIMC Copyright。 
 * 文件：key.c
 * 作者: Lingyu Meng
 * 平台: 2025CIMC IHD-V04
 * 版本: Lingyu Meng     2025/3/10     V0.01    original
************************************************************/

/************************* 头文件 *************************/

#include "key.h"

/************************ 全局变量定义 ************************/


/************************************************************ 
 * Function :       KEY_Init
 * Comment  :       用于初始化KEY端口
 * Parameter:       null
 * Return   :       null
 * Author   :       Lingyu Meng
 * Date     :       2025-03-30 V0.1 original
************************************************************/

void KEY_Init(void)
{
	
	rcu_periph_clock_enable(RCU_GPIOE);    									// 初始化GPIO_E总线时钟  
	
	gpio_mode_set(GPIOE, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO_PIN_2);	// 配置PE2为上拉输入
	
	
}


/************************************************************ 
 * Function :       EXTI_PIN_Init
 * Comment  :       用于初始化中断
 * Parameter:       null
 * Return   :       null
 * Author   :       Lingyu Meng
 * Date     :       2025-03-30 V0.1 original
************************************************************/

void EXTI_PIN_Init(void)
{
	rcu_periph_clock_enable(RCU_SYSCFG);								//使能SYSCFG时钟，对应系统总线
	
	syscfg_exti_line_config(EXTI_SOURCE_GPIOE, EXTI_SOURCE_PIN2);		//连接PE2端口到中断线
	
	exti_init(EXTI_2, EXTI_INTERRUPT, EXTI_TRIG_FALLING);				//配置中断为下降沿触发
	
	nvic_irq_enable(EXTI2_IRQn,2,2);									//使能外部中断线 EXTI2； 设置优先级
	
	exti_interrupt_flag_clear(EXTI_2);									// 清除中断标志位


}

/************************************************************ 
 * Function :       EXTI2_IRQHandler
 * Comment  :       EXTI2的中断服务函数，触发中断后LED2翻转
 * Parameter:       null
 * Return   :       null
 * Author   :       Lingyu Meng
 * Date     :       2025-03-30 V0.1 original
************************************************************/
void EXTI2_IRQHandler(void)
{
	if(RESET != exti_interrupt_flag_get(EXTI_2))
	{
		gpio_bit_toggle(GPIOA,GPIO_PIN_5);   // 端口电平翻转
		
		exti_interrupt_flag_clear(EXTI_2);	 // 清除中断标志位
	
	}

}

/****************************End*****************************/

