# 05 - STM32CubeMX 与产品架构对接指南

CubeMX 在本项目中是引脚、时钟和外设初始化的辅助设计工具，不是工程结构或构建
配置的唯一来源。生成代码必须在临时目录审查后迁入，不能直接覆盖当前仓库。

## 配置前先确定产品

| 产品 | MCU | HSE / SYSCLK | 主 LED | 应用按键 | 控制台 |
| --- | --- | --- | --- | --- | --- |
| `bluepill_f103c8` | STM32F103C8T6 | 8 / 72 MHz | PC13，低有效 | 无 | USART1 PA9/PA10 |
| `atk_elite_f103ze` | STM32F103ZET6 | 8 / 72 MHz | PB5，低有效 | PE4，低有效上拉 | USART1 PA9/PA10 |

CubeMX 的 MCU、封装、晶振和引脚必须与目标产品一致。精英板的 LED1、KEY1 和
WK_UP 等完整资源以 `product/atk_elite_f103ze/include/product_config.h` 为准。

## CubeMX 配置基线

1. 在 MCU Selector 中选择准确料号，而不是只选同系列近似型号。
2. `System Core -> SYS -> Debug` 选择 `Serial Wire`，保留 PA13/PA14。
3. `RCC -> HSE` 选择 `Crystal/Ceramic Resonator`；输入 8 MHz，PLL ×9，HCLK
   设为 72 MHz，并复核 APB1 不超过 36 MHz。
4. 按产品资源配置 GPIO 和 USART1。不要把 BluePill 的 PC13 示例复制到精英板。
5. 生成时勾选“每个外设生成独立 .c/.h”和“保留 USER CODE”，输出到仓库外的
   临时目录。生成器选 CMake、Makefile 或 STM32CubeIDE 都不会改变本仓库的
   CMake/Kconfig 结构。

## 迁入规则

```text
CubeMX 临时输出
      │ 比对、审查
      ├─ 时钟/引脚事实 ───────> product/*/include/product_config.h
      ├─ MCU/容量/启动文件 ───> product/*/product.cmake
      ├─ 通用 CMSIS/HAL 更新 ─> drivers/（整版本导入并保留许可证）
      ├─ 外设底层初始化 ──────> bsp/src + bsp/inc
      └─ 中断/系统专用胶水 ───> platform/src
```

- 不直接替换 `drivers/CMSIS`。当前 CMSIS Device 来自 STM32CubeF1 v1.8.7；升级时
  应按一个完整上游版本导入，保留版本和许可证，并重新验证两个器件密度启动文件。
- 不用 CubeMX 的 `main.c` 替换 `platform/src/main.c`。当前唯一入口只调用
  `SystemRuntime_Start()`。
- 不复制 CubeMX 生成的 `SysTick_Handler`。裸机、RT-Thread 和 FreeRTOS 运行时
  分别拥有唯一时基入口。
- 不在 BSP 中硬编码 MCU 型号或产品引脚。板级资源来自 `product_config.h`，产品
  能力决定 Kconfig 选项是否可见。
- 不把生成目录整体加入 CMake。按模块使用 `target_sources()` 显式登记需要的
  源文件，头文件和宏通过目标级属性传播。

## 更新一个外设的工作流

1. 在 CubeMX 临时工程修改并生成代码，保存 `.ioc` 作为设计依据（如决定入库，
   应放在对应产品目录）。
2. 比较时钟、GPIO、NVIC 和外设初始化差异，仅迁入需要的逻辑。
3. 新增产品静态资源宏；若只有部分产品具备该硬件，再增加产品能力宏。
4. 在 `bsp/Kconfig` 增加依赖能力的功能项，在 `bsp/CMakeLists.txt` 条件登记源码。
5. 保持应用调用 BSP 抽象，不引用 HAL 句柄、产品引脚或 RTOS API。
6. 运行目标产品的三系统 Debug/Release；共享驱动或公共时钟有变化时运行完整
   `build/build.bat all` 矩阵。

## 验收清单

- menuconfig 只能选择产品实际具备的资源。
- 三个系统各自只有一个 SysTick/调度入口，链接无重复中断符号。
- 生成链接脚本中的 Flash/RAM 与产品容量一致。
- USART1 为 115200 8N1，启动日志产品名、系统名和实际时钟正确。
- LED 极性正确；精英板 KEY0 上拉和低有效配置正确。
- 固件容量与 RTOS 互斥检查通过，并完成目标板烧录和外设实测。
