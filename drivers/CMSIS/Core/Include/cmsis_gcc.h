/**************************************************************************//**
 * @file     cmsis_gcc.h
 * @brief    CMSIS compiler GCC header file
 ******************************************************************************/
#ifndef __CMSIS_GCC_H
#define __CMSIS_GCC_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifndef   __ASM
  #define __ASM                                  __asm
#endif
#ifndef   __INLINE
  #define __INLINE                               inline
#endif
#ifndef   __STATIC_INLINE
  #define __STATIC_INLINE                        static inline
#endif
#ifndef   __STATIC_FORCEINLINE
  #define __STATIC_FORCEINLINE                   __attribute__((always_inline)) static inline
#endif
#ifndef   __NO_RETURN
  #define __NO_RETURN                            __attribute__((__noreturn__))
#endif
#ifndef   __USED
  #define __USED                                 __attribute__((used))
#endif
#ifndef   __WEAK
  #define __WEAK                                 __attribute__((weak))
#endif
#ifndef   __PACKED
  #define __PACKED                               __attribute__((packed, aligned(1)))
#endif
#ifndef   __PACKED_STRUCT
  #define __PACKED_STRUCT                        struct __attribute__((packed, aligned(1)))
#endif

__STATIC_FORCEINLINE void __NOP(void)
{
  __ASM volatile ("nop");
}

__STATIC_FORCEINLINE void __WFI(void)
{
  __ASM volatile ("wfi");
}

__STATIC_FORCEINLINE void __WFE(void)
{
  __ASM volatile ("wfe");
}

__STATIC_FORCEINLINE void __SEV(void)
{
  __ASM volatile ("sev");
}

__STATIC_FORCEINLINE void __ISB(void)
{
  __ASM volatile ("isb 0xF":::"memory");
}

__STATIC_FORCEINLINE void __DSB(void)
{
  __ASM volatile ("dsb 0xF":::"memory");
}

__STATIC_FORCEINLINE void __DMB(void)
{
  __ASM volatile ("dmb 0xF":::"memory");
}

__STATIC_FORCEINLINE void __enable_irq(void)
{
  __ASM volatile ("cpsie i" : : : "memory");
}

__STATIC_FORCEINLINE void __disable_irq(void)
{
  __ASM volatile ("cpsid i" : : : "memory");
}

#pragma GCC diagnostic pop

#endif
