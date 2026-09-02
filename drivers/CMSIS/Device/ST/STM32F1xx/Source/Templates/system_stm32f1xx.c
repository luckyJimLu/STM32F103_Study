/**
  ******************************************************************************
  * @file    system_stm32f1xx.c
  * @author  MCD Application Team
  * @brief   CMSIS Cortex-M3 Device Peripheral Access Layer System Source File.
  ******************************************************************************
  */

#include <stdint.h>

#if !defined  (HSE_VALUE) 
  #define HSE_VALUE    8000000U /*!< Default value of the External oscillator in Hz. */
#endif 

#if !defined  (HSI_VALUE)
  #define HSI_VALUE    8000000U /*!< Default value of the Internal oscillator in Hz. */
#endif 

uint32_t SystemCoreClock = 72000000U;

const uint8_t AHBPrescTable[16U] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
const uint8_t APBPrescTable[8U] =  {0, 0, 0, 0, 1, 2, 3, 4};

/**
  * @brief  Setup the microcontroller system
  *         Initialize the Embedded Flash Interface, the PLL and update the 
  *         SystemCoreClock variable.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
void SystemInit (void)
{
  /* Reset the RCC clock configuration to the default reset state(for debug purpose) */
  /* Set HSION bit */
  *((volatile uint32_t *)(0x40021000 + 0x00)) |= 0x00000001U;

  /* Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits */
  *((volatile uint32_t *)(0x40021000 + 0x04)) &= 0xF8FF0000U;

  /* Reset HSEON, CSSON and PLLON bits */
  *((volatile uint32_t *)(0x40021000 + 0x00)) &= 0xFEF6FFFFU;

  /* Reset HSEBYP bit */
  *((volatile uint32_t *)(0x40021000 + 0x00)) &= 0xFFFBFFFFU;

  /* Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits */
  *((volatile uint32_t *)(0x40021000 + 0x04)) &= 0xFF80FFFFU;

  /* Disable all interrupts and clear pending bits  */
  *((volatile uint32_t *)(0x40021000 + 0x08)) = 0x009F0000U;

  /* Vector Table Relocation in Internal FLASH. */
  *((volatile uint32_t *)(0xE000ED08)) = 0x08000000U;
}

/**
  * @brief  Update SystemCoreClock variable according to Clock Register Values.
  * @param  None
  * @retval None
  */
void SystemCoreClockUpdate (void)
{
  SystemCoreClock = 72000000U;
}
