// SpiConfig.c
#include "stm32f4xx.h"
#include "SpiConfig.h"

extern volatile uint32_t uwTick;

/* 系统时钟配置25MHz HSE（不超频） */
void SystemClock_Config(void)
{
    RCC->CR |= RCC_CR_HSEON;
    while (!(RCC->CR & RCC_CR_HSERDY));

    RCC->CFGR = 0;                                  // 清零分频设置
    RCC->CFGR |= RCC_CFGR_SW_HSE;                   // 系统时钟源选择 HSE
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSE);
}

/* SysTick 初始化：25MHz 下 1ms 中断 */
void SysTick_Init(void)
{
    SysTick->LOAD = 25000000UL / 1000 - 1;          // 1ms
    SysTick->VAL = 0;
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |
                    SysTick_CTRL_TICKINT_Msk |
                    SysTick_CTRL_ENABLE_Msk;
}



void delay_ms(uint32_t ms)
{
    uint32_t start = uwTick;
    while ((uwTick - start) < ms);
}

void GPIO_Init_All(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    GPIOA->MODER &= ~((3<<(2*2)) | (3<<(3*2)) | (3<<(6*2)));
    GPIOA->MODER |=  ((1<<(2*2)) | (1<<(3*2)) | (1<<(6*2)));
    GPIOA->OSPEEDR |= ((3<<(2*2)) | (3<<(3*2)) | (3<<(6*2)));  // 高速
    GPIOA->OTYPER &= ~((1<<2) | (1<<3) | (1<<6));
    GPIOA->PUPDR &= ~((3<<(2*2)) | (3<<(3*2)) | (3<<(6*2)));

    GPIOA->MODER &= ~((3<<(5*2)) | (3<<(7*2)));
    GPIOA->MODER |=  ((2<<(5*2)) | (2<<(7*2)));
    GPIOA->OSPEEDR |= ((3<<(5*2)) | (3<<(7*2)));
    GPIOA->AFR[0] &= ~((0xF<<(5*4)) | (0xF<<(7*4)));
    GPIOA->AFR[0] |=  ((5<<(5*4)) | (5<<(7*4)));

    LCD_CS_HIGH();
    LCD_DC_HIGH();
    LCD_RST_HIGH();
}

/* SPI1 初始化*/
void SPI1_Init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

    SPI1->CR1 = 0;
    SPI1->CR1 |= SPI_CR1_MSTR;
    SPI1->CR1 |= (0 << SPI_CR1_BR_Pos);     // /4 → 6.25MHz（手册内最快）
    SPI1->CR1 |= SPI_CR1_SSM | SPI_CR1_SSI;
    SPI1->CR1 &= ~SPI_CR1_DFF;
    SPI1->CR1 &= ~SPI_CR1_LSBFIRST;
    SPI1->CR1 &= ~SPI_CR1_CPOL;
    SPI1->CR1 &= ~SPI_CR1_CPHA;
    SPI1->CR1 |= SPI_CR1_SPE;
}

void SPI1_Write(uint8_t data)
{
    while (!(SPI1->SR & SPI_SR_TXE));
    *(uint8_t*)&SPI1->DR = data;
    while (!(SPI1->SR & SPI_SR_TXE));
    while (SPI1->SR & SPI_SR_BSY);
}

void LCD_WriteCmd(uint8_t cmd)
{
    LCD_DC_LOW();
    LCD_CS_LOW();
    SPI1_Write(cmd);
    LCD_CS_HIGH();
}

void LCD_WriteData(uint8_t data)
{
    LCD_DC_HIGH();
    LCD_CS_LOW();
    SPI1_Write(data);
    LCD_CS_HIGH();
}

void LCD_Init(void)
{
    LCD_RST_LOW();
    delay_ms(50);
    LCD_RST_HIGH();
    delay_ms(200);

    LCD_WriteCmd(0x01); delay_ms(150);
    LCD_WriteCmd(0x11); delay_ms(255);

    LCD_WriteCmd(0xB2);
    LCD_WriteData(0x05); LCD_WriteData(0x05);
    LCD_WriteData(0x00); LCD_WriteData(0x33); LCD_WriteData(0x33);

    LCD_WriteCmd(0x3A); LCD_WriteData(0x05);
    LCD_WriteCmd(0x36); LCD_WriteData(0x00);
    LCD_WriteCmd(0x21);
    LCD_WriteCmd(0x29); delay_ms(10);
}

//屏幕测试函数 铺满屏幕
void LCD_Fill(uint16_t color)
{
    uint32_t i;
    uint8_t hi = color >> 8;
    uint8_t lo = color & 0xFF;

    LCD_WriteCmd(0x2A);
    LCD_WriteData(0x00); LCD_WriteData(0x00);
    LCD_WriteData(0x00); LCD_WriteData(0xEF);

    LCD_WriteCmd(0x2B);
    LCD_WriteData(0x00); LCD_WriteData(0x00);
    LCD_WriteData(0x01); LCD_WriteData(0x3F);

    LCD_WriteCmd(0x2C);
    LCD_DC_HIGH();
    LCD_CS_LOW();

    for (i = 0; i < 240UL * 320UL; i++)
    {
        SPI1_Write(hi);
        SPI1_Write(lo);
    }

    LCD_CS_HIGH();
}