/************************************************************
 * ��Ȩ��2025CIMC Copyright�� 
 * �ļ���Function.c
 * ����: Lingyu Meng
 * ƽ̨: 2025CIMC IHD-V04
 * �汾: Lingyu Meng     2025/2/16     V0.01    original
************************************************************/


/************************* ͷ�ļ� *************************/

#include "Function.h"

/************************* �궨�� *************************/


/************************ �������� ************************/


/************************ �������� ************************/



/************************************************************ 
 * Function :       System_Init
 * Comment  :       ���ڳ�ʼ��MCU
 * Parameter:       null
 * Return   :       null
 * Author   :       Lingyu Meng
 * Date     :       2025-02-30 V0.1 original
************************************************************/

void System_Init(void)
{
	systick_config();	// ʱ������
	
	LED_Init();			// LED��ʼ��
	
	KEY_Init();			// KEY��ʼ��
}


/************************************************************ 
 * Function :       UsrFunction
 * Comment  :       �û�������: ��������LED����
 * Parameter:       null
 * Return   :       null
 * Author   :       Lingyu Meng
 * Date     :       2025-02-30 V0.1 original
************************************************************/

void UsrFunction(void)
{
	
	while(1)
	{
		// ���Key1��LED1 ����
        if(KEY_Stat(KEY_PORT,KEY1_PIN))
        {
            LED1_ON();
			
        }
        
        // ���Key21��LED2 ����
        else if(KEY_Stat(KEY_PORT,KEY2_PIN))
        {
			LED2_ON();
            
        }
        
        // ���Key31��LED3 ����
        else if(KEY_Stat(KEY_PORT,KEY3_PIN))
        {
			LED3_ON();
            
        }
        
        // ���Key41��LED4 ����
        else if(KEY_Stat(KEY_PORT,KEY4_PIN))
        {
			LED4_ON();
            
        }
		// Ĭ��״̬��LEDȫ��
		else{
			LED_Off();
		}
	}
}


/****************************End*****************************/

