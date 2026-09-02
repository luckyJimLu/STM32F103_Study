/**
  ******************************************************************************
  * @file    stm32f103xe.h
  * @author  MCD Application Team
  * @brief   CMSIS STM32F103xE Device Peripheral Access Layer Header File.
  ******************************************************************************
  */

#ifndef __STM32F103xE_H
#define __STM32F103xE_H

#ifdef __cplusplus
 extern "C" {
#endif 

#define __CM3_REV                 0x0200U  /*!< Core Revision r2p0                           */
#define __MPU_PRESENT             0U       /*!< STM32F103xE does not provide an MPU          */
#define __NVIC_PRIO_BITS          4U       /*!< STM32F103xE uses 4 Bits for the Priority Levels */
#define __Vendor_SysTickConfig    0U       /*!< Set to 1 if different SysTick Config is used */

typedef enum
{
  NonMaskableInt_IRQn   = -14,
  MemoryManagement_IRQn = -12,
  BusFault_IRQn         = -11,
  UsageFault_IRQn       = -10,
  SVCall_IRQn           = -5,
  DebugMonitor_IRQn     = -4,
  PendSV_IRQn           = -2,
  SysTick_IRQn          = -1,
  WWDG_IRQn             = 0,
  PVD_IRQn              = 1,
  TAMPER_IRQn           = 2,
  RTC_IRQn              = 3,
  FLASH_IRQn            = 4,
  RCC_IRQn              = 5,
  EXTI0_IRQn            = 6,
  EXTI1_IRQn            = 7,
  EXTI2_IRQn            = 8,
  EXTI3_IRQn            = 9,
  EXTI4_IRQn            = 10,
  DMA1_Channel1_IRQn    = 11,
  DMA1_Channel2_IRQn    = 12,
  DMA1_Channel3_IRQn    = 13,
  DMA1_Channel4_IRQn    = 14,
  DMA1_Channel5_IRQn    = 15,
  DMA1_Channel6_IRQn    = 16,
  DMA1_Channel7_IRQn    = 17,
  ADC1_2_IRQn           = 18,
  USB_HP_CAN1_TX_IRQn   = 19,
  USB_LP_CAN1_RX0_IRQn  = 20,
  CAN1_RX1_IRQn         = 21,
  CAN1_SCE_IRQn         = 22,
  EXTI9_5_IRQn          = 23,
  TIM1_BRK_IRQn         = 24,
  TIM1_UP_IRQn          = 25,
  TIM1_TRG_COM_IRQn     = 26,
  TIM1_CC_IRQn          = 27,
  TIM2_IRQn             = 28,
  TIM3_IRQn             = 29,
  TIM4_IRQn             = 30,
  I2C1_EV_IRQn          = 31,
  I2C1_ER_IRQn          = 32,
  I2C2_EV_IRQn          = 33,
  I2C2_ER_IRQn          = 34,
  SPI1_IRQn             = 35,
  SPI2_IRQn             = 36,
  USART1_IRQn           = 37,
  USART2_IRQn           = 38,
  USART3_IRQn           = 39,
  EXTI15_10_IRQn        = 40,
  RTC_Alarm_IRQn        = 41,
  USBWakeUp_IRQn        = 42,
  TIM8_BRK_IRQn         = 43,
  TIM8_UP_IRQn          = 44,
  TIM8_TRG_COM_IRQn     = 45,
  TIM8_CC_IRQn          = 46,
  ADC3_IRQn             = 47,
  FSMC_IRQn             = 48,
  SDIO_IRQn             = 49,
  TIM5_IRQn             = 50,
  SPI3_IRQn             = 51,
  UART4_IRQn            = 52,
  UART5_IRQn            = 53,
  TIM6_IRQn             = 54,
  TIM7_IRQn             = 55,
  DMA2_Channel1_IRQn    = 56,
  DMA2_Channel2_IRQn    = 57,
  DMA2_Channel3_IRQn    = 58,
  DMA2_Channel4_5_IRQn  = 59,
} IRQn_Type;

#include "core_cm3.h"
#include "system_stm32f1xx.h"
#include <stdint.h>

#define FLASH_BASE            0x08000000UL
#define SRAM_BASE             0x20000000UL
#define PERIPH_BASE           0x40000000UL

#define APB1PERIPH_BASE       PERIPH_BASE
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x00010000UL)
#define AHBPERIPH_BASE        (PERIPH_BASE + 0x00020000UL)

#define GPIOA_BASE            (APB2PERIPH_BASE + 0x00000800UL)
#define GPIOB_BASE            (APB2PERIPH_BASE + 0x00000C00UL)
#define GPIOC_BASE            (APB2PERIPH_BASE + 0x00001000UL)
#define GPIOD_BASE            (APB2PERIPH_BASE + 0x00001400UL)
#define GPIOE_BASE            (APB2PERIPH_BASE + 0x00001800UL)
#define GPIOF_BASE            (APB2PERIPH_BASE + 0x00001C00UL)
#define GPIOG_BASE            (APB2PERIPH_BASE + 0x00002000UL)

#define USART1_BASE           (APB2PERIPH_BASE + 0x00003800UL)
#define USART2_BASE           (APB1PERIPH_BASE + 0x00004400UL)
#define USART3_BASE           (APB1PERIPH_BASE + 0x00004800UL)

#define RCC_BASE              (AHBPERIPH_BASE + 0x00001000UL)

/* GPIO Structure */
typedef struct
{
  volatile uint32_t CRL;
  volatile uint32_t CRH;
  volatile uint32_t IDR;
  volatile uint32_t ODR;
  volatile uint32_t BSRR;
  volatile uint32_t BRR;
  volatile uint32_t LCKR;
} GPIO_TypeDef;

/* RCC Structure */
typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t CFGR;
  volatile uint32_t CIR;
  volatile uint32_t APB2RSTR;
  volatile uint32_t APB1RSTR;
  volatile uint32_t AHBENR;
  volatile uint32_t APB2ENR;
  volatile uint32_t APB1ENR;
  volatile uint32_t BDCR;
  volatile uint32_t CSR;
} RCC_TypeDef;

/* USART Structure */
typedef struct
{
  volatile uint32_t SR;
  volatile uint32_t DR;
  volatile uint32_t BRR;
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t CR3;
  volatile uint32_t GTPR;
} USART_TypeDef;

#define GPIOA               ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB               ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC               ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD               ((GPIO_TypeDef *) GPIOD_BASE)
#define GPIOE               ((GPIO_TypeDef *) GPIOE_BASE)
#define GPIOF               ((GPIO_TypeDef *) GPIOF_BASE)
#define GPIOG               ((GPIO_TypeDef *) GPIOG_BASE)

#define RCC                 ((RCC_TypeDef *) RCC_BASE)
#define USART1              ((USART_TypeDef *) USART1_BASE)
#define USART2              ((USART_TypeDef *) USART2_BASE)
#define USART3              ((USART_TypeDef *) USART3_BASE)

#define RCC_APB2ENR_IOPAEN_Pos               (2U)
#define RCC_APB2ENR_IOPAEN_Msk               (0x1UL << RCC_APB2ENR_IOPAEN_Pos)
#define RCC_APB2ENR_IOPBEN_Pos               (3U)
#define RCC_APB2ENR_IOPBEN_Msk               (0x1UL << RCC_APB2ENR_IOPBEN_Pos)
#define RCC_APB2ENR_IOPCEN_Pos               (4U)
#define RCC_APB2ENR_IOPCEN_Msk               (0x1UL << RCC_APB2ENR_IOPCEN_Pos)
#define RCC_APB2ENR_USART1EN_Pos             (14U)
#define RCC_APB2ENR_USART1EN_Msk             (0x1UL << RCC_APB2ENR_USART1EN_Pos)

#define USART_SR_TXE_Pos                     (7U)
#define USART_SR_TXE_Msk                     (0x1UL << USART_SR_TXE_Pos)
#define USART_SR_RXNE_Pos                    (5U)
#define USART_SR_RXNE_Msk                    (0x1UL << USART_SR_RXNE_Pos)

#define USART_CR1_UE_Pos                     (13U)
#define USART_CR1_UE_Msk                     (0x1UL << USART_CR1_UE_Pos)
#define USART_CR1_TE_Pos                     (3U)
#define USART_CR1_TE_Msk                     (0x1UL << USART_CR1_TE_Pos)
#define USART_CR1_RE_Pos                     (2U)
#define USART_CR1_RE_Msk                     (0x1UL << USART_CR1_RE_Pos)

#ifdef __cplusplus
}
#endif

#endif /* __STM32F103xE_H */
