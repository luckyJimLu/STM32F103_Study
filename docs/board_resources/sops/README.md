# 实验 SOP 索引

本目录把 《STM32F1开发指南（精英版）- HAL库版本 V1.2》 第 6～52 章的 47 个实验逐一拆分为可执行 SOP。页码均指 PDF 页码。

使用顺序：先阅读上级目录中的 [实验到 RTOS 迁移 Map](../EXPERIMENT_RTOS_MAP.md)，再按依赖顺序执行单项 SOP。每份 SOP 都同时覆盖裸机复现、RTOS 改造和验收。

| 章 | 实验 SOP | PDF 页码 | RTOS 适配 |
| ---: | --- | ---: | --- |
| 6 | [跑马灯](SOP-06-led-marquee.md) | 140-155 | 直接适合 |
| 7 | [蜂鸣器](SOP-07-buzzer.md) | 156-160 | 直接适合 |
| 8 | [按键输入](SOP-08-key-input.md) | 161-166 | 直接适合 |
| 9 | [串口通信](SOP-09-uart.md) | 167-183 | 直接适合 |
| 10 | [外部中断](SOP-10-exti.md) | 184-190 | 直接适合 |
| 11 | [独立看门狗 IWDG](SOP-11-iwdg.md) | 191-196 | 适合但需改造 |
| 12 | [窗口看门狗 WWDG](SOP-12-wwdg.md) | 197-203 | 适合但需严谨设计 |
| 13 | [定时器中断](SOP-13-timer-interrupt.md) | 204-212 | 直接适合 |
| 14 | [PWM 输出](SOP-14-pwm.md) | 213-221 | 直接适合 |
| 15 | [输入捕获](SOP-15-input-capture.md) | 222-233 | 直接适合 |
| 16 | [电容触摸按键](SOP-16-capacitive-touch.md) | 234-242 | 适合但需时序隔离 |
| 17 | [OLED 显示](SOP-17-oled.md) | 243-259 | 直接适合 |
| 18 | [TFTLCD 显示](SOP-18-tft-lcd.md) | 260-287 | 适合但需资源规划 |
| 19 | [USMART 调试组件](SOP-19-usmart.md) | 288-299 | 适合但需服务化 |
| 20 | [RTC 实时时钟](SOP-20-rtc.md) | 300-316 | 直接适合 |
| 21 | [待机唤醒](SOP-21-standby-wakeup.md) | 317-324 | 适合但需系统级改造 |
| 22 | [ADC](SOP-22-adc.md) | 325-337 | 直接适合 |
| 23 | [内部温度传感器](SOP-23-internal-temperature.md) | 338-341 | 直接适合 |
| 24 | [光敏传感器](SOP-24-light-sensor.md) | 342-347 | 直接适合 |
| 25 | [DAC](SOP-25-dac.md) | 348-358 | 直接适合 |
| 26 | [DMA](SOP-26-dma.md) | 359-370 | 直接适合 |
| 27 | [IIC](SOP-27-i2c-eeprom.md) | 371-382 | 适合但需总线仲裁 |
| 28 | [SPI](SOP-28-spi-flash.md) | 383-394 | 适合但需总线仲裁 |
| 29 | [RS485 通信](SOP-29-rs485.md) | 395-403 | 适合但需状态机 |
| 30 | [CAN 通信](SOP-30-can.md) | 404-433 | 直接适合 |
| 31 | [触摸屏](SOP-31-touchscreen.md) | 434-458 | 直接适合 |
| 32 | [红外遥控](SOP-32-infrared-remote.md) | 459-468 | 直接适合 |
| 33 | [DS18B20 温度传感器](SOP-33-ds18b20.md) | 469-477 | 适合但需时序改造 |
| 34 | [DHT11 温湿度传感器](SOP-34-dht11.md) | 478-485 | 适合但需时序改造 |
| 35 | [MPU6050 六轴传感器](SOP-35-mpu6050.md) | 486-507 | 适合但需资源规划 |
| 36 | [无线通信](SOP-36-wireless.md) | 508-520 | 适合但需总线仲裁 |
| 37 | [FLASH 模拟 EEPROM](SOP-37-flash-eeprom.md) | 521-533 | 适合但需事务化 |
| 38 | [摄像头](SOP-38-camera.md) | 534-552 | 可行但资源紧张 |
| 39 | [内存管理](SOP-39-memory-management.md) | 553-563 | 适合但建议静态化 |
| 40 | [SD 卡](SOP-40-sd-card.md) | 564-582 | 适合但需块服务 |
| 41 | [FATFS 文件系统](SOP-41-fatfs.md) | 583-598 | 适合但需单一所有权 |
| 42 | [汉字显示](SOP-42-chinese-display.md) | 599-614 | 直接适合 |
| 43 | [图片显示](SOP-43-picture-display.md) | 615-628 | 可行但资源紧张 |
| 44 | [照相机](SOP-44-camera-photo.md) | 629-640 | 可行但资源紧张 |
| 45 | [手写识别](SOP-45-handwriting.md) | 641-652 | 适合但需工作任务 |
| 46 | [T9 拼音输入法](SOP-46-t9-input.md) | 653-665 | 适合但需异步查询 |
| 47 | [串口 IAP](SOP-47-uart-iap.md) | 666-680 | 可行，建议与 RTOS 解耦 |
| 48 | [USB 虚拟串口](SOP-48-usb-cdc.md) | 681-690 | 直接适合 |
| 49 | [USB 读卡器](SOP-49-usb-msc.md) | 691-697 | 适合但需独占介质 |
| 50 | [uC/OS-II 实验 1：任务调度](SOP-50-ucos-task-scheduling.md) | 698-711 | RTOS 原生实验 |
| 51 | [uC/OS-II 实验 2：信号量和邮箱](SOP-51-ucos-semaphore-mailbox.md) | 712-723 | RTOS 原生实验 |
| 52 | [uC/OS-II 实验 3：消息队列、信号量集和软件定时器](SOP-52-ucos-queue-event-timer.md) | 724-743 | RTOS 原生实验 |
