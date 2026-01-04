#include "RtcConcig.h"                 // RTC 配置相关头文件
#include "custom.h"                   // 用户自定义变量（g_hour / g_min / g_sec 等）

volatile uint8_t rtc_1s_flag = 0;     // RTC 每 1 秒中断标志位

// 将 BCD 格式转换为十进制整数
static uint8_t BCD2BIN(uint8_t bcd)   
{
    return ((bcd >> 4) * 10) + (bcd & 0x0F); // 高 4 位 *10 + 低 4 位
}


// RTC + LSE 初始化
void RTC_LSE_Init(void)
{
    RCC->APB1ENR |= (1 << 28);         // 使能 PWR 外设时钟
    PWR->CR |= (1 << 8);               // 允许访问备份域

    if (RTC->BKP0R == 0xA5A5)          // 判断 RTC 是否已经初始化过
        return;                        // 已初始化则直接退出

    RCC->BDCR |= (1 << 0);             // 启动 LSE 振荡器
    while (!(RCC->BDCR & (1 << 1)));   // 等待 LSE 稳定

    RCC->BDCR &= ~(3 << 8);            // 清 RTC 时钟源选择位
    RCC->BDCR |=  (1 << 8);            // 选择 LSE 作为 RTC 时钟源
    RCC->BDCR |=  (1 << 15);           // 使能 RTC 时钟

    RTC->WPR = 0xCA;                   // 解锁 RTC 写保护 1
    RTC->WPR = 0x53;                   // 解锁 RTC 写保护 2

    RTC->ISR |= (1 << 7);              // 进入 RTC 初始化模式 
    while (!(RTC->ISR & (1 << 6)));    // 等待初始化模式就绪 

    RTC->PRER = (127 << 16) | 255;     // 预分频：32768Hz -> 1Hz

    RTC->CR &= ~(1 << 6);              // 设置为 24 小时制

    RTC->TR = 0x00000000;              // 初始时间设置为 00:00:00

    RTC->DR = (0x2 << 20) |             // 年份：25（BCD）
              (0x1 << 16) |             // 月份：1 月
              (0x0 << 8)  |             // 日期十位
              (0x1 << 0);               // 日期个位（1 号）

    RTC->ISR &= ~(1 << 7);             // 退出 RTC 初始化模式

    RTC->WPR = 0xFF;                   // 重新锁定 RTC 写保护

    RTC->BKP0R = 0xA5A5;               // 写备份寄存器，标记 RTC 已初始化
}


// RTC Wakeup 定时器初始化 精准1s
void RTC_Wakeup_Init(void)
{
    RTC->WPR = 0xCA;                   // 解锁 RTC 写保护 1
    RTC->WPR = 0x53;                   // 解锁 RTC 写保护 2

    RTC->CR &= ~(1 << 10);             // 关闭 Wakeup 定时器
    while (!(RTC->ISR & (1 << 2)));    // 等待 Wakeup 可配置

    RTC->WUTR = 0;                     // Wakeup 自动重载值
    RTC->CR &= ~(7 << 0);              // 清 Wakeup 时钟选择位
    RTC->CR |=  (4 << 0);              // 选择 ck_spre 1hz

    RTC->ISR &= ~(1 << 10);            // 清 Wakeup 中断标志

    RTC->CR |= (1 << 14);              // 使能 Wakeup 中断
    RTC->CR |= (1 << 10);              // 使能 Wakeup 定时器

    RTC->WPR = 0xFF;                   // 重新锁定 RTC 写保护

    EXTI->IMR  |= (1 << 22);           // 使能 EXTI Line22
    EXTI->RTSR |= (1 << 22);           // 配置为上升沿触发

    NVIC_EnableIRQ(RTC_WKUP_IRQn);     // 使能 RTC Wakeup 中断向量
}

// RTC Wakeup 中断服务函数
void RTC_WKUP_IRQHandler(void)
{
    if (RTC->ISR & (1 << 10))          // 判断是否为 Wakeup 中断
    {
        RTC->ISR &= ~(1 << 10);        // 清 RTC Wakeup 中断标志
        EXTI->PR = (1 << 22);          // 清 EXTI Line22 中断标志

        rtc_1s_flag = 1;               // 置位 1 秒标志，供主循环使用

        uint32_t tr = RTC->TR;         // 读取 RTC 时间寄存器

        g_hour = BCD2BIN((tr >> 16) & 0x3F); // 解析小时
        g_min  = BCD2BIN((tr >> 8)  & 0x7F); // 解析分钟
        g_sec  = BCD2BIN(tr & 0x7F);         // 解析秒
    }
}
