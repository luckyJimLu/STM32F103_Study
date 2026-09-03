#ifndef LOGGER_H
#define LOGGER_H

#include <stdbool.h>
#include <stdint.h>

#include "autoconf.h"

typedef enum
{
    LOGGER_LEVEL_FATAL = 0,
    LOGGER_LEVEL_ERROR = 1,
    LOGGER_LEVEL_WARN = 2,
    LOGGER_LEVEL_INFO = 3,
    LOGGER_LEVEL_DEBUG = 4
} Logger_LevelTypeDef;

typedef void (*Logger_OutputFunction)(const char *data, uint16_t length);
typedef uint32_t (*Logger_TimestampFunction)(void);

void Logger_Init(Logger_OutputFunction output,
                 Logger_TimestampFunction timestamp);
bool Logger_IsInitialized(void);
void Logger_Write(Logger_LevelTypeDef level,
                  const char *tag,
                  const char *format,
                  ...);

#if defined(CONFIG_LOG_ENABLE)
#define LOG_FATAL(tag, format, ...) \
    Logger_Write(LOGGER_LEVEL_FATAL, tag, format, ##__VA_ARGS__)
#define LOG_ERROR(tag, format, ...) \
    Logger_Write(LOGGER_LEVEL_ERROR, tag, format, ##__VA_ARGS__)
#define LOG_WARN(tag, format, ...) \
    Logger_Write(LOGGER_LEVEL_WARN, tag, format, ##__VA_ARGS__)
#define LOG_INFO(tag, format, ...) \
    Logger_Write(LOGGER_LEVEL_INFO, tag, format, ##__VA_ARGS__)
#define LOG_DEBUG(tag, format, ...) \
    Logger_Write(LOGGER_LEVEL_DEBUG, tag, format, ##__VA_ARGS__)
#else
#define LOG_FATAL(tag, format, ...) ((void)0)
#define LOG_ERROR(tag, format, ...) ((void)0)
#define LOG_WARN(tag, format, ...) ((void)0)
#define LOG_INFO(tag, format, ...) ((void)0)
#define LOG_DEBUG(tag, format, ...) ((void)0)
#endif

#endif
