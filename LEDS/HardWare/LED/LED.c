/************************************************************
 * ��Ȩ��2025CIMC Copyright�� 
 * �ļ���led.c
 * ����: Lingyu Meng
 * ƽ̨: 2025CIMC IHD-V04
 * �汾: Lingyu Meng     2025/2/16     V0.01    original
************************************************************/

/************************* ͷ�ļ� *************************/
#include "gd32f4xx.h"                   // Device header
#include "Headerfiles.h"
#include "LED.h"

/************************ ȫ�ֱ������� ************************/


/************************************************************ 
 * Function :       LED_Init
 * Comment  :       ���ڳ�ʼ��LED�˿�
 * Parameter:       null
 * Return   :       null
 * Author   :       Lingyu Meng
 * Date     :       2025-02-30 V0.1 original
************************************************************/

void LED_Init(void)
{
	rcu_periph_clock_enable(RCU_GPIOE);    // ��ʼ��GPIO_A����ʱ��
	
	//��ʼ��LED1�˿�
	gpio_mode_set(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_2);   			// GPIOģʽ����Ϊ���
    gpio_output_options_set(GPIOE, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_2);   // �����������
	gpio_bit_reset(GPIOE, GPIO_PIN_2);  											// ���ų�ʼ��ƽΪ�͵�ƽ
	gpio_mode_set(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_3);   			// GPIOģʽ����Ϊ���
    gpio_output_options_set(GPIOE, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_3);   // �����������
	gpio_bit_reset(GPIOE, GPIO_PIN_3);  											// ���ų�ʼ��ƽΪ�͵�ƽ
	//��ʼ��LED2~4�˿ڣ�������ʼ���˿ڣ�
//	gpio_mode_set(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);   			// GPIOģʽ����Ϊ���
//    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);     // �����������
//	gpio_bit_reset(GPIOA, GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);  										     	// ���ų�ʼ��ƽΪ�͵�ƽ
	
}

void LED_Flash(void)
{
	gpio_bit_set(GPIOE,GPIO_PIN_2);
	gpio_bit_reset(GPIOE, GPIO_PIN_3);
	delay_1ms(50);
	gpio_bit_set(GPIOE,GPIO_PIN_3);
	gpio_bit_reset(GPIOE, GPIO_PIN_2);
	delay_1ms(50);
}

/****************************End*****************************/

