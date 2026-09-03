# 固件架构与配置边界

## 配置模型

产品选择和系统选择是两个正交的 Kconfig choice。产品配置是 MCU、存储布局、
时钟和板载资源的唯一来源；系统配置只决定运行时端口和内核。固定 defconfig
用于回归构建，本地 `.config` 用于开发调试。

| 产品 | 主 LED | 应用按键 | 控制台 | HSE |
| --- | --- | --- | --- | --- |
| `bluepill_f103c8` | PC13，低有效 | 无 | USART1 PA9/PA10 | 8MHz |
| `atk_elite_f103ze` | PB5，低有效 | PE4，低有效上拉 | USART1 PA9/PA10 | 8MHz |

精英板的 PE5、PE3 和 PA0 也记录在产品资源头中，但当前示例应用只使用主 LED
和 KEY0。BluePill 只有 NRST 板载按键，因此按键菜单在该产品下不可选。

## 层次约束

1. `product` 只提供静态资源和构建参数。
2. `drivers` 依赖产品配置和 CMSIS，不依赖 BSP、应用或 RTOS。
3. `bsp` 依赖驱动，不得直接判断 `STM32F103xB/xE`。
4. `app` 依赖 BSP，只暴露 `App_Init()` 和非阻塞 `App_Process(now_ms)`。
5. `platform` 负责 main、调度器、任务包装和 SysTick，并选择唯一 RTOS 内核。

新增产品时必须提供产品头、CMake 元数据和三个系统 defconfig；新增 BSP 外设时
必须使用产品能力宏并让 Kconfig 控制源码和初始化。新增第三方组件前必须具备
固定版本源码、许可证、目标平台端口和至少一个可运行验证。

## 时基与错误处理

裸机、RT-Thread 和 FreeRTOS 各自提供唯一 `SysTick_Handler`，同时维护 HAL
毫秒 tick。应用按固定轮询周期运行，用时间差处理心跳和非阻塞按键去抖。
时钟、任务创建或调度器启动失败统一进入 `BSP_FatalError()`，不会继续以未知
时钟或半初始化状态运行。
