#ifndef __I2C_CONFIG_H
#define __I2C_CONFIG_H

#include "stm32f4xx.h"
#include "lvgl.h"

/* ================= 触摸芯片 CST816T ================= */

#define CST816T_ADDR      0x15    // 7-bit I2C 地址

/* ================= I2C1 引脚 ================= */
// PB6 -> SCL
// PB7 -> SDA
#define TP_I2C            I2C1

/* ================= RST / INT ================= */
#define TP_RST_PORT       GPIOA
#define TP_RST_PIN        0       // PA0

#define TP_INT_PORT       GPIOB
#define TP_INT_PIN        5       // PB5

/* ================= 触摸数据结构 ================= */
typedef struct
{
    uint16_t x;
    uint16_t y;
    uint8_t  pressed;
} TouchData_t;

/* ================= 调试变量（可选） ================= */
extern uint8_t  tp_pressed;
extern uint16_t tp_x;
extern uint16_t tp_y;

/* ================= 接口函数 ================= */
void I2C1_Init(void);
void TP_Reset(void);

uint8_t TP_ReadOneByte(uint8_t reg, uint8_t *data);
uint8_t TP_ReadBytes(uint8_t reg, uint8_t *buf, uint8_t len);
uint8_t TP_GetTouch(TouchData_t *touch);

/* LVGL 输入设备初始化 */
void lv_port_indev_init(void);

#endif
