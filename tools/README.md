# 🛠️ STM32F103 开发与编译环境软件清单及搭建指南

本文档汇总了本项目（基于 **CMake + Ninja + GNU Arm Toolchain + Kconfig** 现代构建架构）在开发、配置、编译、调试与烧录阶段所需要的**全套软件工具清单**与**环境搭建步骤**。

---

## 📋 软件清单总览 (Software Checklist)

| 分类 | 软件名称 | 推荐版本 | 用途说明 | 属性 | 官方下载地址 / 获取途径 |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **交叉编译器** | **GNU Arm Embedded Toolchain** | 10.3+ / 12.3+ / 13.x | ARM Cortex-M 交叉编译工具链 (`arm-none-eabi-gcc`) | **必装** | [Arm 官方下载中心](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads) |
| **构建配置** | **CMake** | 3.20 及以上 | 跨平台构建系统配置生成器 | **必装** | [CMake 官网](https://cmake.org/download/) |
| **构建执行器** | **Ninja** | 1.10 及以上 | 极速高并发底层构建引擎 | **必装** | [Ninja 官方 Release](https://github.com/ninja-build/ninja/releases) |
| **配置工具** | **Python 3** | 3.8 及以上 | 运行 Kconfig 图形化菜单 `menuconfig.py` 及脚本 | **必装** | [Python 官方下载](https://www.python.org/downloads/) |
| **配置依赖** | **kconfiglib** | 最新版本 | Kconfig 菜单解析与 `.config` 生成依赖包 | **必装** | `pip install kconfiglib windows-curses` |
| **调试与烧录** | **SEGGER J-Link** | V7.x 及以上 | 官方 J-Link 驱动套件 (`JLink.exe`, `JLinkGDBServerCL.exe`)，用于固件一键极速烧录与在线断点调试（**本项目默认使用**，无需额外安装 OpenOCD） | **必装/默认** | [SEGGER J-Link 官网下载](https://www.segger.com/downloads/jlink/) |
| **片上调试 (可选)** | **OpenOCD** | 0.11+ / 0.12+ | 开源片上调试器，若使用 ST-Link / DAP-Link 时可选安装（使用 J-Link 时无需安装） | 可选 | [OpenOCD Windows Builds](https://github.com/openocd-org/openocd/releases) |
| **固件工具** | **STM32CubeProgrammer** | 最新版 | ST 官方芯片烧录、读保护解除与 Option Byte 工具 | 可选 | [ST 官网 STM32CubeProg](https://www.st.com/en/development-tools/stm32cubeprog.html) |
| **代码格式化** | **LLVM (clang-format)** | 14.0 及以上 | 根据 `.clang-format` 规范统一代码格式 | 推荐 | [LLVM Releases](https://github.com/llvm/llvm-project/releases) |
| **串口调试助手** | **VOFA+ / MobaXterm** | 最新版 | 接收串口调试日志（115200 波特率）或波形可视化 | 推荐 | [VOFA+ 官网](https://www.vofa.plus/) |

---

## 💻 推荐 IDE / 编辑器与插件清单

### 方案 A：VS Code (最推荐)
1. **主程序**：[Visual Studio Code 官方下载](https://code.visualstudio.com/)
2. **必装扩展插件**：
   - **`C/C++`** (`ms-vscode.cpptools`)：C 语言智能补全、符号跳转与语法高亮。
   - **`CMake Tools`** (`ms-vscode.cmake-tools`)：自动识别 `CMakePresets.json`，支持一键点击状态栏配置与编译。
   - **`Cortex-Debug`** (`marus25.cortex-debug`)：ARM Cortex-M 芯片硬件断点、单步调试、外设寄存器查看。
   - **`Kconfig`** (`trond-snekvik.kconfig-lang`)：提供 `Kconfig` 语法高亮与语法检测。
   - **`Clang-Format`** (`xaver.clang-format`)：保存时自动按规范格式化代码。

### 方案 B：CLion (全功能一体化)
- 原生内置对 CMake、Ninja 及嵌入式 OpenOCD / GDB Server 的完善支持。

---

## 📥 环境安装与部署方式

本项目支持以下两种环境配置方式：

### 方式一：系统全局安装（推荐日常开发）

#### Windows 用户（推荐通过包管理器快速安装）
以管理员身份打开 PowerShell 执行：
```powershell
# 使用 Windows 官方包管理器 winget 一键安装常用开发套件
winget install Kitware.CMake
winget install Ninja-build.Ninja
winget install Git.Git
winget install Python.Python.3.11

# 安装 Python Kconfiglib 库 (Windows 上需附带 curses)
python -m pip install --upgrade pip
pip install kconfiglib windows-curses
```
> **注意**：`arm-none-eabi-gcc` 可从 [Arm 官网](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads) 下载 Windows Zip 或 exe 安装包，并将其 `bin` 目录添加到系统环境变量 `PATH`。

#### Linux (Ubuntu / Debian) 用户
```bash
sudo apt update
sudo apt install -y build-essential gcc-arm-none-eabi binutils-arm-none-eabi \
                    cmake ninja-build git python3 python3-pip openocd

# 安装 Kconfig 解析库
pip3 install kconfiglib
```

---

### 方式二：绿色免安装便携版（直接放入 `tools/` 目录）

本项目的构建脚本支持**零环境变量污染的便携化模式**。如果你的电脑无法修改系统全局环境变量，可直接将绿色版软件解压存放在 `tools/` 对应子目录中：

```
tools/
├── toolchain/
│   └── bin/
│       ├── arm-none-eabi-gcc.exe
│       ├── arm-none-eabi-g++.exe
│       └── ...
├── ninja/
│   └── ninja.exe
├── cmake/
│   └── bin/
│       └── cmake.exe
├── openocd/
│   └── bin/
│       └── openocd.exe
├── env_setup.bat              # [Windows] 一键将上述 tools 工具注册到当前终端 PATH
├── env_setup.sh               # [Linux/macOS] 一键将上述 tools 工具注册到当前终端 PATH
└── README.md
```

- **自动检测机制**：工程的 `cmake/arm-none-eabi-gcc.cmake` 会自动检测：如果 `tools/toolchain/bin` 存在，会优先使用该本地工具链，无需手动配 PATH！
- **终端手动激活**：
  ```cmd
  :: Windows CMD
  call tools\env_setup.bat
  ```

---

## 🩺 环境安装验证清单 (Verification)

在终端中逐项运行以下指令，确认各核心工具已正常响应：

| 验证项 | 验证命令 | 预期结果示例 |
| :--- | :--- | :--- |
| **交叉编译器** | `arm-none-eabi-gcc -v` | `gcc version 10.3.1` 或更高版本 |
| **构建管理** | `cmake --version` | `cmake version 3.20.0` 或更高版本 |
| **构建执行器** | `ninja --version` | `1.10.2` 或更高版本 |
| **Python** | `python --version` | `Python 3.8.x` 或更高版本 |
| **Kconfiglib** | `python -c "import kconfiglib; print('OK')"` | 终端打印 `OK` |
| **烧录工具** | `scripts\flash.bat` 或 `JLink.exe` | SEGGER J-Link Commander 正常启动并识别 |

---

## 🚀 快速上手编译

当上述清单工具准备完毕后，可在工程根目录直接执行：

```bash
# 1. 运行图形化配置菜单裁剪功能与外设
python scripts/menuconfig.py

# 2. 编译裸机版本
cmake --preset baremetal-debug
cmake --build --preset baremetal-debug

# 3. 编译 FreeRTOS 版本
cmake --preset freertos-debug
cmake --build --preset freertos-debug

# 4. 编译 RT-Thread Nano 版本
cmake --preset rtt-debug
cmake --build --preset rtt-debug
```
编译生成的 `.elf`、`.hex`、`.bin` 和 `.map` 镜像文件均存放在 `build/` 对应预设目录下。
