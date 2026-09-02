# 03 - FreeRTOS 移植与任务实战指南

## 一、FreeRTOS 体系架构概述
FreeRTOS 是全球应用最广泛的小型开源嵌入式实时操作系统。
在 STM32F103 (ARM Cortex-M3) 平台上，FreeRTOS 的核心代码由三部分组成：
1. **核心文件**：`tasks.c`, `queue.c`, `list.c`, `timers.c`
2. **移植适配层**：`portable/GCC/ARM_CM3/` (`port.c`, `portmacro.h`)
3. **内存堆管理**：`portable/MemMang/heap_4.c` (最推荐的内存管理实现)

---

## 二、移植关键注意事项

### 1. 中断向量映射
FreeRTOS 的任务切换依赖 `SVC_Handler`、`PendSV_Handler` 以及 `SysTick_Handler`。
在 `FreeRTOSConfig.h` 中进行宏重映射：
```c
#define vPortSVCHandler     SVC_Handler
#define xPortPendSVHandler  PendSV_Handler
#define xPortSysTickHandler SysTick_Handler
```

### 2. Cortex-M3 中断优先级分组规范
> [!IMPORTANT]
> STM32F103 在配合 FreeRTOS 使用时，强烈建议将 NVIC 优先级分组配置为 **NVIC_PRIORITYGROUP_4**（全部 4 位都用于抢占优先级，0 位用于响应优先级）。
> 这样可以确保 FreeRTOS API 安全中断管理（`configMAX_SYSCALL_INTERRUPT_PRIORITY`）正确生效。

---

## 三、实战：多任务与消息队列示例
```c
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "bsp_led.h"

static TaskHandle_t xLedTaskHandle = NULL;

void vLedTask(void *pvParameters)
{
    while (1)
    {
        BSP_LED_Toggle();
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

int main(void)
{
    BSP_Init();

    xTaskCreate(vLedTask, "LedTask", 128, NULL, 2, &xLedTaskHandle);

    /* 启动调度器 */
    vTaskStartScheduler();

    while (1);
}
```
