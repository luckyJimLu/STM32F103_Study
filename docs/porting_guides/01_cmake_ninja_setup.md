# 01 - CMake + Ninja + GCC 嵌入式编译环境搭建实战

## 1. 为什么选择 CMake + Ninja 架构？
传统的 Keil MDK / IAR 属于专有 IDE，跨平台支持差、无法便捷接入 CI/CD，且工程文件与配置强耦合。
使用 **CMake + Ninja + arm-none-eabi-gcc** 可以带来以下核心优势：
1. **极速构建**：Ninja 基于 DAG 依赖图执行并行编译，秒级完成大型嵌入式工程构建。
2. **跨平台兼容**：在 Windows、macOS、Linux 下拥有一致的构建体验。
3. **宏与模块化管理**：通过 Kconfig 和目标级 CMake 配置管理产品、RTOS 与外设组件。
4. **易于自动化与集成**：无缝对接 VS Code、CLion 以及 GitHub Actions。

---

## 2. 工具链准备与环境安装 (Windows 环境)

### 必须工具列表
1. **GNU Arm Embedded Toolchain (`arm-none-eabi-gcc`)**
   - 推荐版本：10.3+ / 12.3+
   - 下载地址：[Arm GNU Toolchain Downloads](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads)
   - 验证命令：`arm-none-eabi-gcc -v`
2. **CMake (3.20+)**
   - 下载地址：[CMake Official](https://cmake.org/download/)
   - 验证命令：`cmake --version`
3. **Ninja 构建工具**
   - 下载地址：[Ninja Releases](https://github.com/ninja-build/ninja/releases)
   - 验证命令：`ninja --version`
4. **调试与烧录工具 (OpenOCD 或 pyOCD / J-Link)**
   - OpenOCD 官方构建版：`openocd -v`

> [!TIP]
> 建议将上述工具的 `bin` 路径均加入系统的 `PATH` 环境变量中。

---

## 3. 本工程 CMake 编译命令实战

### 方式一：使用 CMake Presets (推荐)
本工程根目录下已配置 `CMakePresets.json`：

```bash
# 1. 裸机 Debug 模式配置与编译
cmake --preset bluepill-baremetal-debug
cmake --build --preset bluepill-baremetal-debug

# 2. RT-Thread Nano 模式配置与编译
cmake --preset bluepill-rtthread-debug
cmake --build --preset bluepill-rtthread-debug

# 3. FreeRTOS 模式配置与编译
cmake --preset bluepill-freertos-debug
cmake --build --preset bluepill-freertos-debug
```

### 方式二：标准命令行手动配置
```bash
# 1. 生成构建配置 (指定 Ninja 与交叉工具链)
cmake -B build -G Ninja \
      -DCMAKE_TOOLCHAIN_FILE=cmake/arm-none-eabi-gcc.cmake \
      -DCMAKE_BUILD_TYPE=Debug \
      -DPROJECT_CONFIG_FILE=product/bluepill_f103c8/configs/baremetal_defconfig

# 2. 执行编译
cmake --build build

# 3. 查看输出产物
# 产物位于 build/STM32F103_Study.elf, .hex, .bin, .map
```
