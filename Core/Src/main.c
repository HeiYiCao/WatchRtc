#include "stm32f4xx.h"      // STM32F4 系列寄存器定义
#include "SpiConfig.h"     // SPI1 + LCD(ST7789) 相关配置
#include "I2cConfig.h"     // I2C1 配置（触摸）
#include "lvgl.h"          // LVGL 图形库核心头文件
#include "gui_guider.h"    // GuiGuider 自动生成的 UI 结构与函数
#include "events_init.h"   // GuiGuider 生成的事件初始化函数
#include "custom.h"        // Lvgl自定义代码
#include "RtcConcig.h"     // RTC 初始化与配置（LSE / Wakeup）

volatile uint32_t uwTick = 0;

// GuiGuider 总结构体
lv_ui guider_ui;


//LVGL 刷新回调函数
static void my_flush_cb(lv_disp_drv_t *disp_drv,
                        const lv_area_t *area,
                        lv_color_t *color_p)
{
    // 刷新区域左上角坐标
    int32_t x1 = area->x1;
    int32_t y1 = area->y1;

    // 刷新区域右下角坐标
    int32_t x2 = area->x2;
    int32_t y2 = area->y2;

    //设置列地址X
    LCD_WriteCmd(0x2A);                 // CASET
    LCD_WriteData(x1 >> 8);             // 起始列高 8 位
    LCD_WriteData(x1 & 0xFF);           // 起始列低 8 位
    LCD_WriteData(x2 >> 8);             // 结束列高 8 位
    LCD_WriteData(x2 & 0xFF);            // 结束列低 8 位

    //设置行地址Y
    LCD_WriteCmd(0x2B);                 // RASET
    LCD_WriteData(y1 >> 8);             // 起始行高 8 位
    LCD_WriteData(y1 & 0xFF);            // 起始行低 8 位
    LCD_WriteData(y2 >> 8);             // 结束行高 8 位
    LCD_WriteData(y2 & 0xFF);            // 结束行低 8 位

    //写入显存
    LCD_WriteCmd(0x2C);                 // 写显存
    LCD_DC_HIGH();                      // 数据模式
    LCD_CS_LOW();                       // 选中 LCD

    // 计算需要写入的像素点数量
    uint32_t size = (x2 - x1 + 1) * (y2 - y1 + 1);

    // LVGL 的颜色缓冲指针 RGB565
    uint16_t *buf = (uint16_t *)color_p;

    // 通过 SPI 逐像素发送 高字节 + 低字节
    for (uint32_t i = 0; i < size; i++)
    {
        SPI1_Write(buf[i] >> 8);        // 发送颜色高字节
        SPI1_Write(buf[i] & 0xFF);      // 发送颜色低字节
    }

    LCD_CS_HIGH();                      // 释放 LCD 片选

    // 通知 LVGL 本次刷新完成 
    lv_disp_flush_ready(disp_drv);
}

//LVGL 显示驱动注册
static void lv_port_disp_init(void)
{
    // LVGL 绘图缓冲区结构体
    static lv_disp_draw_buf_t draw_buf;

    // 像素缓冲区
    static lv_color_t buf[240 * 10];

    // 初始化绘图缓冲区
    lv_disp_draw_buf_init(&draw_buf, buf, NULL, 240 * 10);

    // 显示驱动结构体
    static lv_disp_drv_t disp_drv;

    // 初始化为默认值
    lv_disp_drv_init(&disp_drv);

    // 屏幕横向分辨率
    disp_drv.hor_res = 240;

    // 屏幕纵向分辨率
    disp_drv.ver_res = 320;

    // 设置刷新回调函数
    disp_drv.flush_cb = my_flush_cb;

    // 设置绘图缓冲区
    disp_drv.draw_buf = &draw_buf;

    // 注册显示驱动
    lv_disp_drv_register(&disp_drv);
}

int main(void)
{
    // ---------------- 系统基础初始化 ----------------
    SystemClock_Config();   // 系统时钟配置（25MHz HSE）
    SysTick_Init();         // SysTick 1ms 中断（delay + LVGL tick）

    // ---------------- 外设初始化 ----------------
    GPIO_Init_All();        // LCD / SPI / 控制引脚 GPIO 初始化
    SPI1_Init();            // SPI1 初始化（约 6.25MHz）
    LCD_Init();             // ST7789 屏幕初始化
    I2C1_Init();            // I2C1 初始化（触摸 / RTC）

    // ---------------- LVGL 初始化 ----------------
    lv_init();              // LVGL 内核初始化
    lv_port_disp_init();    // 注册显示驱动
    lv_port_indev_init();   // 注册输入设备（触摸）

    // ---------------- GuiGuider UI ----------------
    setup_ui(&guider_ui);   // 创建所有界面与控件
    events_init(&guider_ui); // 绑定事件回调

    // ---------------- RTC ----------------
    RTC_LSE_Init();         // LSE 32.768kHz 初始化
    RTC_Wakeup_Init();      // RTC 唤醒中断配置

    // ---------------- 启动指示 LED（PC13）----------------
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; // 使能 GPIOC 时钟
    GPIOC->MODER |= (1 << (13 * 2));    // PC13 配置为输出
    GPIOC->ODR &= ~(1 << 13);           // LED 亮
    delay_ms(300);                      // 延时 300ms
    GPIOC->ODR |= (1 << 13);            // LED 灭

    // ---------------- 主循环 ----------------
    while (1)
    {
        lv_timer_handler();  // LVGL 任务调度（必须周期调用）
        delay_ms(5);         // 5ms 一次，≈200Hz
    }
}

//SysTick 中断服务函数
void SysTick_Handler(void)
{
    uwTick++;               // 系统毫秒计数
    lv_tick_inc(1);         // 告诉 LVGL 过去了 1ms
}
