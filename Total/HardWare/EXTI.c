#include "HeaderFiles.h"
#include "EXTI.h"
void Test(void){
Led_Flash();
}
void EXTI_Pin_Init(void){
	rcu_periph_clock_enable(RCU_SYSCFG);
	syscfg_exti_line_config(EXTI_SOURCE_GPIOE,EXTI_SOURCE_PIN4);//配置中断线
	exti_init(EXTI_4,EXTI_INTERRUPT,EXTI_TRIG_FALLING);//初始化外部中断，选择模式和触发方式
	nvic_irq_enable(EXTI4_IRQn,2,2);
	exti_interrupt_flag_clear(EXTI_4);
}                           

//中断服务函数
void EXTI4_IRQHandler(void){
	if(RESET!=exti_interrupt_flag_get(EXTI_4)){
	gpio_bit_toggle(GPIOE,GPIO_PIN_3);//电平翻转
	exti_interrupt_flag_clear(EXTI_4);//清除中断标志位
	}
}


