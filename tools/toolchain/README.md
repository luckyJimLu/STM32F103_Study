# ARM GNU Toolchain (编译工具链)

## 说明
用于存放 `arm-none-eabi-gcc` 交叉编译工具链。

## 推荐下载版本
- **版本**：Arm GNU Toolchain 10.3 / 12.3 / 13.2+
- **官方下载地址**：[Arm GNU Toolchain Downloads](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads)

## 目录组织要求
解压后需保证目录结构如下：
```
tools/toolchain/
├── bin/
│   ├── arm-none-eabi-gcc.exe (或 arm-none-eabi-gcc)
│   ├── arm-none-eabi-g++.exe
│   ├── arm-none-eabi-objcopy.exe
│   ├── arm-none-eabi-size.exe
│   └── ...
├── arm-none-eabi/
├── lib/
└── ...
```
> 工程构建系统检测到 `tools/toolchain/bin` 时会自动优先使用该路径下的编译器。
