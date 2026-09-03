# 项目文档导航

本导航描述当前 `product + platform + CMake` 架构下的真实工程状态。`board_resources/`
中的教程摘录、历史移植资料和 ST 官方文档只用于理解原理，不能替代当前工程的
Kconfig、CMake、产品配置和 `platform/` 实现。

---

## 一、按角色选择入口

| 你的目标 | 从哪篇开始 | 后续阅读 |
| --- | --- | --- |
| 第一次构建并烧录 | [根 README](../README.md) | [CMake + Ninja 构建](porting_guides/01_cmake_ninja_setup.md) → [SOP-08 烧录调试](SOP_development_standard_procedure.md#sop-08硬件烧录j-link-在线仿真与排错) |
| 理解分层与设计约束 | [固件架构与配置边界](architecture.md) | [产品板级配置](../product/README.md) |
| 改配置、加功能 | [Kconfig/menuconfig 指南](porting_guides/04_kconfig_menuconfig_guide.md) | [开发标准作业程序](SOP_development_standard_procedure.md) |
| 新增产品或 BSP | [SOP-04 外设与 BSP 规范](SOP_development_standard_procedure.md#sop-04新增外设模块与-bsp-驱动开发规范) | [产品板级配置](../product/README.md) → [CubeMX 对接](porting_guides/05_stm32cubemx_integration_guide.md) |
| 维护 RTOS 端口 | [RT-Thread Nano 端口](porting_guides/02_rt_thread_nano_porting.md) | [FreeRTOS 端口](porting_guides/03_freertos_porting.md) |
| 引入第三方组件 | [SOP-06 第三方库引入](SOP_development_standard_procedure.md#sop-06第三方开源库-lwipcjsonrtt-引入与调用) | [lwIP 移植参考](porting_guides/06_lwip_porting_sop.md) |
| 查硬件引脚与资料 | [硬件资料库](hardware/README.md) | [开发板资料](board_resources/README.md) |

---

## 二、当前工程文档

### 架构与配置

| 文档 | 用途 |
| --- | --- |
| [固件架构与配置边界](architecture.md) | 分层依赖、配置唯一来源、启动流程、SysTick 所有权、发布边界 |
| [产品板级配置](../product/README.md) | 产品目录职责、四类必备文件、新增产品流程 |
| [Kconfig/menuconfig 指南](porting_guides/04_kconfig_menuconfig_guide.md) | 产品与系统选择、defconfig、生成文件、新增选项规则 |

### 构建与运行

| 文档 | 用途 |
| --- | --- |
| [CMake + Ninja 构建](porting_guides/01_cmake_ninja_setup.md) | 工具链、preset、单配置/矩阵构建、产物与校验 |
| [本地构建入口](../build/README.md) | `build.bat` / `clean.bat` 用法与 preset 命名规则 |
| [RT-Thread Nano 端口](porting_guides/02_rt_thread_nano_porting.md) | 当前 RT-Thread 实现职责、扩展规则与验收 |
| [FreeRTOS 端口](porting_guides/03_freertos_porting.md) | 当前集成说明（含历史教程的原理参考） |

### 开发作业与集成

| 文档 | 用途 |
| --- | --- |
| [开发标准作业程序](SOP_development_standard_procedure.md) | SOP-01 ~ SOP-09：环境、配置、外设、RTOS、三方库、构建、烧录、提交 |
| [STM32CubeMX 对接](porting_guides/05_stm32cubemx_integration_guide.md) | 将生成结果审查后迁入产品/BSP/驱动层 |
| [lwIP 移植参考](porting_guides/06_lwip_porting_sop.md) | 尚未集成组件的历史参考与接入准入要求 |

---

## 三、关键流程图索引

流程图内嵌在各文档中，统一使用 Mermaid 绘制：

| 流程图 | 说明 | 位置 |
| --- | --- | --- |
| 分层依赖与配置注入 | 谁依赖谁、配置从哪来到哪去 | [架构 · 分层依赖](architecture.md#分层依赖与配置注入) |
| Kconfig → 固件数据流 | menuconfig、defconfig、autoconf 到 ELF/HEX/BIN | [架构 · 配置到固件](architecture.md#从配置到固件的数据流) |
| 上电启动流程 | 复位向量 → `main` → 三系统分支 → `App_Process` | [架构 · 启动流程](architecture.md#启动流程) |
| SysTick 与毫秒时基 | 三系统各自独占时基的实现方式 | [架构 · 时基所有权](architecture.md#时基所有权) |
| 构建与校验流程 | preset → configure → build → 链接后校验 | [01 · 构建流程](porting_guides/01_cmake_ninja_setup.md#5-构建与校验流程) |
| 配置选择与生成流程 | `.config` / defconfig 如何变成 `autoconf.h` | [04 · 配置流](porting_guides/04_kconfig_menuconfig_guide.md#配置流) |
| 标准作业主流程 | 从需求到合入的完整路径 | [SOP · 主流程](SOP_development_standard_procedure.md#标准作业主流程) |
| 新增 BSP 外设四步法 | 源码 → Kconfig → CMake → 验证矩阵 | [SOP-04](SOP_development_standard_procedure.md#sop-04新增外设模块与-bsp-驱动开发规范) |
| 烧录与在线调试流程 | 构建 → J-Link 烧录 → 串口/GDB 验证 → 排错 | [SOP-08](SOP_development_standard_procedure.md#sop-08硬件烧录j-link-在线仿真与排错) |
| 新产品接入流程 | Kconfig → 产品文件 → preset → 矩阵 → 实测 | [产品 README](../product/README.md#新增产品流程) |

---

## 四、资料与当前能力边界

- `board_resources/` 是正点原子教程摘要和实验迁移资料。其中的 MDK 工程、uC/OS、
  `SYSTEM` 目录、示例入口和 `delay.c`/`sys.h` 约定**不是**当前工程接口。
- `hardware/` 与 `st_official_docs/` 用于查证原理图、引脚和寄存器行为。
- `docs/ref_docs/` 中的 PDF 被 `.gitignore` 排除，只保留在本地。
- `third_party/` 中的 cJSON、SEGGER RTT、lwIP、EasyLogger 和 Letter Shell 均为
  **不完整参考占位**，不出现在 menuconfig，也不参与固件构建。
- 当前可发布组合仅为两个产品 × 三种系统 × Debug/Release = **12 个 preset**。

---

## 五、文档与源码一致性规则

1. 文档描述的命令、目录或接口与源码冲突时，以 `CMakePresets.json`、顶层 `Kconfig`、
   `cmake/`、`product/`、`platform/` 的实现为准，并**同步修正文档**。
2. 默认行为（如 `.config` 缺失时的回退产品）以 `cmake/stm32f103_options.cmake`
   为准，不在多篇文档里各自描述。
3. 教程类资料必须显式标注"历史参考/不可直接套用"，避免与当前实现混淆。
4. 新增或改动流程图时，同步更新本文档的流程图索引。
