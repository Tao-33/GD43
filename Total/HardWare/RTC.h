
#ifndef __RTC_H
#define __RTC_H
#include "HeaderFiles.h"

// 调整状态枚举
typedef enum {
    ADJ_YEAR,
    ADJ_MONTH,
    ADJ_DAY,
    ADJ_HOUR,
    ADJ_MINUTE,
    ADJ_SECOND,
    ADJ_CONFIRM
} AdjustState;
extern AdjustState current_state;



void RTC_Init(void);	// RTC初始化
void rtc_setup(void);	// RTC时钟设置
void rtc_show_time(void);	// RTC时间
void rtc_show_alarm(void);	// RTC闹钟
uint8_t usart_input_threshold(uint32_t value);  // 用作输入值有效校验
void rtc_pre_config(void);
// 限制数值范围[min,max]
int32_t CLAMP(int32_t value, int32_t min, int32_t max) ;

// 循环数值范围[min,max]
int32_t CYCLIC(int32_t value, int32_t min, int32_t max) ;

// 获取当月最大天数
uint8_t get_max_day(uint16_t year, uint8_t month) ;
// 应用RTC修改
void apply_rtc_changes(void) ;
// 调整数值
void adjust_value(int8_t delta) ;
// 处理按键事件
void handle_key_event(uint8_t key) ;
// 显示当前调整状态
void show_adjust_status(void);

void KEY_Adjust(void);
#endif
