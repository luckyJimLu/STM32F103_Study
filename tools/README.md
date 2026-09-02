# 🛠️ Tools 编译工具链与实用工具目录

本目录用于统一组织和放置本地嵌入式开发所需的 **编译工具链 (Toolchain)**、**构建工具 (Ninja/CMake)**、**调试烧录工具 (OpenOCD)** 以及 **代码格式化脚本**。

支持将绿色免安装版工具链直接解压到本目录中，实现工程与工具的“即开即用、随盘携带（便携化）”，无需污染全局操作系统环境变量。

---

## 📁 目录组织规划

```
tools/
├── env_setup.bat              # [Windows] 一键临时注入 tools 下所有工具到 PATH
├── env_setup.sh               # [Linux/macOS] 一键临时注入 tools 下所有工具到 PATH
├── toolchain/                 # ARM GCC 交叉编译工具链 (arm-none-eabi-gcc)
│   └── README.md              # 下载指引与目录规范
├── openocd/                   # OpenOCD 调试与烧录工具包
│   └── README.md
├── ninja/                     # Ninja 高速构建工具 (ninja.exe)
│   └── README.md
├── cmake/                     # CMake 便携版 (cmake.exe)
│   └── README.md
├── format/                    # 代码风格格式化工具
│   ├── .clang-format          # 嵌入式 C/C++ 统一代码风格定义
│   ├── format_code.bat        # Windows 一键批量格式化工程代码
│   └── format_code.sh         # Linux/macOS 批量格式化脚本
└── README.md                  # 本说明文档
```

---

## ⚡ 便携化工具链使用方法

### 1. 放入绿色版工具
- 将下载的 `arm-gnu-toolchain-*-arm-none-eabi` 解压至 `tools/toolchain/`（确保 `tools/toolchain/bin/arm-none-eabi-gcc` 存在）。
- 将 `ninja.exe` 放入 `tools/ninja/`。
- 将 `openocd` 放入 `tools/openocd/`。

### 2. 一键激活环境 (可选)
在终端中执行：
```cmd
:: Windows CMD
call tools\env_setup.bat

:: Linux / macOS Terminal
source tools/env_setup.sh
```

> **注**：工程的 `CMake` 和 `Makefile` 已内置智能检测逻辑：如果 `tools/toolchain/bin/` 下存在编译器，将**自动优先使用本地 tools 目录下的工具链**！
