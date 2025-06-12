/************************************************************
 * 版权：2025CIMC Copyright。 
 * 文件：RTC.c
 * 作者: Qiao Qin @ GigaDevice
 * 平台: 2025CIMC IHD-V04
 * 版本: Qiao Qin     2025/4/20     V0.01    original
************************************************************/


#include "RTC.h"
#include "HeaderFiles.h"

#define RTC_CLOCK_SOURCE_LXTAL		// 配置RTC时钟源，使用外部32.768KHz
#define BKP_VALUE    0x32F0



rtc_parameter_struct   rtc_initpara;//RTC初始化结构体
rtc_alarm_struct  rtc_alarm;//闹钟配置结构体
__IO uint32_t prescaler_a = 0, prescaler_s = 0;//预分频器
uint32_t RTCSRC_FLAG = 0;



AdjustState current_state = ADJ_YEAR;

/*!
    \brief      main function
    \param[in]  none
    \param[out] none
    \retval     none
*/
void RTC_Init(void)
{
    printf("\n\r  ****************** RTC calendar demo ******************\n\r");

    /* enable PMU clock */
    rcu_periph_clock_enable(RCU_PMU);//使能电源管理单元
    /* enable the access of the RTC registers */
    pmu_backup_write_enable();//解锁备份域写保护
	
    rtc_pre_config();//RTC预配置
    /* get RTC clock entry selection */
    RTCSRC_FLAG = GET_BITS(RCU_BDCTL, 8, 9);

    /* check if RTC has aready been configured */
	//判断是否需要重新配置RTC
    if((BKP_VALUE != RTC_BKP0) || (0x00 == RTCSRC_FLAG)){
        /* backup data register value is not correct or not yet programmed
        or RTC clock source is not configured (when the first time the program 
        is executed or data in RCU_BDCTL is lost due to Vbat feeding) */
        rtc_setup();//完整的RTC初始化
    }else{
        /* detect the reset source */
        if (RESET != rcu_flag_get(RCU_FLAG_PORRST)){
            printf("power on reset occurred....\n\r");
        }else if (RESET != rcu_flag_get(RCU_FLAG_EPRST)){
            printf("external reset occurred....\n\r");
        }
        printf("no need to configure RTC....\n\r");

        rtc_show_time();
    }
    rcu_all_reset_flag_clear();
}

/*!
    \brief      RTC configuration function
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rtc_pre_config(void)
{
    #if defined (RTC_CLOCK_SOURCE_IRC32K)
          rcu_osci_on(RCU_IRC32K);
          rcu_osci_stab_wait(RCU_IRC32K);
          rcu_rtc_clock_config(RCU_RTCSRC_IRC32K);

          prescaler_s = 0x13F;
          prescaler_a = 0x63;
    #elif defined (RTC_CLOCK_SOURCE_LXTAL)
          rcu_osci_on(RCU_LXTAL);//开启外部32.768KHz晶振
          rcu_osci_stab_wait(RCU_LXTAL);//等待晶振稳定
          rcu_rtc_clock_config(RCU_RTCSRC_LXTAL);//配置时钟源

          prescaler_s = 0xFF;//同步分频255+1
          prescaler_a = 0x7F;//异步分频127+1
    #else
    #error RTC clock source should be defined.
    #endif /* RTC_CLOCK_SOURCE_IRC32K */

    rcu_periph_clock_enable(RCU_RTC);//使能
    rtc_register_sync_wait();//等待RTC寄存器同步完成
}

/*!
    \brief      use hyperterminal to setup RTC time and alarm
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rtc_setup(void)
{
    /* setup RTC time value */
	uint32_t tmp_year = 0xFF, tmp_month = 0xFF, tmp_day = 0xFF;
    uint32_t tmp_hh = 0xFF, tmp_mm = 0xFF, tmp_ss = 0xFF;

    rtc_initpara.factor_asyn = prescaler_a;//用之前算的分频值
    rtc_initpara.factor_syn = prescaler_s;
    rtc_initpara.year = 0x16;//默认年份2016
    rtc_initpara.day_of_week = RTC_SATURDAY;//默认周六
    rtc_initpara.month = RTC_APR;//默认四月
    rtc_initpara.date = 0x30;//30日
    rtc_initpara.display_format = RTC_24HOUR;//24小时制
    rtc_initpara.am_pm = RTC_AM;

    /* current time input */
    printf("=======Configure RTC Time========\n\r");
	printf("  please set the last two digits of current year:\n\r");
    while(tmp_year == 0xFF) {
        tmp_year = usart_input_threshold(99);//限制输入
        rtc_initpara.year = tmp_year;
    }
    printf("  20%0.2x\n\r", tmp_year);

    printf("  please input month:\n\r");
    while(tmp_month == 0xFF) {
        tmp_month = usart_input_threshold(12);
        rtc_initpara.month = tmp_month;
    }
    printf("  %0.2x\n\r", tmp_month);

    printf("  please input day:\n\r");
    while(tmp_day == 0xFF) {
        tmp_day = usart_input_threshold(31);
        rtc_initpara.date = tmp_day;
    }
    printf("  %0.2x\n\r", tmp_day);
		
	
    printf("  please input hour:\n\r");
    while (0xFF == tmp_hh){
        tmp_hh = usart_input_threshold(23);
        rtc_initpara.hour = tmp_hh;
    }
    printf("  %0.2x\n\r", tmp_hh);

    printf("  please input minute:\n\r");
    while (0xFF == tmp_mm){
        tmp_mm = usart_input_threshold(59);
        rtc_initpara.minute = tmp_mm;
    }
    printf("  %0.2x\n\r", tmp_mm);

    printf("  please input second:\n\r");
    while (0xFF == tmp_ss){
        tmp_ss = usart_input_threshold(59);
        rtc_initpara.second = tmp_ss;
    }
    printf("  %0.2x\n\r", tmp_ss);

    /* RTC current time configuration */
    if(ERROR == rtc_init(&rtc_initpara)){
        printf("\n\r** RTC time configuration failed! **\n\r");
    }else{
        printf("\n\r** RTC time configuration success! **\n\r");
        rtc_show_time();
        RTC_BKP0 = BKP_VALUE;
    }
/*
//     setup RTC alarm 
//    tmp_hh = 0xFF;
//    tmp_mm = 0xFF;
//    tmp_ss = 0xFF;

//    rtc_alarm_disable(RTC_ALARM0);
//    printf("=======Input Alarm Value=======\n\r");
//    rtc_alarm.alarm_mask = RTC_ALARM_DATE_MASK|RTC_ALARM_HOUR_MASK|RTC_ALARM_MINUTE_MASK;
//    rtc_alarm.weekday_or_date = RTC_ALARM_DATE_SELECTED;
//    rtc_alarm.alarm_day = 0x31;
//    rtc_alarm.am_pm = RTC_AM;

//     RTC alarm input 
//    printf("  please input Alarm Hour:\n\r");
//    while (0xFF == tmp_hh){
//        tmp_hh = usart_input_threshold(23);
//        rtc_alarm.alarm_hour = tmp_hh;
//    }
//    printf("  %0.2x\n\r", tmp_hh);

//    printf("  Please Input Alarm Minute:\n\r");
//    while (0xFF == tmp_mm){
//        tmp_mm = usart_input_threshold(59);
//        rtc_alarm.alarm_minute = tmp_mm;
//    }
//    printf("  %0.2x\n\r", tmp_mm);

//    printf("  Please Input Alarm Second:\n\r");
//    while (0xFF == tmp_ss){
//        tmp_ss = usart_input_threshold(59);
//        rtc_alarm.alarm_second = tmp_ss;
//    }
//    printf("  %0.2x", tmp_ss);

//     RTC alarm configuration 
//    rtc_alarm_config(RTC_ALARM0,&rtc_alarm);
//    printf("\n\r** RTC Set Alarm Success!  **\n\r");
//    rtc_show_alarm();

//    rtc_interrupt_enable(RTC_INT_ALARM0);
//    rtc_alarm_enable(RTC_ALARM0);
*/
}

// 输入范围：0-99（超出范围需自行处理）
uint8_t dec2bcd(uint8_t decimal) {
    return ((decimal / 10) << 4) | (decimal % 10);
}


/*!
    \brief      display the current time
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rtc_show_time(void)
{
//    uint32_t time_subsecond = 0;  这可以处理亚秒级显示
//    uint8_t subsecond_ss = 0,subsecond_ts = 0,subsecond_hs = 0;

    rtc_current_time_get(&rtc_initpara);//调用库函数从硬件寄存器读取时间
		//这个函数会更新rtc_initpara的值
    /* 亚秒计算逻辑get the subsecond value of current time, and convert it into fractional format */
//    time_subsecond = rtc_subsecond_get();
//    subsecond_ss=(1000-(time_subsecond*1000+1000)/400)/100;
//    subsecond_ts=(1000-(time_subsecond*1000+1000)/400)%100/10;
//    subsecond_hs=(1000-(time_subsecond*1000+1000)/400)%10;
	OLED_Printf(0,0,12,"20%0.2x-%0.2x-%0.2x", 
           rtc_initpara.year, rtc_initpara.month, rtc_initpara.date);
	OLED_Printf(0,13,12,"  %0.2x:%0.2x:%0.2x \r\n",
           rtc_initpara.hour, rtc_initpara.minute, rtc_initpara.second);
	OLED_Refresh();
    printf("\r\nCurrent time: 20%0.2x-%0.2x-%0.2x", 
           rtc_initpara.year, rtc_initpara.month, rtc_initpara.date);

    printf(" : %0.2x:%0.2x:%0.2x \r\n", 
           rtc_initpara.hour, rtc_initpara.minute, rtc_initpara.second);
}

void rtc_show_EXchange_time(void)
{
    rtc_current_time_get(&rtc_initpara);//调用库函数从硬件寄存器读取时间
	OLED_Printf(0,0,12,"20%02d-%02d-%02d", 
           rtc_initpara.year, rtc_initpara.month, rtc_initpara.date);
	OLED_Printf(0,13,12,"  %02d:%02d:%02d \r\n",
           rtc_initpara.hour, rtc_initpara.minute, rtc_initpara.second);
		OLED_Refresh();
    printf("\r\nCurrent time: 20%02d-%02d-%02d", 
           rtc_initpara.year, rtc_initpara.month, rtc_initpara.date);

    printf(" : %02d:%02d:%02d \r\n", 
           rtc_initpara.hour, rtc_initpara.minute, rtc_initpara.second);
	OLED_Refresh();
}

/*!
    \brief      display the alram value
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rtc_show_alarm(void)
{
    rtc_alarm_get(RTC_ALARM0,&rtc_alarm);
    printf("The alarm: %0.2x:%0.2x:%0.2x \n\r", rtc_alarm.alarm_hour, rtc_alarm.alarm_minute,
           rtc_alarm.alarm_second);
}

/*!
    \brief      get the input character string and check if it is valid
    \param[in]  none
    \param[out] none
    \retval     input value in BCD mode
*/



uint8_t usart_input_threshold(uint32_t value) {
    uint8_t tmp[2] = {0};
	int i=0;
	while(i < 2) {
        if(data_ready) {
            tmp[i] = data_recv;
            data_ready = 0;
            
            if(tmp[i] >= 0x30 && tmp[i] <= 0x39) {
					i++; // 仅接受数字
			}
		}       
    }
	//防止超限
    uint8_t decimal = (tmp[0]-0x30)*10 + (tmp[1]-0x30);
    if(decimal > value) {
        printf("\n\rInput exceed %d\n\r", value);
        return 0xFF;
    }
    return ((tmp[0]-0x30)<<4) | (tmp[1]-0x30); // 正确BCD编码
}


// 限制数值范围[min,max]
uint8_t CLAMP(uint8_t value, uint8_t min, int32_t max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

// 循环数值范围[min,max]
uint8_t CYCLIC(uint8_t value, uint8_t min, uint8_t max) {
    if (value < min) return max;
    if (value > max) return min;
    return value;
}


// 获取当月最大天数
uint8_t get_max_day(uint16_t year, uint8_t month) {
    const uint8_t days[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if(month == 2 && ((year%4==0 && year%100!=0) || year%400==0))
        return 29;
    return days[month-1];
}


//// 应用RTC修改
//void apply_rtc_changes(void) {
//    /* enable PMU clock */
//    rcu_periph_clock_enable(RCU_PMU);//使能电源管理单元
//    /* enable the access of the RTC registers */
//    pmu_backup_write_enable();//解锁备份域写保护
//    
//    /* 配置RTC */
//	rtc_current_time_get(&rtc_initpara);//调用库函数从硬件寄存器读取时间
//    if(ERROR == rtc_init(&rtc_initpara)) {
//        OLED_Printf(0,0,16,"RTC config failed!\n");
//    } else {
////        OLED_Printf(0,0,12," 20%02d-%02d-%02d %02d:%02d:%02d\n", 
////              rtc_initpara.year, rtc_initpara.month, rtc_initpara.date,
////              rtc_initpara.hour, rtc_initpara.minute, rtc_initpara.second);
//        rtc_show_time();
//        RTC_BKP0 = BKP_VALUE;
//    }
////	OLED_Refresh();
//}



void apply_rtc_changes(void) {
//		rtc_initpara.factor_asyn = prescaler_a;//用之前算的分频值
//		rtc_initpara.factor_syn = prescaler_s;
//		rtc_initpara.year = 0x16;//默认年份2016
//		rtc_initpara.day_of_week = RTC_SATURDAY;//默认周六
//		rtc_initpara.month = RTC_APR;//默认四月
//		rtc_initpara.date = 0x30;//30日
//		rtc_initpara.display_format = RTC_24HOUR;//24小时制
//		rtc_initpara.am_pm = RTC_AM;
        
        /* 从硬件读取当前时间 */
   //     rtc_current_time_get(&rtc_initpara);

        if(ERROR == rtc_init(&rtc_initpara)) {
            OLED_Printf(0,0,16,"RTC config failed!\n");
			OLED_Refresh();
        } else {
            rtc_show_time();
            RTC_BKP0 = BKP_VALUE; // 标记配置完成
        }
       if(ERROR == rtc_init(&rtc_initpara)){
			printf("\n\r** RTC time configuration failed! **\n\r");
		}else{
			printf("\n\r** RTC time configuration success! **\n\r");
			//rtc_show_time();
			RTC_BKP0 = BKP_VALUE;
		}
}

uint8_t bcd_to_decimal(uint8_t bcd) {
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}


// 调整数值
void adjust_value(int8_t delta) {
    switch(current_state) {
        case ADJ_YEAR:
            rtc_initpara.year = dec2bcd(CLAMP(bcd_to_decimal(rtc_initpara.year) + delta, 0, 99));
            break;
            
        case ADJ_MONTH:
            rtc_initpara.month = dec2bcd(CYCLIC(bcd_to_decimal(rtc_initpara.month) + delta, 1, 12));
            break;
            
        case ADJ_DAY: {
            uint8_t max_day = get_max_day(2000 + bcd_to_decimal(rtc_initpara.year), bcd_to_decimal(rtc_initpara.month));
            rtc_initpara.date = dec2bcd(CLAMP(bcd_to_decimal(rtc_initpara.date) + delta, 1, max_day));
            break;
        }
            
        case ADJ_HOUR:
            rtc_initpara.hour = dec2bcd(CYCLIC(bcd_to_decimal(rtc_initpara.hour) + delta, 0, 23));
            break;
            
        case ADJ_MINUTE:
            rtc_initpara.minute =dec2bcd( CYCLIC(bcd_to_decimal(rtc_initpara.minute) + delta, 0, 59));
            break;
            
        case ADJ_SECOND:
            rtc_initpara.second = dec2bcd(CYCLIC(bcd_to_decimal(rtc_initpara.second) + delta, 0, 59));
            break;
            
        case ADJ_CONFIRM:
            apply_rtc_changes();
            break;
    }
}

// 处理按键事件
void handle_key_event(uint8_t key) {
    switch(key) {
        case 1: // 切换调整项
			 if(current_state < ADJ_CONFIRM) {
                current_state = (AdjustState)(current_state + 1);
                if(current_state == ADJ_CONFIRM) {
                    //apply_rtc_changes(); // 到达确认状态时保存配置
                }
            } else {
                current_state = ADJ_YEAR; // 完成配置后回到初始状态
            }
            Key_num=0;
            break;
		
			case 2: // 数值增加
            adjust_value(1);
			Key_num=0;
            break;
            
			case 3: // 数值减少
            adjust_value(-1);
			Key_num=0;
            break;
    }
}

//// 显示当前调整状态
//void show_adjust_status(void) {
//    const char *items[] = {"Year","Month","Day","Hour","Minute","Second","Confirm"};
//    OLED_Printf(0,0,16,"\n[%s] 20%02d-%02d-%02d %02d:%02d:%02d\n", 
//          items[current_state],
//          rtc_initpara.year, rtc_initpara.month, rtc_initpara.date,
//          rtc_initpara.hour, rtc_initpara.minute, rtc_initpara.second);
//}

// 显示当前调整状态
void show_adjust_status(void) {
	
    OLED_Printf(0,0,12," 20%0.2x-%0.2x-%0.2x %0.2x:%0.2x:%0.2x\n", 
          rtc_initpara.year, rtc_initpara.month, rtc_initpara.date,
          rtc_initpara.hour, rtc_initpara.minute, rtc_initpara.second);
	OLED_Printf(0,12,12,"%d",current_state);
	OLED_Refresh();
}



