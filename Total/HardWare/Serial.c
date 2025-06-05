#include "HeaderFiles.h"
#include "Serial.h"

void  Serial_Init(void){
	rcu_periph_clock_enable(RCU_GPIOA);
	rcu_periph_clock_enable(RCU_USART0);
	
	gpio_af_set(GPIOA,GPIO_AF_7,GPIO_PIN_9|GPIO_PIN_10);//使用复用才能使用串口
	
	gpio_mode_set(GPIOA,GPIO_MODE_AF,GPIO_PUPD_PULLUP,GPIO_PIN_9);
	gpio_output_options_set(GPIOA,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_9);
	
	gpio_mode_set(GPIOA,GPIO_MODE_AF,GPIO_PUPD_NONE,GPIO_PIN_10);
	gpio_output_options_set(GPIOA,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_10);
	
	usart_deinit(USART0);//先复位串口
	usart_baudrate_set(USART0,115200);//定义波特率
	usart_parity_config(USART0,USART_PM_NONE);//定义校验方式
	usart_word_length_set(USART0,USART_WL_8BIT);//定义数据字长，八位或九位
	usart_stop_bit_set(USART0,USART_STB_1BIT);//定义停止位一位
	usart_transmit_config(USART0,USART_TRANSMIT_ENABLE);//使能发送
	
	//关掉硬件流控进行控制
	usart_hardware_flow_rts_config(USART0,USART_RTS_DISABLE);
	usart_hardware_flow_cts_config(USART0,USART_CTS_DISABLE);
	
	nvic_irq_enable(USART0_IRQn,0,0);//使能对应的NVIC中断
	usart_enable(USART0);//使能串口
}

void Serial_SendData(uint16_t *buf,uint16_t len){
	uint16_t t;
	for(t=0;t<len;t++){
	while(usart_flag_get(USART0,USART_FLAG_TC)==RESET);
	usart_data_transmit(USART0,buf[t]);
	}
	while(usart_flag_get(USART0,USART_FLAG_TC)==RESET);
}

int fputc(int ch,FILE *f){
	usart_data_transmit(USART0,(uint8_t)ch);
	while(usart_flag_get(USART0,USART_FLAG_TBE)==RESET);
	return ch;
}
	


