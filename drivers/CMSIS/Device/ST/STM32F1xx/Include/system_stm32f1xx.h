/**
  ******************************************************************************
  * @file    system_stm32f1xx.h
  * @author  MCD Application Team
  * @brief   CMSIS Device System Header File for STM32F1xx devices.
  ******************************************************************************
  */

#ifndef __SYSTEM_STM32F1XX_H
#define __SYSTEM_STM32F1XX_H

#ifdef __cplusplus
 extern "C" {
#endif 

extern uint32_t SystemCoreClock;          /*!< System Clock Frequency (Core Clock) */
extern const uint8_t AHBPrescTable[16U];  /*!< AHB prescalers table values */
extern const uint8_t APBPrescTable[8U];   /*!< APB prescalers table values */

extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);

#ifdef __cplusplus
}
#endif

#endif /*__SYSTEM_STM32F1XX_H */
