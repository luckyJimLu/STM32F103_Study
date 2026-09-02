# FreeRTOS 模块使用与源码引入说明

本目录用于存放 **FreeRTOS** 内核源码及针对 STM32F103 (Cortex-M3) 的端口文件。

## 目录结构规划
- `include/`: FreeRTOS 核心头文件 (`FreeRTOS.h`, `task.h`, `queue.h`, `semphr.h` 等)
- `src/`: FreeRTOS 核心源码 (`tasks.c`, `queue.c`, `list.c`, `timers.c`, `event_groups.c`)
- `portable/GCC/ARM_CM3/`: Cortex-M3 GCC 移植层 (`port.c`, `portmacro.h`)
- `portable/MemMang/`: 内存管理算法 (推荐 `heap_4.c`)
- `FreeRTOSConfig.h`: FreeRTOS 参数裁剪配置文件

## 移植参考
详情请参考知识库文档：[FreeRTOS 移植实战指南](../../../docs/porting_guides/03_freertos_porting.md)
