# LwIP 轻量级 TCP/IP 协议栈

## 仓库说明
LwIP 是专门为嵌入式系统设计的轻量级开源 TCP/IP 协议栈，广泛应用于物联网、工业网关与智能设备。

## 源码拉取指南
推荐直接拉取官方稳定版到 `src` 文件夹：
```bash
git clone -b STABLE-2_1_3_RELEASE https://git.savannah.nongnu.org/git/lwip.git third_party/lwip/src
```

## STM32F103 适配说明
- **硬件搭配**：SPI 以太网控制器（如 **ENC28J60**、**W5500**）或串口 PPP 拨号模块。
- **架构适配**：`arch/` 目录下已预置好 GCC Cortex-M3 的 `cc.h`、`perf.h` 及裁剪后的 `lwipopts.h`。
- **构建管理**：在 `menuconfig` -> `Third-Party Libraries` 中勾选 `Enable LwIP` 即可自动参与编译。
