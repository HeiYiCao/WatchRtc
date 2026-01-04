/*
* Copyright 2023 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/


/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include "stm32f4xx.h"

#include "lvgl.h"
#include "custom.h"
uint8_t g_hour = 12;
uint8_t g_min  = 0;
uint8_t g_sec  = 0;
lv_timer_t *clock_timer = NULL;






/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/





void custom_init(lv_ui *ui)
{

}

//RTC设置时间
void RTC_SetTime(uint8_t hour, uint8_t min, uint8_t sec)
{
    //解锁写保护
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;

    //进入初始化模式
    RTC->ISR |= RTC_ISR_INIT;
    while((RTC->ISR & RTC_ISR_INITF) == 0);

    //设置时间
    RTC->TR =
        ((hour / 10) << 20) | ((hour % 10) << 16) |
        ((min  / 10) << 12) | ((min  % 10) << 8 ) |
        ((sec  / 10) << 4 ) | (sec  % 10);

    //退出初始化模式
    RTC->ISR &= ~RTC_ISR_INIT;

    //重新上锁
    RTC->WPR = 0xFF;
}




