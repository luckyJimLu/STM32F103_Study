# FreeRTOS 模块使用与源码引入说明

本目录保存当前工程已有的 **FreeRTOS V10.4.4+ / V202112.00 快照**及
STM32F103 Cortex-M3 GCC 端口。产品、应用和 BSP 不在此处配置。

## 目录结构规划
- `include/`: FreeRTOS 核心头文件 (`FreeRTOS.h`, `task.h`, `queue.h`, `semphr.h` 等)
- `src/`: FreeRTOS 核心源码 (`tasks.c`, `queue.c`, `list.c`, `timers.c`, `event_groups.c`)
- `portable/GCC/ARM_CM3/`: Cortex-M3 GCC 移植层 (`port.c`, `portmacro.h`)
- `portable/MemMang/`: 内存管理算法（当前 CMake 只编译 `heap_4.c`）
- `FreeRTOSConfig.h`: FreeRTOS 参数裁剪配置文件

板级初始化、应用任务创建和调度器启动位于
`platform/src/system_runtime_freertos.c`；统一应用逻辑位于 `app/`。SysTick 包装
与 HAL tick 转换在 `freertos_hooks.c`，其他层不得再定义 SysTick。可调参数来自
本目录 `Kconfig` 生成的 `CONFIG_FREERTOS_*` 宏。

## 移植参考
详情请参考：[FreeRTOS 当前端口与历史移植参考](../../../docs/porting_guides/03_freertos_porting.md)
