#include "I2cConfig.h"     // I2C1 + 触摸芯片 CST816T 相关声明

//调试变量
uint8_t  tp_pressed = 0;  // 当前是否有触摸
uint16_t tp_x = 0;        // 当前触摸 X 坐标
uint16_t tp_y = 0;        // 当前触摸 Y 坐标

// 触摸芯片最大坐标范围（物理分辨率）
#define TOUCH_MAX_X   240
#define TOUCH_MAX_Y   320

// I2C 超时计数 防止死循环
#define I2C_TIMEOUT  100000

//GPIO + I2C 初始化
static void I2C1_GPIO_Config(void)
{
    //使能 GPIOB 和 I2C1 时钟
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

    //PB6 PB7 配置为复用功能 AF4（I2C1），开漏，上拉 
    GPIOB->MODER &= ~((3<<(6*2)) | (3<<(7*2)));   // 清模式位
    GPIOB->MODER |=  ((2<<(6*2)) | (2<<(7*2)));   // 复用模式

    GPIOB->OTYPER |= (1<<6) | (1<<7);             // 开漏输出
    GPIOB->OSPEEDR |= (3<<(6*2)) | (3<<(7*2));    // 高速

    GPIOB->PUPDR &= ~((3<<(6*2)) | (3<<(7*2)));   // 清上下拉
    GPIOB->PUPDR |=  ((1<<(6*2)) | (1<<(7*2)));   // 上拉

    GPIOB->AFR[0] &= ~((0xF<<(6*4)) | (0xF<<(7*4))); // 清 AF
    GPIOB->AFR[0] |=  ((4<<(6*4)) | (4<<(7*4)));    // AF4 = I2C
}

//I2c初始化
void I2C1_Init(void)
{
    // 初始化 I2C1 对应 GPIO
    I2C1_GPIO_Config();

    //I2C 软件复位
    I2C1->CR1 = I2C_CR1_SWRST;   // 置位软件复位
    I2C1->CR1 = 0;               // 清除复位

    //APB1 = 25MHz
    I2C1->CR2   = 25;            // APB1 时钟频率 25MHz
    I2C1->CCR   = 125;           // 标准模式 100kHz
    I2C1->TRISE = 26;            // 上升时间配置

    I2C1->CR1 |= I2C_CR1_ACK;    // 使能 ACK
    I2C1->CR1 |= I2C_CR1_PE;     // 使能 I2C 外设

    //触摸复位脚 RST：PA0 输出 
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;        // 使能 GPIOA
    GPIOA->MODER &= ~(3<<(TP_RST_PIN*2));       // 清模式
    GPIOA->MODER |=  (1<<(TP_RST_PIN*2));       // 输出模式
    GPIOA->OTYPER &= ~(1<<TP_RST_PIN);          // 推挽输出

    //触摸中断脚 INT：PB5 输入，上拉 
    GPIOB->MODER &= ~(3<<(TP_INT_PIN*2));       // 输入模式
    GPIOB->PUPDR |=  (1<<(TP_INT_PIN*2));       // 上拉

    // 复位触摸芯片
    TP_Reset();
}

void TP_Reset(void)
{
    // 拉低复位脚
    TP_RST_PORT->ODR &= ~(1<<TP_RST_PIN);
    for(volatile int i=0;i<8000;i++);   // 短延时

    // 拉高复位脚
    TP_RST_PORT->ODR |= (1<<TP_RST_PIN);
    for(volatile int i=0;i<800000;i++); // 上电稳定延时
}

//I2C 读函数
uint8_t TP_ReadBytes(uint8_t reg, uint8_t *buf, uint8_t len)
{
    uint32_t timeout;

    //发送 START 
    I2C1->CR1 |= I2C_CR1_START;
    timeout = I2C_TIMEOUT;
    while(!(I2C1->SR1 & I2C_SR1_SB))
        if(--timeout == 0) return 1;

    //发送设备地址 + 写
    I2C1->DR = CST816T_ADDR << 1;
    timeout = I2C_TIMEOUT;
    while(!(I2C1->SR1 & I2C_SR1_ADDR))
        if(--timeout == 0) return 2;
    (void)I2C1->SR2;   // 清 ADDR 标志

    //发送寄存器地址
    I2C1->DR = reg;
    timeout = I2C_TIMEOUT;
    while(!(I2C1->SR1 & I2C_SR1_TXE))
        if(--timeout == 0) return 3;

    //发送 RESTART
    I2C1->CR1 |= I2C_CR1_START;
    timeout = I2C_TIMEOUT;
    while(!(I2C1->SR1 & I2C_SR1_SB))
        if(--timeout == 0) return 4;

    //发送设备地址 + 读
    I2C1->DR = (CST816T_ADDR << 1) | 1;
    timeout = I2C_TIMEOUT;
    while(!(I2C1->SR1 & I2C_SR1_ADDR))
        if(--timeout == 0) return 5;
    (void)I2C1->SR2;   // 清 ADDR

    // 连续读取数据
    for(uint8_t i=0;i<len;i++)
    {
        if(i == len-1)
        {
            I2C1->CR1 &= ~I2C_CR1_ACK;   // 最后一个字节关闭 ACK
            I2C1->CR1 |= I2C_CR1_STOP;  // 发送 STOP
        }

        timeout = I2C_TIMEOUT;
        while(!(I2C1->SR1 & I2C_SR1_RXNE))
            if(--timeout == 0) return 6;

        buf[i] = I2C1->DR;               // 读取数据
    }

    I2C1->CR1 |= I2C_CR1_ACK;            // 恢复 ACK
    return 0;                            // 成功
}

// 读取单个寄存器
uint8_t TP_ReadOneByte(uint8_t reg, uint8_t *data)
{
    return TP_ReadBytes(reg, data, 1);
}

//触摸信息
uint8_t TP_GetTouch(TouchData_t *touch)
{
    uint8_t finger = 0;   // 手指数
    uint8_t buf[4];       // 坐标缓存
    uint8_t gesture;      // 手势寄存器

    /* 1. 读取手指数 */
    if (TP_ReadOneByte(0x02, &finger) != 0)
        return 1;

    // 无触摸
    if ((finger & 0x0F) == 0)
    {
        touch->pressed = 0;
        tp_pressed = 0;

        // 读取一次 Gesture 清状态
        TP_ReadOneByte(0x01, &gesture);

        return 0;
    }

    //读取 X/Y 坐标
    if (TP_ReadBytes(0x03, buf, 4) != 0)
        return 2;

    touch->pressed = 1;
    touch->x = ((buf[0] & 0x0F) << 8) | buf[1];  // X 坐标
    touch->y = ((buf[2] & 0x0F) << 8) | buf[3];  // Y 坐标

    tp_pressed = 1;
    tp_x = touch->x;
    tp_y = touch->y;

    //通知芯片已处理
    TP_ReadOneByte(0x01, &gesture);

    return 0;
}

//触摸状态
void lv_touchpad_read(lv_indev_drv_t * indev_drv,
                      lv_indev_data_t * data)
{
    TouchData_t t;

    // 读取触摸状态
    TP_GetTouch(&t);

    if(t.pressed)
    {
        data->state = LV_INDEV_STATE_PR;  // 按下状态

        /* 映射到 LVGL 坐标系 */
        data->point.x = (t.x * LV_HOR_RES_MAX) / TOUCH_MAX_X;
        data->point.y = (t.y * LV_VER_RES_MAX) / TOUCH_MAX_Y;
    }
    else
    {
        data->state = LV_INDEV_STATE_REL; // 松开状态
    }
}

//注册 LVGL 输入设备
void lv_port_indev_init(void)
{
    static lv_indev_drv_t indev_drv;   // 输入设备驱动结构体

    lv_indev_drv_init(&indev_drv);     // 初始化默认值
    indev_drv.type = LV_INDEV_TYPE_POINTER; // 指针类设备
    indev_drv.read_cb = lv_touchpad_read;   // 读取回调

    lv_indev_drv_register(&indev_drv); // 注册到 LVGL
}
