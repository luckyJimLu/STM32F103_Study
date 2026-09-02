#ifndef SEGGER_RTT_H
#define SEGGER_RTT_H

#include <stdint.h>
#include <stddef.h>

#define SEGGER_RTT_MAX_NUM_UP_BUFFERS     1
#define SEGGER_RTT_MAX_NUM_DOWN_BUFFERS   1
#define BUFFER_SIZE_UP                    512

typedef struct {
  const char* sName;
  char*       pBuffer;
  unsigned    SizeOfBuffer;
  unsigned    WrOff;
  volatile unsigned RdOff;
  unsigned    Flags;
} RING_BUFFER;

typedef struct {
  char        acID[16];
  int         MaxNumUpBuffers;
  int         MaxNumDownBuffers;
  RING_BUFFER aUp[SEGGER_RTT_MAX_NUM_UP_BUFFERS];
  RING_BUFFER aDown[SEGGER_RTT_MAX_NUM_DOWN_BUFFERS];
} SEGGER_RTT_CB;

void SEGGER_RTT_Init(void);
unsigned SEGGER_RTT_WriteString(unsigned BufferIndex, const char* s);
unsigned SEGGER_RTT_Write(unsigned BufferIndex, const void* pBuffer, unsigned NumBytes);

#endif
