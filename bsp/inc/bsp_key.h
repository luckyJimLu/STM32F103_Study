#ifndef BSP_KEY_H
#define BSP_KEY_H

typedef enum
{
    KEY_RELEASED = 0,
    KEY_PRESSED = 1
} Key_StateTypeDef;

void BSP_KEY_Init(void);
Key_StateTypeDef BSP_KEY_GetState(void);

#endif
