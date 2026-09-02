# ST 官方文档与参考资料索引库

本目录用于整理并归档 STM32F103 系列芯片的 ST 官方核心技术手册、工具链简报与编程参考。

---

## 📑 已归档官方文档与数据简报

- [📄 DB2163 - STM32CubeMX 数据简报与架构解析](DB2163_STM32CubeMX_Data_Brief.md)：STM32CubeMX 图形配置工具特性、时钟求解器、STM32Cube 生态工具链组成。

---

## 必读核心官方文档索引

| 文档编号 | 文档名称 (Document Title) | 核心内容说明 |
| :--- | :--- | :--- |
| **RM0008** | *STM32F101xx, STM32F102xx, STM32F103xx, STM32F105xx and STM32F107xx advanced Arm-based 32-bit MCUs Reference Manual* | **【权威参考手册】** 包含所有外设（RCC、GPIO、USART、TIM、ADC、DMA、I2C、SPI、CAN等）的寄存器描述与工作原理 |
| **PM0056** | *STM32F10xxx/20xxx/21xxx/L1xxxx Cortex-M3 programming manual* | **【内核编程手册】** 包含 Cortex-M3 架构、汇编指令集、NVIC 中断与 SysTick 详尽说明 |
| **DS5319** | *STM32F103x8, STM32F103xB DataSheet* | 中密度芯片（64K/128K Flash）电气特性、引脚定义、时序与封装尺寸 |
| **DS5792** | *STM32F103xC, STM32F103xD, STM32F103xE DataSheet* | 高密度芯片（256K~512K Flash）电气特性、FSMC 接口与引脚分布 |
| **UM1850** | *Description of STM32F1 HAL and low-layer drivers* | ST 官方 HAL/LL 驱动库 API 参考手册 |
| **DB2163** | *STM32CubeMX Data Brief* | STM32CubeMX 配置与初始化 C 代码生成工具说明简报 |
| **AN2586** | *Getting started with STM32F10xxx hardware development* | 官方硬件电路设计指南（电源去耦、时钟布局、布线注意事项） |
| **AN2606** | *STM32 microcontroller system memory boot mode* | 内置 Bootloader 通信协议与 ISP 串口下载详解 |

---

## 推荐学习与研读路径
1. **第一阶段 (基础入门)**：结合开发板原理图研读 **AN2586** 与 **RM0008 的 RCC / GPIO 章节**，理解系统时钟树与端口模式。
2. **第二阶段 (外设与中断实战)**：结合 **PM0056 的 NVIC 章节** 和 **RM0008 的 USART / EXTI / TIM 章节**，掌握中断与外设通信。
3. **第三阶段 (RTOS 与多任务)**：深入研读 **PM0056 的 SVC / PendSV / SysTick 异常机制**，彻底掌握上下文切换原理。
