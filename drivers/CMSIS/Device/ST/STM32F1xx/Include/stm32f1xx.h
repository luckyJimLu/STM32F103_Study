/**
  ******************************************************************************
  * @file    stm32f1xx.h
  * @author  MCD Application Team
  * @brief   CMSIS STM32F1xx Device Component
  ******************************************************************************
  */
#ifndef __STM32F1xx_H
#define __STM32F1xx_H

#ifdef __cplusplus
 extern "C" {
#endif 

#if !defined (STM32F100xB) && !defined (STM32F100xE) && !defined (STM32F101x6) && \
    !defined (STM32F101xB) && !defined (STM32F101xE) && !defined (STM32F101xG) && \
    !defined (STM32F102x6) && !defined (STM32F102xB) && !defined (STM32F103x6) && \
    !defined (STM32F103xB) && !defined (STM32F103xE) && !defined (STM32F103xG) && \
    !defined (STM32F105xC) && !defined (STM32F107xC)
  /* Default to STM32F103xB if not defined */
  #define STM32F103xB
#endif

#if defined(STM32F103xB)
  #include "stm32f103xb.h"
#elif defined(STM32F103xE)
  #include "stm32f103xe.h"
#else
  #error "Please select target STM32F1xx device line in CMake configuration"
#endif

#ifdef __cplusplus
}
#endif

#endif /* __STM32F1xx_H */
