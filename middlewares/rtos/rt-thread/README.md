# RT-Thread Nano 3.1.5

本目录保存 RT-Thread Nano v3.1.5 内核、Cortex-M3 GCC 端口和许可证。
板级初始化、控制台和 SysTick 适配位于 `platform` 的 RT-Thread 系统端口，
不属于内核源码。

当前工程使用静态应用线程，不启用动态 heap 或 FinSH；menuconfig 只展示已经
接入实现的 tick、优先级、线程栈和时间片参数。
