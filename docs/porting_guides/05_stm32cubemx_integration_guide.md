# 05 - STM32CubeMX 图形化配置与代码生成对接实战

本文档指导如何在本项目架构下，使用 **STM32CubeMX** 进行芯片图形化引脚配置、时钟树求解、外设初始化代码生成，并与现有的 **CMake + Ninja + Kconfig + BSP** 体系无缝融合。

---

## 一、STM32CubeMX 完整操作分步指南

### 1. 芯片选型 (Pinout & MCU Selection)
1. 打开 STM32CubeMX，点击 **"ACCESS TO MCU SELECTOR"**。
2. 在搜索框中输入你的芯片型号（如 `STM32F103C8` 或 `STM32F103ZE`）。
3. 双击选中芯片进入引脚配置界面。

---

### 2. 核心基础外设配置 (必配项)
1. **调试接口 (SYS)**：
   - 进入 `System Core` -> `SYS`。
   - `Debug` 选项选择 **`Serial Wire`**（非常重要，避免烧录后 SWD 引脚被复用导致无法再次烧录）。
2. **时钟源 (RCC)**：
   - 进入 `System Core` -> `RCC`。
   - `High Speed Clock (HSE)` 选择 **`Crystal/Ceramic Resonator`**（外部晶振）。
3. **GPIO 与外设配置**：
   - 例如点击 `PC13` 引脚，设置为 `GPIO_Output`，并在配置中设置 Label 为 `LED0`。
   - 进入 `Connectivity` -> `USART1`，Mode 选择 `Asynchronous`（异步模式，TX: PA9, RX: PA10）。

---

### 3. 时钟树配置 (Clock Tree)
1. 切换到 **Clock Configuration** 标签页。
2. 将 `Input frequency` 设为 `8` (MHz)。
3. 在 `PLL Source Mux` 选择 `HSE`，`PLLMul` 选 `*9`。
4. `System Clock Mux` 选择 `PLLCLK`。
5. 在 `HCLK (MHz)` 输入框直接填入 **`72`** 并按回车，CubeMX 将自动计算并配置所有分频器。

---

### 4. 工程管理器关键设置 (Project Manager - 核心避坑点)

在点击生成代码前，进入 **Project Manager** 标签页进行如下设置：

#### (1) Project 选项卡
- **Project Name**：建议填写 `STM32F103_Cube`。
- **Toolchain / IDE**：
  - **选项 A (推荐)**：选择 **`CMake`**（新版 CubeMX 6.8+ 原生支持直接生成 CMakeLists.txt）。
  - **选项 B**：选择 **`Makefile`** 或 **`STM32CubeIDE`**。

#### (2) Code Generator 选项卡 (至关重要)
- **STM32Cube MCU packages**：选择 `Copy only the necessary library files`（仅拷贝用到的库文件，保持轻量）。
- **Generated files**：
  -  勾选 **`Generate peripheral initialization as a pair of '.c/.h' files per peripheral`**（将每个外设的初始化代码独立生成为 `gpio.c/h`, `usart.c/h`，避免全部挤在 `main.c` 中）。
  -  勾选 **`Keep User Code when re-generating`**（重新生成时保留 `USER CODE BEGIN` 与 `USER CODE END` 之间的手写代码）。

---

## 二、如何与本工程的模块化架构完美结合？

推荐采用 **“CubeMX 负责外设引脚底层，BSP/App 负责业务调用”** 的分层模式：

```mermaid
graph TD
    CubeMX[STM32CubeMX (.ioc 文件)] -->|生成代码| CubeGen[Core/ 与 Drivers/HAL 源码]
    
    CubeGen -->|提供底层外设句柄| BSP[bsp/ 板级支持包]
    BSP -->|封装硬件接口| App[app/ 业务逻辑层]

    App --> MainApp[main.c 统一调度]
    Kconfig[Kconfig / menuconfig] -->|宏开关| BSP
    Kconfig -->|宏开关| App
```

### 1. 代码迁移与文件归属
CubeMX 生成的代码中：
- **`Drivers/STM32F1xx_HAL_Driver`**：官方 HAL 库，可直接放入本工程的 `drivers/STM32F1xx_HAL_Driver/`。
- **`Core/Src/gpio.c`, `usart.c` 等**：外设硬件引脚配置函数（如 `MX_GPIO_Init()`, `MX_USART1_UART_Init()`），直接放入 `bsp/` 对应驱动模块中调用。
- **`Core/Src/stm32f1xx_it.c`**：中断服务函数，按需合并至 `drivers/` 或 `bsp/`。
- **`Core/Src/system_stm32f1xx.c`**：时钟初始化，直接替换 `drivers/CMSIS/` 下的文件。

### 2. 用户代码保护规范
在修改 CubeMX 生成的代码时，**务必将自己的逻辑写在专属标记区内**：
```c
/* USER CODE BEGIN 2 */
// 你的自定义初始化代码，如 BSP_Init()，重新生成时不会被覆盖
/* USER CODE END 2 */
```

---

## 三、一键开发工作流总结

1. **改引脚/外设**：双击打开工程中的 `.ioc` 文件 -> 在 CubeMX 中调整 -> 点击 `GENERATE CODE`。
2. **裁剪配置**：终端运行 `make menuconfig` 勾选所需 RTOS 与三方库。
3. **极速编译**：运行 `cmake --build build` 或 `make -j4`。
4. **烧录调试**：运行 `scripts\flash.bat`。
