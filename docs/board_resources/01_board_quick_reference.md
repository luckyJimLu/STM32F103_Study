# 正点原子精英 STM32F103 开发板资源速查

## 主控资源

精英开发板使用 STM32F103ZET6，LQFP144 封装。教程在 PDF p.29 给出的资源如下：

| 项目 | 规格 | 项目 | 规格 |
| --- | --- | --- | --- |
| 内核 | Cortex-M3 | 主频 | 72 MHz |
| Flash | 512 KB | SRAM | 64 KB |
| IO | 112 | 工作电压 | 3.3 V |
| 通用定时器 | 8 | 高级定时器 | 2 |
| USART | 5 | SPI | 3 |
| I2C | 2 | CAN | 1 |
| ADC | 3 个 12 位 ADC，共 18 通道 | DAC | 2 个 12 位 DAC |
| DMA | 2 | RTC | 1 |
| SDIO | 1 | FSMC | 1 |
| USB | USB Device | FPU | 无 |

## 常用板载 IO

| 资源 | MCU 引脚 | 电气/使用说明 | 来源页 |
| --- | --- | --- | --- |
| LED0 | PB5 | 低电平点亮；与 TIM3_CH2 PWM 实验复用 | PDF p.201、p.285 |
| LED1 | PE5 | 低电平点亮 | PDF p.201 |
| 蜂鸣器 BEEP | PB8 | GPIO 控制 | PDF p.207 |
| KEY0 | PE4 | 低电平有效，内部上拉 | PDF p.212-213 |
| KEY1 | PE3 | 低电平有效，内部上拉 | PDF p.212-213 |
| KEY_UP/WK_UP | PA0 | 高电平有效，内部下拉；还可作 TIM2_CH1/TIM5_CH1 | PDF p.212-213、p.294、p.305 |
| 电容触摸 TPAD | PA1 | 通过跳线帽连接；与 ADC 输入等功能复用 | PDF p.353 |
| 红外输入 REMOTE_IN | PB9 | TIM4_CH4 输入捕获 | PDF p.641 |
| DS18B20/DHT11 接口 | PG11 | 两类传感器共用同一个接口，不能同时插用 | PDF p.652、p.662 |
| 光敏传感器 | PF8 | ADC3_CH6 | PDF p.513 |

## 串行总线和板载器件

| 功能 | 引脚/外设 | 板级要求与注意事项 | 来源页 |
| --- | --- | --- | --- |
| USB 转串口 | USART1: PA9/PA10 | 接板载 CH340，按丝印安装对应跳线帽 | PDF p.237 |
| 软件 I2C + AT24C02 | SCL PB6，SDA PB7 | 教程使用 GPIO 模拟 I2C；SDA 使用开漏方式 | PDF p.547、p.543-558 |
| SPI NOR Flash | SPI2: PB13/PB14/PB15 | 教程使用 NM25Q128/W25Qxx 类器件；与 NRF24L01 共用 SPI2 | PDF p.560-579、p.669-683 |
| NRF24L01 | SPI2；CE PG8，CSN PG7，IRQ PG6 | 与 NOR Flash 分时复用，未使用器件的片选应保持无效 | PDF p.669-683 |
| RS485 | USART2: PA2/PA3；方向 PD7 | P5 跳线连通收发器；PD7=0 接收、PD7=1 发送；A/B 不可接反 | PDF p.580-588 |
| CAN | CAN1: PA11/PA12 | P6 跳线连接 CRX/CTX；板上含收发器和 120 ohm 终端电阻 | PDF p.589-615 |
| USB Device | PA11 D-，PA12 D+ | 通过 P3 跳线连接；与 CAN 共用 PA11/PA12，不能同时使用 | PDF p.605、p.852、p.867 |
| microSD | SDIO | 用于 SD 卡、FATFS、图片和照相机实验 | PDF p.725-805 |

## 定时器和模拟引脚

| 用途 | 引脚/资源 | 说明 |
| --- | --- | --- |
| TIM3 PWM 输出 | PB5/TIM3_CH2 | 直接控制 LED0 亮度，LED0 为低电平有效 |
| TIM5 输入捕获 | PA0/TIM5_CH1 | 与 WK_UP 共用，用按键产生输入脉冲 |
| TIM2 脉冲计数 | PA0/TIM2_CH1 | 与 WK_UP 共用，KEY0 用于清零 |
| TIM8 四通道输出比较 | PC6-PC9/TIM8_CH1-CH4 | 适合使用示波器观察四路相位 |
| TIM1 互补 PWM | PE9 正向、PE8 互补、PE15 刹车 | 用示波器检查死区和刹车行为 |
| PWM 输入 | PB5 输出，PC6 输入 | 用杜邦线连接 PB5 到 PC6 |
| ADC 外部单通道 | PA1/ADC1_CH1 | 可通过跳线连接板载电位器，量程约 0-3.3 V |
| ADC 多通道 | PA0-PA5/ADC1_CH1-CH6 | DMA1_Channel1 连续搬运 |
| 内部温度 | ADC1_CH16 | 使用内部温度传感器，注意采样时间与换算参数 |
| 光敏输入 | PF8/ADC3_CH6 | 读取板载光敏传感器输出 |
| DAC 输出 | PA4/DAC1_CH1 | 可直接接示波器观察直流、三角波或正弦波 |

## 显示和摄像头接口

### OLED 模块

教程的 0.96 英寸 OLED 复用了摄像头接口信号：

| OLED 信号 | 开发板信号/引脚 |
| --- | --- |
| CS | OV_WRST / PD6 |
| RS | OV_SCL / PD3 |
| WR | OV_RRST / PG14 |
| RD | DCMI_SDA / PG13 |
| RST | DCMI_RESET / PG15 |

### TFTLCD

开发板接口支持正点原子 MCU 屏，以 16 位 8080 并口经 FSMC 驱动。模块可直接插接，但仍应确认屏幕型号、控制器 ID 和接口方向。教程从 PDF p.375 开始介绍 TFTLCD 与 FSMC。

### OV7725 摄像头

| 模块信号 | MCU 引脚 | 模块信号 | MCU 引脚 |
| --- | --- | --- | --- |
| OV_D0-D7 | PC0-PC7 | FIFO_OE | PG15 |
| OV_SCL | PD3 | FIFO_WRST | PD6 |
| OV_SDA | PG13 | FIFO_WEN | PB3 |
| OV_VSYNC | PA8/EXTI8 | FIFO_RCLK | PB4 |
| FIFO_RRST | PG14 | - | - |

安装摄像头模块时建议断电，模块方向应按开发板座子和教程图示确认。相关内容见 PDF p.698-714。

## 关键复用冲突

| 冲突 | 影响 | 处理方式 |
| --- | --- | --- |
| CAN 与 USB 共用 PA11/PA12 | 两者不能同时连接到 MCU | 通过 P6/P3 跳线二选一，并同步修改软件配置 |
| NOR Flash 与 NRF24L01 共用 SPI2 | 同时访问会产生总线争用 | 独立片选、分时访问，保持非目标器件 CS 为无效状态 |
| DS18B20 与 DHT11 共用 PG11 接口 | 两种传感器不能同时占用 | 只安装并初始化当前实验所需器件 |
| LED0 与 TIM3_CH2 共用 PB5 | GPIO 和 PWM 模式不能同时使用 | 根据实验重新配置 PB5，注意 LED 低电平有效 |
| WK_UP 与定时器通道共用 PA0 | 按键输入、捕获、计数功能互斥 | 按实验选择 GPIO/AF 输入模式 |
| TPAD、ADC 和 DAC 实验会占用模拟排针 | 跳线或外部信号可能改变采样结果 | 实验前核对 P7/P10 跳线和外部输入范围 |
| OLED 与摄像头接口复用多根 IO | 同时连接可能造成驱动冲突 | 不同时初始化两个模块，必要时断开其中一个 |

## 上电和调试检查清单

1. 确认供电为 3.3 V 逻辑，不向 MCU IO 直接输入 5 V，除非数据手册明确标注该引脚容忍 5 V。
2. 按当前实验检查 P3、P5、P6、P7/P10 等跳线，尤其注意 USB/CAN 和 RS485 路由。
3. 确认 HSE/LSE 配置与实物晶振一致，再配置 72 MHz 系统时钟。
4. 保留 SWD 调试引脚，先验证下载、复位和串口输出，再逐个启用复杂外设。
5. 检查 GPIO 模式、上拉/下拉、复用重映射和外设时钟，不要只检查引脚编号。
6. 连接示波器、传感器或总线时必须共地；RS485/CAN 差分线不得接反。
