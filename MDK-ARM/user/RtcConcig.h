#ifndef __RTC_CONFIG_H
#define __RTC_CONFIG_H

#include "stm32f411xe.h"
#include <stdint.h>

/* ===== 对外变量 ===== */
extern volatile uint8_t rtc_1s_flag;



/* ===== 接口 ===== */
void RTC_LSE_Init(void);
void RTC_Wakeup_Init(void);

#endif
