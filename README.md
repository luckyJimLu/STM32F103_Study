# STM32F103 多产品、三系统学习工程

同一套应用和 BSP 代码可由 menuconfig 组合为两种产品板和三种运行系统：

| 产品 | MCU | 板载资源 |
| --- | --- | --- |
| BluePill | STM32F103C8T6，64KB Flash/20KB SRAM | PC13 LED、USART1 PA9/PA10；无用户按键 |
| 正点原子精英板（默认） | STM32F103ZET6，512KB Flash/64KB SRAM | PB5/PE5 LED、PE4/PE3/PA0 按键、板载 USB 转串口（USART1 PA9/PA10） |

运行系统为裸机、RT-Thread Nano 3.1.5 或 FreeRTOS。产品和系统均通过
Kconfig choice 生成互斥宏，不需要修改业务源码。

## 架构

```text
product profile + autoconf
           ↓
CMSIS → compact HAL → BSP → application
                         ↖ system runtime port
                            ├─ bare-metal
                            ├─ RT-Thread Nano
                            └─ FreeRTOS
```

- `product/`：产品时钟、容量、引脚、链接参数和六份 defconfig。
- `platform/`：统一启动接口和三种系统端口，独占各自 SysTick。
- `app/`：不引用任何 RTOS 头文件的共享应用逻辑。
- `bsp/`：只使用产品资源宏，不判断芯片型号。
- `drivers/`：STM32CubeF1 v1.8.7 CMSIS 与精简 HAL。
- `middlewares/rtos/`：保持当前版本的 RT-Thread Nano 和 FreeRTOS。
- `third_party/`：未完成的参考占位，当前不参与配置或构建。

更完整的设计约束见 [架构说明](docs/architecture.md)，全部文档入口见
[项目文档导航](docs/README.md)。

## 配置

```bat
python scripts\menuconfig.py
```

保存后只更新本地 `.config`。它不会入库；可复现配置位于每个产品的
`configs/*_defconfig`。构建生成的 `autoconf.h` 位于各自构建目录，配置之间
不会互相覆盖。

## 构建

Windows 仓库内置 CMake、Ninja 和 GNU Arm Toolchain：

```bat
REM 使用当前 .config；没有 .config 时默认 正点原子精英板 F103ZE + 裸机
build\build.bat

REM 构建一个固定组合
build\build.bat bluepill-rtthread-debug
build\build.bat atk-elite-freertos-release

REM 两产品 × 三系统 × Debug/Release
build\build.bat all
```

GNU Make 仅是 CMake 的便捷包装，不再维护独立源码清单：

```bash
make menuconfig
make PRESET=atk-elite-baremetal-debug
make matrix
```

每次链接后自动检查产品 Flash/RAM 上限、入口/SysTick 符号以及 RTOS 互斥性。
ELF、HEX、BIN 和 MAP 输出到 `build/out/<preset>/`。

## 烧录与调试

本项目默认使用 **SEGGER J-Link** 进行固件烧录与在线调试（**无需安装 OpenOCD 或 ST-Link**）：

```bat
REM 默认构建并烧录 正点原子精英板 F103ZE 裸机固件
build\build.bat
scripts\flash.bat

REM 烧录指定预设构建固件
scripts\flash.bat atk-elite-baremetal-debug

REM 烧录当前 menuconfig 激活配置
scripts\flash.bat configured-debug
```

VS Code 原生支持 J-Link GDB Server 调试，按 `F5` 即以 `STM32F103ZE + SWD` 启动。板载 USB 转串口使用 `USART1`（PA9/PA10），串口参数为 `115200 8N1`；启动日志会打印产品、运行系统和实际系统时钟。串口在电脑上的 COM 号由 Windows 动态分配，请在设备管理器或串口工具中选择实际出现的端口。
