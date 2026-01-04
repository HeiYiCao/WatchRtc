// SpiConfig.h
#ifndef __SPI_CONFIG_H
#define __SPI_CONFIG_H

#include "stm32f4xx.h"

#define LCD_CS_LOW()   (GPIOA->BSRR = (1 << (3 + 16)))
#define LCD_CS_HIGH()  (GPIOA->BSRR = (1 << 3))
#define LCD_DC_LOW()   (GPIOA->BSRR = (1 << (2 + 16)))
#define LCD_DC_HIGH()  (GPIOA->BSRR = (1 << 2))
#define LCD_RST_LOW()  (GPIOA->BSRR = (1 << (6 + 16)))
#define LCD_RST_HIGH() (GPIOA->BSRR = (1 << 6))

void SystemClock_Config(void);
void SysTick_Init(void);
void delay_ms(uint32_t ms);
void GPIO_Init_All(void);
void SPI1_Init(void);
void SPI1_Write(uint8_t data);
void LCD_WriteCmd(uint8_t cmd);
void LCD_WriteData(uint8_t data);
void LCD_Init(void);
void LCD_Fill(uint16_t color);

#endif