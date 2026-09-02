# STM32F103 硬件知识库与设计资料

本目录用于归档与组织 STM32F103 开发板及周边外设的硬件设计文件、原理图、引脚分配及元器件选型资料。

正点原子精英 STM32F103 开发板的教程摘要、模块化学习笔记和引脚速查，见 [开发板资料](../board_resources/README.md)。

## 目录索引
- [原理图设计指南与引脚分配](schematics_guide.md)：最小系统电路、时钟、复位、供电与调试接口设计规范。
- 建议归档文件：
  - `schematics/`: 存放 PDF 格式或 EDA 原理图文件 (Altium Designer / KiCad / 嘉立创EDA)
  - `pcb/`: 存放 PCB 设计图与 Gerber 生产文件
  - `datasheets/`: 核心外设芯片（如 Flash W25Qxx、OLED SSD1306、传感器等）的数据手册

---

## 常用板型硬件配置速查

### 1. STM32F103C8T6 (BluePill 最小系统板)
- **主控型号**：STM32F103C8T6 (LQFP48, 64KB Flash, 20KB SRAM)
- **板载晶振**：主频晶振 8.000MHz，RTC 晶振 32.768kHz
- **板载 LED**：连接至 `PC13`（低电平点亮）
- **按键**：`NRST` 复位按键
- **调试接口**：SWD (SWDIO - PA13, SWCLK - PA14, 3.3V, GND)
- **串口通信**：USART1 (TX - PA9, RX - PA10)

### 2. STM32F103ZET6 (增强型开发板)
- **主控型号**：STM32F103ZET6 (LQFP144, 512KB Flash, 64KB SRAM, 支持 FSMC)
- **板载 LED**：LED0 (`PB5`), LED1 (`PE5`)
- **板载按键**：KEY0 (`PE4`), KEY1 (`PE3`), WK_UP (`PA0`)
- **常用外设接口**：TFT-LCD (FSMC)、SRAM、SPI Flash、RS485、CAN、EEPROM
