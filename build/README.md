# 本地构建入口

本目录只保留 Windows 批处理入口，构建产物与生成文件都写到 `build/out/` 下，
被 `.gitignore` 排除。

## 脚本

| 脚本 | 用法 | 说明 |
| --- | --- | --- |
| `_env.bat` | 由其他脚本调用 | 定位仓库内 CMake/Ninja，设置 `PROJECT_ROOT` |
| `build.bat [preset]` | `build\build.bat atk-elite-freertos-release` | 配置并构建；缺省 `configured-debug` |
| `build.bat all` | `build\build.bat all` | 执行 `scripts/build_matrix.py`，构建 12 个固定组合 |
| `clean.bat [preset]` | `build\clean.bat bluepill-baremetal-debug` | 删除一个构建目录；缺省或 `all` 删除整个 `build/out` |

## Preset 命名规则

```text
<bluepill|atk-elite>-<baremetal|rtthread|freertos>-<debug|release>
configured-debug
```

- 命名定义在 [`CMakePresets.json`](../CMakePresets.json)，共 12 个固定组合。
- `configured-debug` 读取仓库根 `.config`；**`.config` 不存在时回退到
  正点原子精英板 + 裸机 defconfig**（实现见 `cmake/stm32f103_options.cmake`）。
- 固定 preset 直接读取 `product/<product>/configs/<system>_defconfig`，可复现。

## 产物

```text
build/out/<preset>/
├── STM32F103_Study.elf / .hex / .bin / .map
├── generated/autoconf.h
├── generated/kconfig.cmake
└── generated/<product>.ld
```

每次链接后由 `scripts/check_firmware.py` 校验 Flash/RAM 容量、入口与 SysTick 符号
以及 RTOS 符号互斥性；任一失败即构建失败。

## 相关文档

- 命令细节与校验项：[CMake + Ninja 构建](../docs/porting_guides/01_cmake_ninja_setup.md)
- 产品配置职责：[product/README](../product/README.md)
- 烧录与调试：[SOP-08](../docs/SOP_development_standard_procedure.md#sop-08硬件烧录j-link-在线仿真与排错)
