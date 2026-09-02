# STM32F103 实验到 RTOS 迁移 Map

## 1. 结论

可行。《STM32F1开发指南（精英版）- HAL库版本 V1.2》 的 47 个实验都能在 RTOS 上实现，其中 GPIO、UART、定时器、ADC/DMA、CAN 等可直接任务化；单总线时序、软件 I2C、电容触摸、看门狗、低功耗、文件系统、USB MSC、IAP 和摄像头需要改变原裸机组织方式，不能只把 `while(1)` 原样塞进多个任务。

推荐目标不是“每个实验一个永久任务”，而是把实验沉淀成驱动和服务，再由应用组合：

```text
应用/UI任务
   |  命令、事件、数据
   v
设备服务任务（串口、显示、传感器、存储、USB/网络）
   |  互斥总线、DMA缓冲、状态机
   v
HAL/BSP 驱动
   ^
   |  极短 ISR：清标志、时间戳、通知
硬件外设
```

## 2. 全部实验映射

页码和实验边界来自原书目录及正文。详细步骤见每行链接的 SOP。

| 章 | 实验 | 主要硬件/外设 | 建议执行上下文 | RTOS 适配 |
| ---: | --- | --- | --- | --- |
| 6 | [跑马灯](sops/SOP-06-led-marquee.md) | DS0/PB5、DS1/PE5，GPIO | 周期或事件任务 | 直接适合 |
| 7 | [蜂鸣器](sops/SOP-07-buzzer.md) | 有源蜂鸣器/PB8，GPIO | 周期或事件任务 | 直接适合 |
| 8 | [按键输入](sops/SOP-08-key-input.md) | KEY0/PE4、KEY1/PE3（低有效），KEY_UP/PA0（高有效） | 周期或事件任务 | 直接适合 |
| 9 | [串口通信](sops/SOP-09-uart.md) | USART1/PA9(TX)、PA10(RX)，P3 跳帽，DS0 | 周期或事件任务 | 直接适合 |
| 10 | [外部中断](sops/SOP-10-exti.md) | KEY0/PE4、KEY1/PE3、KEY_UP/PA0，EXTI | 短 ISR + 工作任务 | 直接适合 |
| 11 | [独立看门狗 IWDG](sops/SOP-11-iwdg.md) | IWDG、DS0、KEY_UP | 监督任务 | 适合但需改造 |
| 12 | [窗口看门狗 WWDG](sops/SOP-12-wwdg.md) | WWDG、DS0、DS1 | 监督任务 | 适合但需严谨设计 |
| 13 | [定时器中断](sops/SOP-13-timer-interrupt.md) | TIM3、DS0、DS1 | 短 ISR + 工作任务 | 直接适合 |
| 14 | [PWM 输出](sops/SOP-14-pwm.md) | TIM3_CH2，经部分重映射到 PB5/DS0 | 硬件触发 + 控制任务 | 直接适合 |
| 15 | [输入捕获](sops/SOP-15-input-capture.md) | TIM5_CH1/PA0，DS0；可将 PB5 PWM 接到 PA0 | 短 ISR + 工作任务 | 直接适合 |
| 16 | [电容触摸按键](sops/SOP-16-capacitive-touch.md) | TPAD、TIM5_CH2/PA1，P7 跳帽 | 周期或事件任务 | 适合但需时序隔离 |
| 17 | [OLED 显示](sops/SOP-17-oled.md) | OLED：CS/PD6、RST/PG15、RS/PD3、WR/PG14、RD/PG13，P4 接口 | UI/显示任务 | 直接适合 |
| 18 | [TFTLCD 显示](sops/SOP-18-tft-lcd.md) | 板载 LCD 接口、FSMC、背光 | UI/显示任务 | 适合但需资源规划 |
| 19 | [USMART 调试组件](sops/SOP-19-usmart.md) | USART1、TFTLCD、DS0/DS1 | 周期或事件任务 | 适合但需服务化 |
| 20 | [RTC 实时时钟](sops/SOP-20-rtc.md) | RTC、后备域、备份电池、TFTLCD | 周期或事件任务 | 直接适合 |
| 21 | [待机唤醒](sops/SOP-21-standby-wakeup.md) | PWR、KEY_UP/PA0、DS0、TFTLCD | 周期或事件任务 | 适合但需系统级改造 |
| 22 | [ADC](sops/SOP-22-adc.md) | ADC1_CH1/PA1，P7 ADC 跳帽，TFTLCD | 周期或事件任务 | 直接适合 |
| 23 | [内部温度传感器](sops/SOP-23-internal-temperature.md) | ADC 内部温度通道、TFTLCD | 周期或事件任务 | 直接适合 |
| 24 | [光敏传感器](sops/SOP-24-light-sensor.md) | 光敏输入 PF8/ADC3_IN6，TFTLCD | 周期或事件任务 | 直接适合 |
| 25 | [DAC](sops/SOP-25-dac.md) | DAC_OUT1/PA4，TFTLCD/示波器 | 硬件触发 + 控制任务 | 直接适合 |
| 26 | [DMA](sops/SOP-26-dma.md) | DMA、USART/内存缓冲、DS0 | 短 ISR + 工作任务 | 直接适合 |
| 27 | [IIC](sops/SOP-27-i2c-eeprom.md) | AT24C02，软件 IIC PB6/PB7 | 总线/传感服务 | 适合但需总线仲裁 |
| 28 | [SPI](sops/SOP-28-spi-flash.md) | SPI2/PB13、PB14、PB15，板载 SPI NOR Flash | 总线/传感服务 | 适合但需总线仲裁 |
| 29 | [RS485 通信](sops/SOP-29-rs485.md) | USART2/PA2、PA3，收发方向 PD7，RS485 接口 | 总线/传感服务 | 适合但需状态机 |
| 30 | [CAN 通信](sops/SOP-30-can.md) | CAN/PA11、PA12，收发器、终端电阻 | 短 ISR + 工作任务 | 直接适合 |
| 31 | [触摸屏](sops/SOP-31-touchscreen.md) | 电阻/电容触摸控制器、TFTLCD | UI/显示任务 | 直接适合 |
| 32 | [红外遥控](sops/SOP-32-infrared-remote.md) | 红外接收 PB9/TIM4_CH4 | 短 ISR + 工作任务 | 直接适合 |
| 33 | [DS18B20 温度传感器](sops/SOP-33-ds18b20.md) | 单总线 PG11、DS18B20 | 总线/传感服务 | 适合但需时序改造 |
| 34 | [DHT11 温湿度传感器](sops/SOP-34-dht11.md) | 单线 PG11、DHT11 | 总线/传感服务 | 适合但需时序改造 |
| 35 | [MPU6050 六轴传感器](sops/SOP-35-mpu6050.md) | I2C PB10/PB11，INT/PA4，AD0/PA15，ATK-MPU6050 | 总线/传感服务 | 适合但需资源规划 |
| 36 | [无线通信](sops/SOP-36-wireless.md) | NRF24L01：SPI2，CE/PG8、CSN/PG7、IRQ/PG6 | 短 ISR + 工作任务 | 适合但需总线仲裁 |
| 37 | [FLASH 模拟 EEPROM](sops/SOP-37-flash-eeprom.md) | STM32 内部 Flash | 存储/升级服务 | 适合但需事务化 |
| 38 | [摄像头](sops/SOP-38-camera.md) | OV7725 摄像头、P6、TFTLCD、FIFO/控制信号 | 短 ISR + 工作任务 | 可行但资源紧张 |
| 39 | [内存管理](sops/SOP-39-memory-management.md) | SRAM、内存池、TFTLCD/串口 | 周期或事件任务 | 适合但建议静态化 |
| 40 | [SD 卡](sops/SOP-40-sd-card.md) | 板载 SD 卡座/SDIO，KEY0、串口、TFTLCD | 短 ISR + 工作任务 | 适合但需块服务 |
| 41 | [FATFS 文件系统](sops/SOP-41-fatfs.md) | FATFS R0.11、SD 卡、SPI Flash、TFTLCD/串口 | 存储/升级服务 | 适合但需单一所有权 |
| 42 | [汉字显示](sops/SOP-42-chinese-display.md) | TFTLCD、中文字库、SPI Flash/SD | UI/显示任务 | 直接适合 |
| 43 | [图片显示](sops/SOP-43-picture-display.md) | TFTLCD、SD/SPI Flash、图片文件 | UI/显示任务 | 可行但资源紧张 |
| 44 | [照相机](sops/SOP-44-camera-photo.md) | 摄像头、TFTLCD、SD 卡、按键 | 存储/升级服务 | 可行但资源紧张 |
| 45 | [手写识别](sops/SOP-45-handwriting.md) | 触摸屏、TFTLCD、识别库/字库 | UI/显示任务 | 适合但需工作任务 |
| 46 | [T9 拼音输入法](sops/SOP-46-t9-input.md) | 触摸屏、TFTLCD、拼音/汉字词库 | UI/显示任务 | 适合但需异步查询 |
| 47 | [串口 IAP](sops/SOP-47-uart-iap.md) | USART、内部 Flash、Bootloader、应用分区 | 存储/升级服务 | 可行，建议与 RTOS 解耦 |
| 48 | [USB 虚拟串口](sops/SOP-48-usb-cdc.md) | USB FS/PA11、PA12，PC 主机 | 短 ISR + 工作任务 | 直接适合 |
| 49 | [USB 读卡器](sops/SOP-49-usb-msc.md) | USB FS、SD 卡、MSC 块接口 | 存储/升级服务 | 适合但需独占介质 |
| 50 | [uC/OS-II 实验 1：任务调度](sops/SOP-50-ucos-task-scheduling.md) | uC/OS-II、LED/按键/TFTLCD | RTOS 原生任务 | RTOS 原生实验 |
| 51 | [uC/OS-II 实验 2：信号量和邮箱](sops/SOP-51-ucos-semaphore-mailbox.md) | uC/OS-II、信号量、邮箱 | RTOS 原生任务 | RTOS 原生实验 |
| 52 | [uC/OS-II 实验 3：消息队列、信号量集和软件定时器](sops/SOP-52-ucos-queue-event-timer.md) | uC/OS-II、消息队列、事件/信号量集、软件定时器 | RTOS 原生任务 | RTOS 原生实验 |

## 3. 推荐实施波次

1. **基础 BSP**：统一时钟、GPIO、NVIC、日志、错误码、断言、微秒/毫秒时基和资源表。
2. **基础并发**：第 6～15 章，先完成 LED、蜂鸣器、按键、UART、EXTI、看门狗和定时器；建立任务、队列、互斥量和 ISR 通知规范。
3. **采集与波形**：第 16、22～26 章，形成 ADC/DMA、滤波和 PWM/DAC 的通用数据通道。
4. **总线与传感**：第 27～36 章，建立 I2C、SPI、UART/RS485、CAN 和传感器服务，解决共享总线与超时恢复。
5. **显示、时间与功耗**：第 17～21、31、42、45、46 章，统一 UI 事件流、显示所有权、RTC 和 suspend/resume。
6. **大数据与存储**：第 37～44、49 章，先做块设备和文件系统，再做图片、摄像头及 USB MSC；用有界缓冲和背压控制内存。
7. **升级与内核专题**：第 47、48、50～52 章，完成安全 IAP、USB CDC，并用后三个实验验证所选 RTOS 的核心原语。

## 4. RTOS 原语对照

SOP 使用的是抽象名称，可映射到不同内核：

| 意图 | FreeRTOS | RT-Thread | 使用原则 |
| --- | --- | --- | --- |
| 任务/线程 | `xTaskCreate` | `rt_thread_create` | 优先静态创建；记录栈高水位 |
| 消息队列 | `xQueue*` | `rt_mq_*` | 传值或传有明确所有权的缓冲 |
| 信号量 | `xSemaphore*` | `rt_sem_*` | 事件同步，不用于保护共享资源 |
| 互斥量 | Mutex API | `rt_mutex_*` | 保护总线/对象，利用优先级继承 |
| 事件组 | `xEventGroup*` | `rt_event_*` | 汇总多个健康位或系统状态 |
| 软件定时器 | `xTimer*` | `rt_timer_*` | 回调只通知，不做慢操作 |
| 任务延时 | `vTaskDelay/Until` | `rt_thread_mdelay` | 周期任务优先用绝对周期语义 |
| ISR 到任务 | FromISR API | `rt_*` 的中断安全调用 | ISR 只做最少工作，必要时触发调度 |

## 5. 必须提前定下的系统规则

- **中断优先级**：凡调用内核 API 的中断必须满足所选 RTOS 的优先级限制；NVIC 数值大小与逻辑优先级方向不要混淆。
- **时基**：明确 HAL tick 与 RTOS tick 的来源，避免两个 SysTick 处理互相覆盖；微秒时序使用独立硬件定时器。
- **单一所有权**：显示、UART TX、I2C、SPI、文件系统和 USB 存储应由服务任务独占，或至少以互斥量保护完整事务。
- **超时与恢复**：每次总线、队列、信号量和外设等待都设超时；记录超时、重试、溢出和复位原因。
- **内存**：F103 常见 SRAM 只有几十 KB；摄像头、图片、USB 和文件系统使用固定缓冲池、条带缓冲或零拷贝，禁止无界队列。
- **看门狗**：只有监督任务在所有关键任务都上报心跳后才能喂狗。
- **存储一致性**：Flash/FATFS 写入不在 ISR 中执行；进入待机、MSC 模式或升级前先同步并卸载。
- **时序型驱动**：DS18B20、DHT11、TPAD 和软件 I2C 使用硬件计时、输入捕获或很短的临界区，不允许长时间全局关中断。

## 6. 资源冲突清单

- PA0：KEY_UP、待机唤醒、TIM5_CH1 输入捕获。
- PA1：ADC1_CH1、TPAD/TIM5_CH2 相关实验。
- PA4：DAC 输出、MPU6050 中断信号。
- PA11/PA12：CAN 与 USB 共用，只能按构建或运行模式择一。
- PB5：DS0 与 TIM3_CH2 PWM 共用。
- PB13/PB14/PB15：SPI2 可能同时连接 Flash 和 NRF24L01，必须独立片选并仲裁总线。
- PG11：DS18B20 与 DHT11 单线实验共用。
- PA15：MPU6050 AD0 使用时需处理 JTAG 复用，建议保留 SWD 调试。

## 7. 推荐的项目目录

```text
bsp/                 # 时钟、GPIO、板级资源与引脚声明
drivers/             # 不依赖具体业务的设备驱动
services/            # uart、display、sensor、storage、watchdog 等单一所有者
app/                 # 状态机和业务任务
rtos_port/           # RTOS 原语适配与 ISR 通知封装
tests/               # 每个 SOP 对应的自检/失败注入用例
bootloader/          # 与主 RTOS 应用分离的 IAP
```

下一步建议先选择 FreeRTOS 或 RT-Thread，并以第 6、8、9、10、13 章作为第一条纵向切片：它们足以验证时基、任务、队列、ISR 通知、日志和资源分层是否正确。
