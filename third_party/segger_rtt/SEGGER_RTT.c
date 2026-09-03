#include "SEGGER_RTT.h"
#include <string.h>

static char _acUpBuffer[BUFFER_SIZE_UP];

SEGGER_RTT_CB _SEGGER_RTT = {
  "SEGGER RTT",
  SEGGER_RTT_MAX_NUM_UP_BUFFERS,
  SEGGER_RTT_MAX_NUM_DOWN_BUFFERS,
  {{ "Terminal", _acUpBuffer, sizeof(_acUpBuffer), 0, 0, 0 }},
  {{ "Terminal", NULL, 0, 0, 0, 0 }}
};

void SEGGER_RTT_Init(void) {}

unsigned SEGGER_RTT_Write(unsigned BufferIndex, const void* pBuffer, unsigned NumBytes)
{
  (void)BufferIndex;
  if (pBuffer == NULL || NumBytes == 0U)
  {
    return 0;
  }
  unsigned NumBytesToWrite = NumBytes;
  if (NumBytesToWrite > BUFFER_SIZE_UP) NumBytesToWrite = BUFFER_SIZE_UP;
  memcpy(_acUpBuffer, pBuffer, NumBytesToWrite);
  return NumBytesToWrite;
}

unsigned SEGGER_RTT_WriteString(unsigned BufferIndex, const char* s)
{
  if (s == NULL)
  {
    return 0;
  }
  return SEGGER_RTT_Write(BufferIndex, s, strlen(s));
}
