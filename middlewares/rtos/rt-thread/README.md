# RT-Thread Nano 模块使用与源码引入说明

本目录用于存放 **RT-Thread Nano** 源码以及针对 STM32F103 的移植文件。

## 目录结构规划
- `include/`: RT-Thread 核心头文件 (`rtthread.h`, `rtdef.h` 等)
- `src/`: RT-Thread 内核源码 (`clock.c`, `components.c`, `idle.c`, `ipc.c`, `irq.c`, `kservice.c`, `mem.c`, `object.c`, `scheduler.c`, `thread.c`, `timer.c`)
- `libcpu/arm/cortex-m3/`: Cortex-M3 架构适配文件 (`context_gcc.S`, `cpuport.c`)
- `components/finsh/`: FinSH 控制台（可选）
- `rtconfig.h`: 内核裁剪与配置文件
- `board.c`: 硬件时钟、控制台输入输出接口适配

## 如何获取完整 Nano 源码
推荐直接从官方仓库或包管理器拉取：
```bash
git clone -b v3.1.5 https://github.com/RT-Thread/rtthread-nano.git
```
或参考本工程文档：[RT-Thread Nano 移植手册](../../../docs/porting_guides/02_rt_thread_nano_porting.md)
