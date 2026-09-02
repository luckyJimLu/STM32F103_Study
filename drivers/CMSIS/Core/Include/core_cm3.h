/**************************************************************************//**
 * @file     core_cm3.h
 * @brief    CMSIS Cortex-M3 Core Peripheral Access Layer Header File
 ******************************************************************************/
#ifndef __CORE_CM3_H_GENERIC
#define __CORE_CM3_H_GENERIC

#include <stdint.h>
#include "cmsis_version.h"
#include "cmsis_compiler.h"

#ifdef __cplusplus
 extern "C" {
#endif

/* Memory mapping of Cortex-M3 Hardware */
#define SCS_BASE            (0xE000E000UL)                            /*!< System Control Space Base Address */
#define SysTick_BASE        (SCS_BASE +  0x0010UL)                    /*!< SysTick Base Address */
#define NVIC_BASE           (SCS_BASE +  0x0100UL)                    /*!< NVIC Base Address */
#define SCB_BASE            (SCS_BASE +  0x0D00UL)                    /*!< System Control Block Base Address */

typedef struct
{
  volatile uint32_t CTRL;                   /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
  volatile uint32_t LOAD;                   /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register */
  volatile uint32_t VAL;                    /*!< Offset: 0x008 (R/W)  SysTick Current Value Register */
  volatile const  uint32_t CALIB;           /*!< Offset: 0x00C (R/ )  SysTick Calibration Register */
} SysTick_Type;

typedef struct
{
  volatile uint32_t ISER[8U];               /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
        uint32_t RESERVED0[24U];
  volatile uint32_t ICER[8U];               /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
        uint32_t RSERVED1[24U];
  volatile uint32_t ISPR[8U];               /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
        uint32_t RESERVED2[24U];
  volatile uint32_t ICPR[8U];               /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
        uint32_t RESERVED3[24U];
  volatile uint32_t IABR[8U];               /*!< Offset: 0x200 (R/W)  Interrupt Active bit Register */
        uint32_t RESERVED4[56U];
  volatile uint8_t  IP[240U];               /*!< Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide) */
        uint32_t RESERVED5[644U];
  volatile  uint32_t STIR;                  /*!< Offset: 0xE00 ( /W)  Software Trigger Interrupt Register */
}  NVIC_Type;

typedef struct
{
  volatile const  uint32_t CPUID;           /*!< Offset: 0x000 (R/ )  CPUID Base Register */
  volatile uint32_t ICSR;                    /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
  volatile uint32_t VTOR;                    /*!< Offset: 0x008 (R/W)  Vector Table Offset Register */
  volatile uint32_t AIRCR;                   /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
  volatile uint32_t SCR;                     /*!< Offset: 0x010 (R/W)  System Control Register */
  volatile uint32_t CCR;                     /*!< Offset: 0x014 (R/W)  Configuration Control Register */
  volatile uint8_t  SHP[12U];                /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
  volatile uint32_t SHCSR;                   /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */
  volatile uint32_t CFSR;                    /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register */
  volatile uint32_t HFSR;                    /*!< Offset: 0x02C (R/W)  HardFault Status Register */
  volatile uint32_t DFSR;                    /*!< Offset: 0x030 (R/W)  Debug Fault Status Register */
  volatile uint32_t MMFAR;                   /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register */
  volatile uint32_t BFAR;                    /*!< Offset: 0x038 (R/W)  BusFault Address Register */
  volatile uint32_t AFSR;                    /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register */
} SCB_Type;

#define SysTick             ((SysTick_Type   *)     SysTick_BASE  )   /*!< SysTick configuration struct */
#define NVIC                ((NVIC_Type      *)     NVIC_BASE     )   /*!< NVIC configuration struct */
#define SCB                 ((SCB_Type       *)     SCB_BASE      )   /*!< SCB configuration struct */

#define SysTick_CTRL_CLKSOURCE_Pos          2U
#define SysTick_CTRL_CLKSOURCE_Msk         (1UL << SysTick_CTRL_CLKSOURCE_Pos)
#define SysTick_CTRL_TICKINT_Pos            1U
#define SysTick_CTRL_TICKINT_Msk           (1UL << SysTick_CTRL_TICKINT_Pos)
#define SysTick_CTRL_ENABLE_Pos             0U
#define SysTick_CTRL_ENABLE_Msk            (1UL /*<< SysTick_CTRL_ENABLE_Pos*/)

__STATIC_INLINE uint32_t SysTick_Config(uint32_t ticks)
{
  if ((ticks - 1UL) > 0xFFFFFFUL)
  {
    return (1UL);                                                   /* Reload value impossible */
  }

  SysTick->LOAD  = (uint32_t)(ticks - 1UL);                         /* set reload register */
  NVIC->IP[15]   = (uint8_t)((1UL << 7) - 1UL);                     /* set Priority for Systick Interrupt */
  SysTick->VAL   = 0UL;                                             /* Load the SysTick Counter Value */
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
                   SysTick_CTRL_TICKINT_Msk   |
                   SysTick_CTRL_ENABLE_Msk;                         /* Enable SysTick IRQ and SysTick Timer */
  return (0UL);                                                     /* Function successful */
}

__STATIC_INLINE void NVIC_EnableIRQ(int32_t IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    NVIC->ISER[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}

__STATIC_INLINE void NVIC_DisableIRQ(int32_t IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    NVIC->ICER[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}

__STATIC_INLINE void NVIC_SetPriority(int32_t IRQn, uint32_t priority)
{
  if ((int32_t)(IRQn) >= 0)
  {
    NVIC->IP[((uint32_t)IRQn)] = (uint8_t)((priority << (8U - 4U)) & (uint32_t)0xFFUL);
  }
}

#ifdef __cplusplus
}
#endif

#endif /* __CORE_CM3_H_GENERIC */
