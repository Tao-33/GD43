#include "HeaderFiles.h"
#include "Function.h"
int FLAG=0;
uint8_t Key_num=0;
void BTN1_SINGLEClick_Handler(void* btn)
{
	Key_num=1;
}
void BTN1_LONG_PRESS_HOLD_Handler(void* btn)
{
	Key_num=10;
}
void BTN2_SINGLEClick_Handler(void* btn)
{
	Key_num=2;
}
void BTN3_SINGLEClick_Handler(void* btn)
{
	Key_num=3;
}
void BTN4_SINGLEClick_Handler(void* btn)
{
	Key_num=4;
}
void BTN5_SINGLEClick_Handler(void* btn)
{
	Key_num=5;
}
void BTN6_SINGLEClick_Handler(void* btn)
{
	Key_num=6;
}

void System_Init(void)
{
	systick_config();     // 时钟配置
	Led_Init();
	KEY1_Init();
	KEY2_Init();
	EXTI_Pin_Init();
	Serial_Init();
//	gd_eval_com_init();
	OLED_Init();
	DMA_ADC_config_Init();
	RTC_Init();	
	//按键绑定操作*****************************************
	button_init(&btn1, read_button_GPIO, 0, btn1_id);
	button_init(&btn2, read_button_GPIO, 0, btn2_id);
	button_init(&btn3, read_button_GPIO, 0, btn3_id);
	button_init(&btn4, read_button_GPIO, 0, btn4_id);
	button_init(&btn5, read_button_GPIO, 0, btn5_id);
	button_init(&btn6, read_button_GPIO, 0, btn6_id);
	button_attach(&btn1, SINGLE_CLICK,BTN1_SINGLEClick_Handler);
	button_attach(&btn1, LONG_PRESS_HOLD ,BTN1_LONG_PRESS_HOLD_Handler);
	button_attach(&btn2, SINGLE_CLICK,BTN2_SINGLEClick_Handler);
	button_attach(&btn3, SINGLE_CLICK,BTN3_SINGLEClick_Handler);
	button_attach(&btn4, SINGLE_CLICK,BTN4_SINGLEClick_Handler);
	button_attach(&btn5, SINGLE_CLICK,BTN5_SINGLEClick_Handler);
	button_attach(&btn6, SINGLE_CLICK,BTN6_SINGLEClick_Handler);
	button_start(&btn1);
	button_start(&btn2);
	button_start(&btn3);
	button_start(&btn4);
	button_start(&btn5);
	button_start(&btn6);
	//**************************************************
	TIM2_Init(240-1,3000-1);//开启按键的定时器
}

void UsrFunction(void)
{

	printf("Hello CIMC");
	//rtc_setup();

	while(1)
	{
		
		/*LED测试
		
		*/
		
		/*串口测试，可以接收发送HEX数据包
//		// 在主循环手动设置测试数据
//		Serial_RxPacket[0] = 0xAA; 
//		Serial_RxFlag = 1;
		OLED_ShowNum(1,1,5,2,16);
		OLED_Refresh();
		if (Serial_GetRxFlag() == 1)
		{
			//value = atoi((char*)Serial_RxPacket);
			//OLED_ShowNum(2,1,value,4);
			OLED_ShowHexNum(10,15, Serial_RxPacket[0], 2);
			OLED_ShowHexNum(20,15, Serial_RxPacket[1], 2);
			OLED_ShowHexNum(30,15, Serial_RxPacket[2], 2);
			OLED_ShowHexNum(40,15, Serial_RxPacket[3], 2);
		}
		*/
		
		/*ADC功能测试，可以将ADC值通过串口发送，信息格式可以用Vofa+显示曲线
		int adc_value;
		adc_flag_clear(ADC0,ADC_FLAG_EOC);//清除标志位
		while(SET!=adc_flag_get(ADC0,ADC_FLAG_EOC)){}
		adc_value=ADC_RDATA(ADC0);			
		printf("ADC_Value:%d,%.2f\n",adc_value,3.3*(adc_value/4095.0));
		*/
		
		/*ADC功能测试，带数据转运DMA		
		printf("ADC_Value:%d,%.2f\n",adc_value[0],3.3*(adc_value[0]/4095.0));
		OLED_Printf(0,16,16,"ADC_V:%d,%.2f\n",adc_value[0],3.3*(adc_value[0]/4095.0));
		OLED_Refresh(); 
		*/
		
		/*OLED测试，可以使用OLED_Printf()函数进行方便的OLED显示操作
		OLED_Printf(0, 16, 16, "Ki:%4.2f Ki:%d", 23.33,5);
		OLED_Refresh(); 
		*/
		
		/* 定时中断测试
		OLED_Printf(0, 16, 16, "cnt:%5d", cnt);
		OLED_Refresh(); 
		*/
		
		/*按键逻辑测试
		OLED_Printf(0, 16, 16, "key_Num:%5d", Key_num);
		OLED_Refresh(); 
		*/
		
		/*RTC测试
		rtc_show_time();
		delay_1ms(1000);
		*/
		rtc_show_time();
//		delay_1ms(1000);		
		
		//delay_1ms(1000);
		if(Key_num==4){	
		FLAG=1;
		Key_num=0;
//		rtc_setup();						
		OLED_Clear();
		current_state = ADJ_YEAR;
		while(current_state <ADJ_CONFIRM){
		handle_key_event(Key_num);
		show_adjust_status();
		}
		apply_rtc_changes();
		OLED_Clear();
		}

//		for(int i=0;i<70;i++){
//		OLED_Printf(0,0,12,"  %0.2x\r\n",dec2bcd(i));
//		OLED_Refresh();
//		}
//		delay_1ms(300);
	}
}




