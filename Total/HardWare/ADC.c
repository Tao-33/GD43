#include "HeaderFiles.h"
#include "ADC.h"
void ADC_Port_Init(void){
	rcu_periph_clock_enable(RCU_GPIOC);//打开需要的引脚时钟
	rcu_periph_clock_enable(RCU_ADC0);//ADC0时钟打开
	gpio_mode_set(GPIOC,GPIO_MODE_ANALOG,GPIO_PUPD_NONE,GPIO_PIN_0);//设置模式为模拟量
	adc_clock_config(ADC_ADCCK_PCLK2_DIV8);//选择时钟分频
	ADC_Init();
	adc_software_trigger_enable(ADC0,ADC_ROUTINE_CHANNEL);
}

void ADC_Init(void){
	adc_deinit();
	adc_special_function_config(ADC0,ADC_CONTINUOUS_MODE,ENABLE);//选择ADC的模式，有扫描，连续等
	adc_data_alignment_config(ADC0,ADC_DATAALIGN_RIGHT);//选择数据对齐方式
	adc_channel_length_config(ADC0,ADC_ROUTINE_CHANNEL,1);//配置通道
	
	adc_routine_channel_config(ADC0,0,ADC_CHANNEL_10,ADC_SAMPLETIME_480);//配置触发源和采样时间
	adc_external_trigger_source_config(ADC0,ADC_ROUTINE_CHANNEL,ADC_EXTTRIG_INSERTED_T0_CH3);//配置触发源
	
	adc_external_trigger_config(ADC0,ADC_ROUTINE_CHANNEL,EXTERNAL_TRIGGER_RISING_FALLING);//触发使能
	adc_enable(ADC0);//ADC使能
	delay_1ms(1);
	
	adc_calibration_enable(ADC0);//校准
	
}


