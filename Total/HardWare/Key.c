#include "Key.h"
#include "HeaderFiles.h"

void Key_Init(void){
    rcu_periph_clock_enable(KEY_CLK);								// 初始化KEY总线时钟
    gpio_mode_set(KEY_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP,
                 KEY3_PIN | KEY4_PIN);		//配置GPIO模式为输入
}

uint8_t KEY_State(uint32_t port, uint16_t pin)
{
    if(gpio_input_bit_get(port, pin) == RESET)					//读取GPIO状态，如果按键被按下了
    {
        delay_1ms(20);											//延时消抖
        if(gpio_input_bit_get(port, pin) == RESET)				//再读一次GPIO，按键真的被按下了吗？
        {
            while(gpio_input_bit_get(port, pin) == RESET);		//等待按键释放
            return 1;											//返回按键状态1
        }
    }
    return 0;
}


