# 04 - Kconfig 产品与系统配置指南

## 配置流

```text
Kconfig + product profile
          │ menuconfig
          ▼
   local .config              committed product/*/configs/*_defconfig
          └──────────────┬─────────────────────────┘
                         │ CMake configure
                         ▼
             build/out/<preset>/generated/
                 autoconf.h + kconfig.cmake
```

`.config` 是开发者本地选择，不提交版本库。产品目录下的六份 defconfig 是自动
回归和发布构建输入。CMake 生成文件留在单独构建目录，多个配置可以并行存在。

## 使用 menuconfig

```bash
python scripts/menuconfig.py
# Windows 也可运行 scripts\menuconfig.bat
# GNU Make 包装：make menuconfig
```

选择顺序为：

1. `Product Board Selection`：BluePill C8 或正点原子精英 ZE。
2. `Operating System (RTOS) Selection -> RTOS Mode`：裸机、RT-Thread Nano 或
   FreeRTOS。
3. 应用、BSP 和所选 RTOS 参数。

BluePill 没有板载用户按键，因此其按键选项不可选。产品选择同时确定 MCU 宏、
时钟、存储容量、链接参数和板级资源，不能再独立选择不匹配的芯片。

## 构建当前配置与固定配置

```bash
# 当前 .config；没有时回退到 BluePill 裸机默认配置
cmake --preset configured-debug
cmake --build --preset configured-debug

# 固定可复现配置
cmake --preset atk-elite-freertos-debug
cmake --build --preset atk-elite-freertos-debug
```

`build/build.bat all` 或 `python scripts/build_matrix.py` 会构建两个产品、三个系统
的 Debug/Release 共 12 个镜像。

## 新增选项规则

- Kconfig 名称经 `autoconf.h` 变成 `CONFIG_<NAME>` 宏。
- C/CMake 必须实际使用新增选项；不得保留无效果的菜单。
- CMake 使用目标级 `target_sources()`、`target_include_directories()` 和
  `target_link_libraries()`，禁止恢复全局宏或 `GLOB_RECURSE`。
- 新产品必须提供产品头、CMake 元数据和三种系统 defconfig，并通过完整矩阵。
