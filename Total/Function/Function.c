#include "HeaderFiles.h"
#include "Function.h"



void System_Init(void)
{
	systick_config();     // ʱ������
	Led_Init();
	Key_Init();
	EXTI_Pin_Init();
	Serial_Init();
}

void UsrFunction(void)
{

	printf("Hello CIMC");
	while(1)
	{
		if(KEY_State(GPIOE,KEY3_PIN)==1){
		Led_Flash();		
		}
		if(KEY_State(GPIOE,KEY3_PIN)==1){
		Led_OFF();		
		}
	}
}




