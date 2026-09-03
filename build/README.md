# 本地构建入口

- `build.bat [preset]`：配置并构建；缺省为 `configured-debug`。
- `build.bat all`：执行 `CMakePresets.json` 中全部 12 个固定矩阵构建。
- `clean.bat [preset]`：删除一个构建目录；缺省或 `all` 删除 `build/out`。

预设命名规则为：

```text
<bluepill|atk-elite>-<baremetal|rtthread|freertos>-<debug|release>
```

`configured-debug` 读取根目录本地 `.config`；当它不存在时使用 BluePill 裸机
defconfig。生成配置和固件全部位于 `build/out/<preset>/`。

产品配置职责见 [product/README](../product/README.md)，完整命令与发布检查见
[CMake + Ninja 构建指南](../docs/porting_guides/01_cmake_ninja_setup.md)。
