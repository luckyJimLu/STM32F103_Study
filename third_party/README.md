# 📦 Third-Party 常用三方开源仓与组件库

本目录用于统一放置和管理嵌入式常用第三方开源库（如 **LwIP**、**cJSON**、**SEGGER_RTT**、**EasyLogger**、**Letter-Shell** 等）。

每个组件拥有独立的 `Kconfig`（支持 menuconfig 可视化裁剪）、`Make.defs`（支持 Make 构建）以及 `CMakeLists.txt`（支持 CMake+Ninja 构建）。

---

## 📁 组件清单与索引

| 组件名称 | 目录 | 作用说明 | 官方/开源仓库地址 |
| :--- | :--- | :--- | :--- |
| **cJSON** | [`cJSON/`](cJSON/) | 轻量级 C 语言 JSON 解析与生成库 | [DaveGamble/cJSON](https://github.com/DaveGamble/cJSON) |
| **LwIP** | [`lwip/`](lwip/) | 轻量级 TCP/IP 协议栈（适合有网卡如 ENC28J60/W5500/LAN8720） | [lwIP Gitlab](https://git.savannah.nongnu.org/git/lwip.git) |
| **SEGGER RTT** | [`segger_rtt/`](segger_rtt/) | 高速 J-Link/DAP RTT 调试打印（无需串口引脚） | [SEGGER RTT](https://wiki.segger.com/RTT) |
| **EasyLogger** | [`easylogger/`](easylogger/) | 超轻量级、高性能 C/C++ 日志库（支持颜色、过滤） | [Armink/EasyLogger](https://github.com/armink/EasyLogger) |
| **Letter Shell** | [`letter_shell/`](letter_shell/) | 嵌入式串口交互式命令行终端 | [NevermindZZT/letter-shell](https://github.com/NevermindZZT/letter-shell) |

---

## 🔧 使用与克隆说明

可通过 Git Submodule 或直接 Clone 方式将完整开源仓引入：
```bash
# 引入 cJSON 示例
git clone https://github.com/DaveGamble/cJSON.git third_party/cJSON/src

# 引入 LwIP 示例
git clone -b STABLE-2_1_3_RELEASE https://git.savannah.nongnu.org/git/lwip.git third_party/lwip/src
```

引入后在终端运行 `make menuconfig`（或 `python scripts/menuconfig.py`）即可在界面中勾选启用对应三方库！
