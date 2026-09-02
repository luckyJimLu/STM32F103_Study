# STM32F103 模块化嵌入式开发与实战工程

本项目是基于 **STM32F103**（支持 STM32F103C8T6 / STM32F103ZET6 等型号）搭建的现代化、标准化、模块化嵌入式实战工程。

工程支持 **Kconfig 图形化菜单配置 (menuconfig / guiconfig)**，采用 **CMake + Ninja** 与 **Make + Make.defs** 双重构建支持体系，支持通过宏控制在 **裸机 (Bare-metal)**、**RT-Thread Nano** 以及 **FreeRTOS** 系统之间无缝切换，并配备 **`tools/` 工具链**、**`third_party/` 常用三方开源仓** 以及规范的 **SOP 标准作业程序**。

---

## 📁 目录架构全景

```
STM32F103_Study/
├── .config                      # Kconfig 生成的当前工程配置
├── Kconfig                      # 顶级 Kconfig 菜单配置入口
├── Make.defs                    # 全局 Make 工具链与编译参数定义
├── Makefile                     # 顶级 Makefile (支持 make, make menuconfig, make flash)
├── CMakeLists.txt               # 顶级 CMake 构建入口 (自动联动 .config)
├── CMakePresets.json            # CMake 预设 (Ninja 快速编译)
├── .vscode/                     # VS Code 开发与一键编译/调试配置
├── cmake/                       # CMake 构建模块与工具链
├── tools/                       # 🛠️ 本地编译工具链与环境工具 (arm-none-eabi-gcc / openocd / ninja)
├── third_party/                 # 📦 常用第三方开源仓 (cJSON / LwIP / SEGGER RTT / EasyLogger / Letter Shell)
├── app/                         # 应用层业务代码 (Kconfig / Make.defs / CMakeLists.txt)
├── bsp/                         # 板级支持包 (Kconfig / Make.defs / CMakeLists.txt)
├── drivers/                     # 芯片底层驱动库 (CMSIS + HAL)
├── middlewares/                 # 中间件与操作系统层 (RT-Thread Nano / FreeRTOS)
├── linker/                      # 链接脚本 (STM32F103C8Tx_FLASH.ld / STM32F103ZETx_FLASH.ld)
├── scripts/                     # 脚本工具 (menuconfig, flash)
└── docs/                        # 📚 知识库与实战文档
    ├── SOP_development_standard_procedure.md # 🚀 嵌入式开发标准作业程序 (SOP)
    ├── hardware/                # 硬件原理图与最小系统设计指南
    ├── porting_guides/          # 移植与环境搭建手册
    │   ├── 01_cmake_ninja_setup.md
    │   ├── 02_rt_thread_nano_porting.md
    │   ├── 03_freertos_porting.md
    │   ├── 04_kconfig_menuconfig_guide.md
    │   └── 05_stm32cubemx_integration_guide.md
    └── st_official_docs/        # ST 官方核心参考文档索引 (RM0008, PM0056, DB2163 等)
```

---

## ⚡ 快速使用指南

### 1. 查阅标准作业程序 (SOP)
在开始开发或扩展模块前，强烈建议阅读：
👉 **[STM32F103 模块化嵌入式开发标准作业程序 (SOP)](docs/SOP_development_standard_procedure.md)**

### 2. 启动 menuconfig 进行功能裁剪
```bash
# 终端模式
python scripts/menuconfig.py
# 或
make menuconfig

# 图形窗口模式
python scripts/menuconfig.py --gui
# 或
make guiconfig
```

### 3. 编译项目 (CMake + Ninja 或 Make)
```bash
# CMake + Ninja 模式
cmake -B build -G Ninja
cmake --build build

# GNU Make 模式
make -j4
```

### 4. 一键烧录
```bash
scripts\flash.bat
# 或
make flash
```

---

## 📚 知识库导航
- **[🚀 模块化嵌入式开发标准作业程序 (SOP)](docs/SOP_development_standard_procedure.md)**
- [硬件原理图设计与最小系统指南](docs/hardware/schematics_guide.md)
- [01 - CMake + Ninja 编译环境搭建实战](docs/porting_guides/01_cmake_ninja_setup.md)
- [02 - RT-Thread Nano 移植手册与实战](docs/porting_guides/02_rt_thread_nano_porting.md)
- [03 - FreeRTOS 移植手册与实战](docs/porting_guides/03_freertos_porting.md)
- [04 - Kconfig 可视化裁剪与 Make.defs 构建描述层实战](docs/porting_guides/04_kconfig_menuconfig_guide.md)
- [05 - STM32CubeMX 图形化配置与代码生成对接实战](docs/porting_guides/05_stm32cubemx_integration_guide.md)
- [ST 官方核心参考手册与简报索引](docs/st_official_docs/README.md)
