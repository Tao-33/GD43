#include "HeaderFiles.h"
#include "Function.h"



void System_Init(void)
{
	systick_config();     // 时钟配置
	Led_Init();
	Key_Init();
	EXTI_Pin_Init();
	Serial_Init();
	OLED_Init();
}

void UsrFunction(void)
{

	printf("Hello CIMC");
	while(1)
	{
		/*按键和LED测试
		if(KEY_State(GPIOE,KEY3_PIN)==1){
		Led_Flash();		
		}
		if(KEY_State(GPIOE,KEY3_PIN)==1){
		Led_OFF();		
		}*/
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
	}
}




