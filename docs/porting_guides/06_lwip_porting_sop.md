# 06 - LwIP 协议栈移植标准作业程序 (SOP)

> 本文档基于《STM32F1 LWIP 开发手册 V1.2（ENC28J60版本）》整理，系统化总结了在 STM32F103 平台上基于 ENC28J60 网卡进行 LwIP 移植的标准流程。涵盖**无操作系统（裸机 RAW API）**与**带操作系统（UCOS-II / FreeRTOS 架构移植）**两种方案。

> [!IMPORTANT]
> 本仓库当前没有可构建的 lwIP：`third_party/lwip` 只有体系结构参考头，缺少协议
> 栈源码、网卡驱动、许可证核对和三系统端口，因此 menuconfig 中没有 lwIP 选项。
> 下文是基于 lwIP 1.4.1/旧版例程的历史参考，不是当前工程已支持能力。

## 接入当前架构前的准入条件

正式接入时应固定仍受维护的 lwIP 2.1.x 版本并保留许可证，不修改或重命名上游
`src/core/sys.c`、`lwip/sys.h` 等文件。通过正确的 include 路径和目标级源码清单
解决同名文件问题，并按以下边界集成：

- 产品相关的 ENC28J60/SPI/EXTI 引脚和能力写入 `product/*`；
- SPI 与网卡硬件驱动放入 `drivers`/`bsp`，协议栈及许可证放入 `third_party/lwip`；
- 裸机 RAW API 轮询、RT-Thread `sys_arch`、FreeRTOS `sys_arch` 分别由
  `platform` 选择，应用层只调用统一网络服务接口；
- 新 Kconfig 选项必须依赖产品硬件能力和可用系统，CMake 显式列出源码；
- 为两个产品明确内存预算，完成编译矩阵、静态分析、收发/Ping/DHCP 和长时间
  压力测试后，才可把 lwIP 标记为可选功能。

---

## 历史教程内容（不可直接用于当前工程）

## 一、 移植前准备工作

### 1. 硬件连接与引脚定义
ENC28J60 是一款带有 SPI 接口的独立以太网控制器，硬件引脚一般占用如下信号（以常用开发板 NRF24L01 / SPI 扩展座为例）：

| 引脚名称 | STM32F103 引脚（以精英板为例） | 接口功能说明 |
| :--- | :--- | :--- |
| **VCC / GND** | 3.3V / GND | 供电电源（ENC28J60 为 3.3V 供电） |
| **CS** | PB12 (NSS / GPIO) | SPI 片选信号（低电平有效） |
| **SCK** | PB13 (SPI2_SCK) | SPI 串行时钟线 |
| **MISO** | PB14 (SPI2_MISO) | SPI 主机输入 / 从机输出 |
| **MOSI** | PB15 (SPI2_MOSI) | SPI 主机输出 / 从机输入 |
| **RST** | PG7 (或专用 RST 引脚) | 硬件复位引脚（低电平复位，保持至少 10ms） |
| **INT** | PG6 (配置为 EXTI6 外部中断) | 中断请求引脚（低电平有效，用于接收与错误中断） |

### 2. 软件工程环境准备
1. **基础工程**：准备具备基本时钟配置、串口打印调试（USART1 115200bps）以及**动态内存管理机制（malloc / free）**的工程（可选配置 USMART 调试组件方便寄存器在线调试）。
2. **历史教程源码**（lwIP 1.4.1，仅用于理解下文例程）：
   - `lwip-1.4.1.zip`：包含协议栈核心源码（`core`、`api`、`include`、`netif`）。
   - `contrib-1.4.1.zip`：包含各平台移植参考范例与模板头文件。

### 3. 文件目录规划
在工程根目录建立 `LWIP` 统一存放管理：
```text
LWIP/
├── lwip-1.4.1/              # LwIP 官方源码
│   └── src/
│       ├── api/             # 高层接口 (Sequential API / Sockets)
│       ├── core/            # 内核源码 (TCP/UDP/IP/ARP/DHCP/内存堆栈)
│       │   └── ipv4/        # IPv4 协议实现
│       ├── include/         # LwIP 头文件
│       └── netif/           # 网络接口层驱动支持
├── arch/                    # 平台体系结构抽象层
│   ├── cc.h                 # 数据类型定义、编译器对齐与临界保护宏
│   ├── cpu.h                # 字节序定义 (大小端)
│   ├── perf.h               # 系统统计与性能测量宏
│   ├── sys_arch.h           # OS 适配类型定义与系统时间获取
│   └── sys_arch.c           # OS 信号量、邮箱、线程封装接口
└── lwip_app/
    └── lwip_comm/           # 用户集成封装层
        ├── lwip_comm.c      # 网卡与协议栈初始化、定时器与轮询处理
        ├── lwip_comm.h      # 开发者数据结构与接口声明
        └── lwipopts.h       # 协议栈核心配置文件 (裁剪与参数调优)
```

---

## 二、 阶段一：网卡驱动实现与验证 (ENC28J60)

1. **添加驱动源码**：将 `enc28j60.c` 与 `enc28j60.h` 添加入工程 `HARDWARE` 分组中。
2. **核心驱动函数列表**：
   - `ENC28J60_Init()`：初始化 SPI 接口时钟与引脚模式，复位芯片，配置 MAC/PHY 寄存器，设定接收过滤器与收发缓冲区边界。
   - `ENC28J60_Packet_Send(len, packet)`：关中断下将数据帧写入 ENC28J60 发送缓存并启动发送。
   - `ENC28J60_Packet_Receive(maxlen, packet)`：从接收缓存提取数据帧并返回实际长度。
   - `ENC28J60_ISRHandler()`：网卡中断处理函数，当检测到 `EIR_PKTIF` 标志时调用 `lwip_pkt_handle()`。
   - `EXTI9_5_IRQHandler()`：外部中断线服务函数，检测到 INT 引脚低电平时调用 `ENC28J60_ISRHandler()`。
3. **驱动自检**：在初始化后读取 `ENC28J60_Get_EREVID()` 版本号，若版本非 0 / 非 0xFF 则表明 SPI 物理通信正常。

---

## 三、 阶段二：源码重命名与工程分组添加

### 1. 规避同名文件冲突（历史做法说明）
旧教程建议重命名 `sys.c` / `sys.h` 并全局修改上游源码。当前工程不得采用这种
做法：保留官方目录结构和 `#include "lwip/sys.h"`，由 CMake 目标的 include 路径
隔离同名文件。这样才能升级上游版本并审计补丁。

### 2. Keil / CMake 工程分组配置
- **`LWIP-NETIF`**：
  - `src/netif/etharp.c`
  - `src/netif/ethernetif.c`
- **`LWIP-CORE`**：
  - `src/core/` 下的 `.c` 文件（`mem.c`、`memp.c`、`netif.c`、`pbuf.c`、`raw.c`、`tcp.c`、`tcp_in.c`、`tcp_out.c`、`udp.c`、`init.c`、`def.c`、`dhcp.c`、`timers.c` 等）。
  - `src/core/ipv4/` 下的 `.c` 文件（`autoip.c`、`icmp.c`、`igmp.c`、`inet.c`、`inet_chksum.c`、`ip.c`、`ip_addr.c`、`ip_frag.c` 等）。
- **`LWIP-ARCH`**：
  - `arch/sys_arch.c`
- **`LWIP-API`**（仅在带 OS 方案中编译添加）：
  - `src/api/` 下的所有文件（`api_lib.c`、`api_msg.c`、`err.c`、`netbuf.c`、`netdb.c`、`netifapi.c`、`sockets.c`、`tcpip.c` 等）。
- **`LWIP_APP`**：
  - `lwip_app/lwip_comm/lwip_comm.c`

### 3. 头文件包含路径 (Include Paths)
```text
LWIP/
LWIP/arch
LWIP/lwip-1.4.1/src/include
LWIP/lwip-1.4.1/src/include/ipv4
LWIP/lwip-1.4.1/src/include/netif
LWIP/lwip_app/lwip_comm
```

---

## 四、 阶段三：接口适配层与源码调整

### 1. 体系结构配置 (`arch/`)
* **`cpu.h`**：STM32 Cortex-M3 为小端模式：
  ```c
  #define BYTE_ORDER LITTLE_ENDIAN
  ```
* **`cc.h`**：定义协议栈所需数据宽度及编译器属性：
  ```c
  typedef unsigned char   u8_t;
  typedef signed char     s8_t;
  typedef unsigned short  u16_t;
  typedef signed short    s16_t;
  typedef unsigned long   u32_t;
  typedef signed long     s32_t;
  typedef u32_t           mem_ptr_t;
  typedef int             sys_prot_t;

  #if defined (__CC_ARM)
    #define PACK_STRUCT_BEGIN __packed
    #define PACK_STRUCT_STRUCT
    #define PACK_STRUCT_END
    #define PACK_STRUCT_FIELD(x) x
  #elif defined (__GNUC__)
    #define PACK_STRUCT_BEGIN
    #define PACK_STRUCT_STRUCT __attribute__ ((__packed__))
    #define PACK_STRUCT_END
    #define PACK_STRUCT_FIELD(x) x
  #endif
  ```
* **`perf.h`**：测量与统计宏保持为空宏定义。

### 2. 网卡适配层接口实现 (`ethernetif.c`)
在 `ethernetif.c` 中完善 5 个核心对接函数：
1. **`low_level_init(netif)`**：
   - 设置 MAC 地址（`netif->hwaddr`）与硬件地址长度（`ETHARP_HWADDR_LEN = 6`）。
   - 设定 MTU 为 1500。
   - 配置接口标志位：`NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_LINK_UP`。
2. **`low_level_output(netif, p)`**：
   - 将传入的 `pbuf` 数据链表拼接拷贝至发送缓冲区临时内存；
   - 调用 `ENC28J60_Packet_Send(p->tot_len, buffer)` 发送数据帧；
   - 释放临时内存，返回 `ERR_OK`。
3. **`low_level_input(netif)`**：
   - 申请临时缓冲区并调用 `ENC28J60_Packet_Receive(MAX_FRAMELEN, buffer)` 读取报文；
   - 调用 `pbuf_alloc(PBUF_RAW, len, PBUF_POOL)` 申请 LwIP 的 pbuf 结构；
   - 将数据拷贝至 `pbuf->payload` 链表并返回 pbuf 指针。
4. **`ethernetif_input(netif)`**：
   - 接收低层返回的 `pbuf`，并调用 `netif->input(p, netif)` 送往协议栈网络层。
5. **`ethernetif_init(netif)`**：
   - 绑定底层回调：`netif->output = etharp_output`、`netif->linkoutput = low_level_output`；
   - 调用 `low_level_init(netif)` 初始化硬件。

### 3. 内存管理对接（优化 SRAM 占用）
LwIP 默认会在静态区分配大数组 `ram_heap` 和 `memp_memory`，为节省片上紧张的 SRAM：
1. **`mem.c`**：将 `u8_t ram_heap[...]` 数组屏蔽，改为指针定义：`u8_t *ram_heap;`。
2. **`memp.c`**：将 `static u8_t memp_memory[...]` 数组屏蔽，改为指针定义：`u8_t *memp_memory;`。
3. **`memp.c` 中添加尺寸计算函数**：
   ```c
   u32_t memp_get_memorysize(void) {
       u32_t length = 0;
       length = (MEM_ALIGNMENT - 1
       #define LWIP_MEMPOOL(name,num,size,desc) +((num)*(MEMP_SIZE+MEMP_ALIGN_SIZE(size)))
       #include "lwip/memp_std.h"
       );
       return length;
   }
   ```
4. **统一在 `lwip_comm_mem_malloc()` 中分配**：
   在系统初始化时，通过自建堆管理（`mymalloc`）为 `ram_heap` 和 `memp_memory` 统一申请堆内存，并在退出时释放。

### 4. ICMP 校验和兼容 (`icmp.c`)
如果底层网卡不具备硬件校验或驱动不支持，需保证在 ICMP 回显响应中正常计算校验和，屏蔽冲突代码。

---

## 五、 阶段四：无操作系统（裸机 RAW API）移植 SOP

### 1. 配置 `lwipopts.h`
```c
#ifndef __LWIPOPTS_H__
#define __LWIPOPTS_H__

#define SYS_LIGHTWEIGHT_PROT   0               // 裸机关闭轻量级保护
#define NO_SYS                 1               // 开启无操作系统模式
#define MEM_ALIGNMENT          4               // 4 字节对齐
#define MEM_SIZE               (10 * 1024)     // 内存堆大小 10KB
#define MEMP_NUM_PBUF          10              // memp pbuf 块数
#define PBUF_POOL_SIZE         10              // pbuf 内存池数量
#define PBUF_POOL_BUFSIZE      1500            // 每个 pbuf 大小

#define LWIP_TCP               1               // 使能 TCP
#define TCP_TTL                255
#define TCP_QUEUE_OOSEQ        0
#define TCP_MSS                (1500 - 40)
#define TCP_SND_BUF            (4 * TCP_MSS)
#define TCP_WND                (2 * TCP_MSS)

#define LWIP_UDP               1               // 使能 UDP
#define UDP_TTL                255
#define LWIP_ICMP              1               // 使能 Ping 功能
#define LWIP_DHCP              1               // 使能 DHCP 动态分配

#define LWIP_NETCONN           0               // 裸机禁用 NETCONN
#define LWIP_SOCKET            0               // 裸机禁用 SOCKET
#define LWIP_STATS             0               // 关闭统计功能

#endif
```

### 2. 硬件时钟基准提供
* 配置 STM32 硬件通用定时器（例如 TIM3）为 **10ms 定时周期**。
* 在中断服务程序中累计系统时间：
  ```c
  void TIM3_IRQHandler(void) {
      if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET) {
          lwip_localtime += 10; // 全局时基递增 10ms
          TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
      }
  }
  ```
* 在 `arch/sys_arch.h` 中实现：
  ```c
  u32_t sys_now(void) { return lwip_localtime; }
  ```

### 3. 内核轮询机制 (`lwip_periodic_handle`)
协议栈各模块要求严格的周期时钟驱动：
- **TCP 定时器**（每 250ms）：`tcp_tmr()`
- **ARP 定时器**（每 5s）：`etharp_tmr()`
- **DHCP 定时器**（每 500ms 细定时器、每 60s 粗定时器）
- 必须在主函数 `while(1)` 循环中持续轮询调用 `lwip_periodic_handle()`。

### 4. 裸机主程序流程 (`main.c`)
```c
int main(void) {
    // 1. 硬件基础外设初始化 (串口/时钟/按键/LED/内存池)
    bsp_init();
    TIM3_Int_Init(1000, 719); // 100Hz = 10ms

    // 2. 协议栈初始化
    while (lwip_comm_init() != 0) {
        printf("LwIP Init Failed, retrying...\r\n");
        delay_ms(1000);
    }

    // 3. DHCP 状态等待 (若开启 DHCP)
    #if LWIP_DHCP
    while ((lwipdev.dhcpstatus != 2) && (lwipdev.dhcpstatus != 0xFF)) {
        lwip_periodic_handle();
    }
    #endif

    // 4. 初始化应用功能 (如 UDP/TCP 客户端/Web Server)
    udp_demo_test();

    // 5. 主事件循环
    while (1) {
        lwip_periodic_handle(); // 处理内核定时任务
        // 外部中断在接收报文时会自动调用 lwip_pkt_handle()
    }
}
```

---

## 六、 阶段五：带操作系统（UCOS / FreeRTOS）移植 SOP

### 1. 配置 `lwipopts.h`
```c
#ifndef __LWIPOPTS_H__
#define __LWIPOPTS_H__

#define NO_SYS                       0         // 使能操作系统支持
#define SYS_LIGHTWEIGHT_PROT         1         // 开启轻量级临界区保护
#define MEM_ALIGNMENT                4
#define MEM_SIZE                     (6 * 1024)
#define MEMP_NUM_PBUF                16
#define PBUF_POOL_SIZE               20
#define PBUF_POOL_BUFSIZE            512

#define LWIP_NETCONN                 1         // 使能 Sequential API
#define LWIP_SOCKET                  1         // 使能 Socket API
#define LWIP_COMPAT_MUTEX            1
#define LWIP_SO_RCVTIMEO             1         // 开启接收超时避免线程永久挂起

// 操作系统线程与邮箱尺寸配置
#define TCPIP_THREAD_PRIO            5         // tcpip_thread 内核线程优先级
#define TCPIP_THREAD_STACKSIZE       1000      // 内核线程堆栈深度
#define TCPIP_MBOX_SIZE              20        // 消息邮箱大小
#define DEFAULT_TCP_RECVMBOX_SIZE    20
#define DEFAULT_ACCEPTMBOX_SIZE      20
#define DEFAULT_THREAD_STACKSIZE     512

#endif
```

### 2. 临界区对接 (`arch/cc.h`)
引入操作系统核心头文件，定义进入/退出临界区宏：
```c
#include "includes.h"

#if OS_CRITICAL_METHOD == 3
#define SYS_ARCH_DECL_PROTECT(lev)    u32_t lev
#define SYS_ARCH_PROTECT(lev)         lev = OS_CPU_SR_Save()
#define SYS_ARCH_UNPROTECT(lev)       OS_CPU_SR_Restore(lev)
#endif
```

### 3. 操作系统抽象层实现 (`arch/sys_arch.c` & `sys_arch.h`)
实现 LwIP 与 OS 之间的胶水层：
1. **数据结构定义**（`sys_arch.h`）：
   - 信号量：`typedef OS_EVENT *sys_sem_t;`
   - 互斥量：`typedef OS_EVENT *sys_mutex_t;`
   - 任务标识：`typedef INT8U sys_thread_t;`
   - 邮箱（封装为消息队列）：
     ```c
     typedef struct {
         OS_EVENT *pQ;
         void *pvQEntries[MAX_QUEUE_ENTRIES];
     } TQ_DESCR, *PQ_DESCR;
     typedef PQ_DESCR sys_mbox_t;
     ```
2. **核心接口实现**（`sys_arch.c`）：
   - **信号量**：`sys_sem_new()`、`sys_sem_signal()`、`sys_arch_sem_wait()`、`sys_sem_free()`。
   - **消息邮箱**：`sys_mbox_new()`、`sys_mbox_post()`、`sys_arch_mbox_fetch()`、`sys_mbox_free()`。注意在 `fetch` 函数中将 OS 节拍转换为毫秒，并在超时时正确返回 `SYS_ARCH_TIMEOUT`。
   - **内核线程创建**：`sys_thread_new()`，内部封装调用 `OSTaskCreate` 创建 `tcpip_thread` 内核任务。
   - **系统时钟**：`sys_now()`（将 OS Tick 转换为毫秒返回）。

### 4. 协议栈启动与任务流改造 (`lwip_comm.c`)
- **堆栈分配**：在 `lwip_comm_mem_malloc()` 中为 `TCPIP_THREAD_TASK_STK` 申请堆栈空间。
- **内核初始化**：将 `lwip_init()` 替换为调用 `tcpip_init(NULL, NULL)`，该函数内部自动创建 `tcpip_thread`。
- **网卡输入绑定**：将 `netif_add()` 的输入回调由 `ethernet_input` 替换为 `tcpip_input`。
- **DHCP 处理**：DHCP 过程从主循环中移出，改由独立任务（`lwip_dhcp_task`）处理，获取 IP 成功后调用任务自删除函数释放资源。

---

## 七、 阶段六：调试验证与排错清单

### 1. 验证步骤
1. **链路层确认**：网线插入交换机或电脑后，观察 ENC28J60 模块网口绿灯常亮，黄灯有偶发闪烁。
2. **IP 分配与静态配置检查**：
   - 若开启 DHCP，查看串口日志打印出的 IP 地址、网关及掩码。
   - 若直连电脑，将电脑以太网配置为固定 IP（如 `192.168.1.100`），确保与开发板处于同一网段。
3. **Ping 命令测试**：
   在 PC 命令行终端执行：
   ```cmd
   ping 192.168.1.30 -t
   ```
   * 观察回包延时（通常小于 2ms）且无丢包。
4. **应用协议通信验证**：
   - 打开网络调试助手，测试 UDP 回显或 TCP 客户端/服务器数据收发。

### 2. 常见问题排查手册 (Troubleshooting)

| 异常现象 | 排查方向 | 解决方案 |
| :--- | :--- | :--- |
| **`lwip_comm_init()` 返回 1** | 内存不足 | 检查 `MEM_SIZE` 和 `memp_get_memorysize()` 是否超出了 STM32 片内动态内存堆的可用大小，适当降低缓冲池大小。 |
| **`lwip_comm_init()` 返回 2** | ENC28J60 初始化失败 | 检查 SPI 引脚配置与接线、复位电平、SPI SCK 时钟分频（建议降至 9MHz 以下排查信号完整性问题）。 |
| **`lwip_comm_init()` 返回 3** | 网卡注册失败 | 检查 `netif_add` 传入的 IP/网关参数是否有效，检查 `ethernetif_init` 返回值。 |
| **能够 Ping 通但无法进行 TCP 通信** | MSS/滑动窗口设置不当 | 检查 `lwipopts.h` 中 `TCP_MSS`、`TCP_WND` 和 `TCP_SND_BUF` 的比例关系是否满足规范。 |
| **裸机运行一段时间后停止响应** | 定时器未调用或死循环阻断 | 检查主循环中是否存在长期阻塞的 `delay` 导致 `lwip_periodic_handle()` 未能如期执行；检查中断标志位是否清除。 |
| **OS 下接收阻塞无法退出** | 超时未使能 | 确保在 `lwipopts.h` 中定义了 `LWIP_SO_RCVTIMEO 1`，并为连接配置了 `conn->recv_timeout`。 |
