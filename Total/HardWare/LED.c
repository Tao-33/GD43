#include "HeaderFiles.h"

void Led_Init(void){
	rcu_periph_clock_enable(RCU_GPIOE);
	gpio_mode_set(GPIOE,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,GPIO_PIN_2);
	gpio_output_options_set(GPIOE,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_2);
	gpio_mode_set(GPIOE,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,GPIO_PIN_3);
	gpio_output_options_set(GPIOE,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_3);	
}

void Led_Flash(void){
	gpio_bit_set(GPIOE,GPIO_PIN_2);
	delay_1ms(500);
	gpio_bit_reset(GPIOE,GPIO_PIN_2);
}

void Led_OFF(void){
	gpio_bit_reset(GPIOE,GPIO_PIN_2);
}
