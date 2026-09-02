/**
  ******************************************************************************
  * @file    stm32f1xx_hal_def.h
  * @brief   This file contains HAL common defines, enumeration, macros and
  *          structures definitions.
  ******************************************************************************
  */

#ifndef __STM32F1xx_HAL_DEF
#define __STM32F1xx_HAL_DEF

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx.h"
#include <stddef.h>

typedef enum 
{
  HAL_OK       = 0x00U,
  HAL_ERROR    = 0x01U,
  HAL_BUSY     = 0x02U,
  HAL_TIMEOUT  = 0x03U
} HAL_StatusTypeDef;

typedef enum 
{
  HAL_UNLOCKED = 0x00U,
  HAL_LOCKED   = 0x01U
} HAL_LockTypeDef;

#define UNUSED(X) (void)X      /* To avoid gcc/g++ warnings */

#define __HAL_LOCK(__HANDLE__)                                           \
                                do{                                        \
                                    if((__HANDLE__)->Lock == HAL_LOCKED)   \
                                    {                                      \
                                       return HAL_BUSY;                    \
                                    }                                      \
                                    else                                   \
                                    {                                      \
                                       (__HANDLE__)->Lock = HAL_LOCKED;    \
                                    }                                      \
                                  }while (0U)

#define __HAL_UNLOCK(__HANDLE__)                                          \
                                  do{                                       \
                                      (__HANDLE__)->Lock = HAL_UNLOCKED;    \
                                    }while (0U)

#ifdef __cplusplus
}
#endif

#endif /* ___STM32F1xx_HAL_DEF */
