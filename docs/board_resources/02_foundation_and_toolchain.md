# 基础、工具链与工程结构

对应原书第 1-12 章，PDF p.22-190。

## 章节摘要

| 章节 | 主题 | 核心内容 |
| --- | --- | --- |
| 1 | 学习方法 | 建议按基础篇、入门篇、提高篇推进；结合数据手册、参考手册、原理图和例程源码学习 |
| 2 | STM32 简介 | STM32F103ZET6 资源、型号命名、选型、最小系统和 IO 分配 |
| 3 | 开发环境 | MDK、调试器驱动和 CH340 USB 串口驱动 |
| 4 | STM32 初体验 | 编译例程、串口下载、DAP 下载/调试及 MDK 使用技巧 |
| 5 | 基础知识 | C 语言要点、寄存器、Cortex-M3、总线、存储器和寄存器映射 |
| 6 | 寄存器版工程 | 启动文件、SYSTEM 文件、工程分组和 MDK 各配置页 |
| 7 | HAL 库 | CMSIS、Cube 固件包、HAL 驱动目录、时基和中断处理 |
| 8 | HAL 版工程 | 从零建立 HAL 工程，加入 CMSIS、HAL Driver、User 与 SYSTEM 代码 |
| 9 | 启动过程 | 启动模式、向量表、启动汇编、`SystemInit`、C 运行时和 map 文件 |
| 10 | STM32CubeMX | 安装、固件包、选型、HSE/LSE、时钟树、GPIO、Debug 和代码生成 |
| 11 | 时钟配置 | 时钟源、PLL、SYSCLK、MCO，以及 STM32F1 主频修改流程 |
| 12 | SYSTEM 文件夹 | `delay`、`sys`、`usart` 等配套公共组件及 `printf` 重定向 |

## 建议掌握的工程层次

```text
应用层
  main.c / 业务模块
板级驱动层
  LED、按键、传感器、显示、通信器件驱动
STM32 HAL/LL 层
  stm32f1xx_hal_*.c / stm32f1xx_hal_conf.h
CMSIS 与器件层
  core_cm3.h / stm32f103xe.h / system_stm32f1xx.c
启动与链接层
  startup_stm32f103xe.s / 链接脚本或 scatter 文件
```

配套例程中的 `SYSTEM`、`USMART` 等目录是正点原子的工程组织方式，不是 HAL 的强制结构。移植到本项目时应按功能拆分，而不是机械复制目录。

## 从复位到 main

典型启动过程如下：

1. 根据 BOOT 引脚选择从 Flash、系统存储器或 SRAM 启动。
2. 内核从向量表读取初始 MSP 和复位处理函数地址。
3. 启动文件执行复位处理，调用 `SystemInit()` 配置基础系统状态。
4. C 运行库完成 `.data` 搬运和 `.bss` 清零。
5. 跳转到 `main()`，再执行 HAL、时钟和板级外设初始化。

排查“程序不进 main”时，应依次检查启动模式、向量表地址、启动文件型号、链接脚本、栈指针、系统时钟及 HardFault。

## HAL 工程最小组成

- 与芯片容量匹配的启动文件，例如 STM32F103ZET6 通常使用高密度器件启动文件。
- CMSIS 内核头文件、STM32F1 器件头文件和 `system_stm32f1xx.c`。
- 使用到的 `stm32f1xx_hal_*.c` 驱动文件及 `stm32f1xx_hal_conf.h`。
- `HAL_Init()`、系统时钟配置、GPIO 和所需外设初始化。
- 正确的预处理宏、包含路径、Flash/RAM 地址与容量。

只把头文件加入工程并不等于加入驱动实现；链接错误时应检查对应 `.c` 文件是否参与构建。

## CubeMX 建立工程的主流程

1. 选择准确的 MCU 型号或开发板。
2. 在 RCC 中设置 HSE/LSE 来源，避免时钟树假设与实物不一致。
3. 配置 SYSCLK、AHB、APB1、APB2 和外设时钟。
4. 分配 GPIO/外设引脚，检查冲突和 AFIO 重映射。
5. 保留 Serial Wire 调试接口。
6. 配置工程名称、工具链和代码生成选项。
7. 仅在 `USER CODE` 区域写入需要跨重新生成保留的代码。

## 72 MHz 时钟要点

精英板常见配置是 8 MHz HSE 经 PLL x9 得到 72 MHz SYSCLK。典型总线设置为：

- AHB/HCLK：72 MHz。
- APB1/PCLK1：36 MHz，不得超过 STM32F1 的 APB1 上限。
- APB2/PCLK2：72 MHz。
- 当 APB 预分频不为 1 时，对应定时器时钟通常为该 PCLK 的 2 倍。

实际工程必须以开发板晶振、器件数据手册和时钟树校验结果为准。修改主频后还要同步检查 Flash 等待周期、SysTick、串口波特率、定时器和延时实现。

## 寄存器与 HAL 的关系

- HAL 最终仍通过器件寄存器完成配置；学习寄存器映射有助于排查 HAL 参数或时序问题。
- 直接操作寄存器时优先使用 CMSIS 器件头文件定义，避免手写魔数地址。
- 同一外设不要在不清楚副作用的情况下混用 HAL 初始化与零散寄存器覆盖。
- 中断状态位通常需要按参考手册规定清除；读改写寄存器时要注意保留位和写 1 清零位。

## 移植到非 MDK 工程时

- MDK 的 Target、C/C++、Debug、Utilities 选项应映射为编译器参数、链接脚本、下载器配置和调试配置。
- Keil scatter 文件与 GNU ld 链接脚本语法不同，不能直接互换。
- ARMCC/ArmClang 与 GCC 的启动代码、弱符号、内联汇编和标准库重定向写法可能不同。
- `printf` 重定向应根据所用 C 库实现 `_write`、`fputc` 或其他接口，避免只复制 Keil 版本代码。
