# 02 - RT-Thread Nano 移植与实战指南

## 一、RT-Thread Nano 简介
RT-Thread Nano 是一个极简版的硬实时内核，内存占用极小（ROM < 5KB，RAM < 1KB），非常适合资源受限的 STM32F103 系列芯片。

---

## 二、移植核心步骤

### 1. 中断向量冲突处理
RT-Thread 需要接管 Cortex-M3 的三个核心系统异常：
- `HardFault_Handler`: 硬件故障处理（打印调用栈）
- `PendSV_Handler`: 线程上下文切换核心
- `SysTick_Handler`: 提供系统心跳（Tick）

> [!CAUTION]
> 检查 `startup_stm32f103xx.s` 中若有定义 `PendSV_Handler` 与 `HardFault_Handler`，需避免重复强定义，RT-Thread `libcpu` 中已提供了标准汇编实现（如 `context_gcc.S`）。

### 2. 硬件初始化对接 (`board.c`)
- 在 `rt_hw_board_init()` 中初始化系统时钟与板级硬件：
  ```c
  void rt_hw_board_init(void)
  {
      BSP_Init(); /* 初始化时钟、外设与 SysTick */
      
      #if defined(RT_USING_HEAP)
      /* 初始化内存堆 */
      rt_system_heap_init((void*)&__bss_end__, (void*)_STM32_SRAM_END);
      #endif
  }
  ```
- 在 SysTick 中断中调用 `rt_tick_increase()`：
  ```c
  void SysTick_Handler(void)
  {
      rt_interrupt_enter();
      rt_tick_increase();
      rt_interrupt_leave();
  }
  ```

### 3. 控制台输出对接 (FinSH 交互)
实现 `rt_hw_console_output()` 函数：
```c
void rt_hw_console_output(const char *str)
{
    BSP_USART1_SendString(str);
}
```

---

## 三、实战：创建第一个 RT-Thread 任务
```c
#include <rtthread.h>
#include "bsp_led.h"

static struct rt_thread led_thread;
static rt_uint8_t led_stack[256];

static void led_thread_entry(void *parameter)
{
    while (1)
    {
        BSP_LED_Toggle();
        rt_thread_mdelay(500);
    }
}

int main(void)
{
    rt_thread_init(&led_thread,
                   "led_task",
                   led_thread_entry,
                   RT_NULL,
                   &led_stack[0],
                   sizeof(led_stack),
                   20, 10);
    rt_thread_startup(&led_thread);
    return 0;
}
```
