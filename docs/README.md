# 项目文档导航

本文档索引以当前 `product + platform + CMake` 架构为准。教程摘录和历史移植
资料只用于理解原理，不能替代当前工程的 Kconfig、CMake 和产品配置。

## 当前工程文档

| 文档 | 用途 |
| --- | --- |
| [固件架构与配置边界](architecture.md) | 分层依赖、配置来源、运行时和 SysTick 所有权 |
| [产品板级配置](../product/README.md) | 产品目录结构、配置职责与新增产品清单 |
| [开发标准作业程序](SOP_development_standard_procedure.md) | 新增产品、BSP、应用功能和第三方组件的工作流 |
| [CMake + Ninja 构建](porting_guides/01_cmake_ninja_setup.md) | 单配置、固定 preset 和完整矩阵构建 |
| [RT-Thread Nano 端口](porting_guides/02_rt_thread_nano_porting.md) | 当前 RT-Thread 运行时实现与扩展边界 |
| [FreeRTOS 端口](porting_guides/03_freertos_porting.md) | 当前集成说明及历史移植参考 |
| [Kconfig/menuconfig](porting_guides/04_kconfig_menuconfig_guide.md) | 产品与系统选择、defconfig 和生成文件 |
| [STM32CubeMX 对接](porting_guides/05_stm32cubemx_integration_guide.md) | 将生成结果审查后迁入产品/BSP/驱动层 |
| [lwIP 移植参考](porting_guides/06_lwip_porting_sop.md) | 尚未集成组件的历史参考和准入要求 |
| [本地构建入口](../build/README.md) | Windows 批处理入口和 preset 命名 |

## 资料与当前能力边界

- `board_resources/` 是正点原子教程摘要和实验迁移资料，其中的 MDK、uC/OS、
  `SYSTEM` 目录及示例入口不是当前工程接口。
- `st_official_docs/`、芯片手册和原理图用于查证硬件与寄存器行为。
- `third_party/` 中的 cJSON、SEGGER RTT、lwIP、EasyLogger 和 Letter Shell
  当前都是不完整参考占位，不出现在 menuconfig，也不参与固件构建。
- 当前可发布组合仅为两个产品与裸机、RT-Thread Nano、FreeRTOS 三种系统组成的
  12 个 Debug/Release preset。

文档涉及的命令、目录或接口与源码不一致时，以 `CMakePresets.json`、顶层
`Kconfig`、`product/` 和 `platform/` 中的实现为最终依据，并同步修正文档。
