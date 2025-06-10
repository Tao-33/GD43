#include "HeaderFiles.h"
#include "Timer.h"
int cnt=0;

// 定时器 2 初始化函数
void TIM2_Init(uint16_t prescaler, uint16_t period) {
    // 使能定时器 2 时钟
    rcu_periph_clock_enable(RCU_TIMER2);
	rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);//选择时钟源主频为240Mhz
    // 定时器参数配置
    timer_parameter_struct timer_initpara;
    timer_deinit(TIMER2);
    timer_struct_para_init(&timer_initpara);
    timer_initpara.prescaler = prescaler; // 配置预分频器 psc
    timer_initpara.alignedmode = TIMER_COUNTER_EDGE; // 边缘对齐模式
    timer_initpara.counterdirection = TIMER_COUNTER_UP; // 向上计数
    timer_initpara.period = period; // 配置自动重载值arr
    timer_initpara.clockdivision = TIMER_CKDIV_DIV1; // 时钟分频因子
    timer_initpara.repetitioncounter = 0; // 重复计数器
    timer_init(TIMER2, &timer_initpara);
    // 使能自动重载预装载
    timer_auto_reload_shadow_enable(TIMER2);
    // 配置中断优先级
    nvic_irq_enable(TIMER2_IRQn, 0, 0);
    // 使能溢出中断
    timer_interrupt_enable(TIMER2, TIMER_INT_UP);
    // 启动定时器
    timer_enable(TIMER2);
}

// 定时器 2 溢出中断服务程序
void TIMER2_IRQHandler(void) {
    if (timer_interrupt_flag_get(TIMER2, TIMER_INT_FLAG_UP) != RESET) {
        cnt++;  
		button_ticks();
		// 清除更新中断标志
        timer_interrupt_flag_clear(TIMER2, TIMER_INT_FLAG_UP);
		//cnt++;  
				
    }
}



