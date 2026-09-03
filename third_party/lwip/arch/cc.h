/* cc.h - Architecture environment for GCC ARM Cortex-M3 */

#ifndef __CC_H__
#define __CC_H__

#include <stdint.h>
#include <stdio.h>

typedef uint8_t   u8_t;
typedef int8_t    s8_t;
typedef uint16_t  u16_t;
typedef int16_t   s16_t;
typedef uint32_t  u32_t;
typedef int32_t   s32_t;
typedef uintptr_t mem_ptr_t;

#define PACK_STRUCT_FIELD(x) x
#define PACK_STRUCT_STRUCT __attribute__((packed))
#define PACK_STRUCT_BEGIN
#define PACK_STRUCT_END

#define LWIP_PLATFORM_DIAG(x)   do { printf x; } while(0)
#define LWIP_PLATFORM_ASSERT(x) do { printf("Assertion \"%s\" failed at line %d in %s\n", \
                                            x, __LINE__, __FILE__); \
                                     __disable_irq(); \
                                     while(1) {} \
                                } while(0)

#endif /* __CC_H__ */
