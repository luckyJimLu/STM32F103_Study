#include "logger.h"

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>

#if defined(CONFIG_LOG_ENABLE)
static Logger_OutputFunction s_output;
static Logger_TimestampFunction s_timestamp;
static bool s_initialized;

static const char *logger_level_name(Logger_LevelTypeDef level)
{
    static const char *const names[] = {
        "FATAL", "ERROR", "WARN ", "INFO ", "DEBUG"};

    if ((unsigned int)level >= (sizeof(names) / sizeof(names[0])))
    {
        return "UNKWN";
    }
    return names[level];
}
#endif

void Logger_Init(Logger_OutputFunction output,
                 Logger_TimestampFunction timestamp)
{
#if defined(CONFIG_LOG_ENABLE)
    s_output = output;
    s_timestamp = timestamp;
    s_initialized = output != NULL;
#else
    (void)output;
    (void)timestamp;
#endif
}

bool Logger_IsInitialized(void)
{
#if defined(CONFIG_LOG_ENABLE)
    return s_initialized;
#else
    return false;
#endif
}

void Logger_Write(Logger_LevelTypeDef level,
                  const char *tag,
                  const char *format,
                  ...)
{
#if defined(CONFIG_LOG_ENABLE)
    char line[CONFIG_LOG_BUFFER_SIZE];
    size_t used;
    int result;
    va_list args;

    if (!s_initialized || (level > (Logger_LevelTypeDef)CONFIG_LOG_LEVEL) ||
        (format == NULL))
    {
        return;
    }

    result = snprintf(line,
                      sizeof(line),
                      "[%010lu] [%s] [%-7s] ",
                      (unsigned long)(s_timestamp != NULL ? s_timestamp() : 0U),
                      logger_level_name(level),
                      tag != NULL ? tag : "SYSTEM");
    if (result < 0)
    {
        return;
    }

    used = (size_t)result;
    if (used >= sizeof(line))
    {
        used = sizeof(line) - 1U;
    }

    va_start(args, format);
    result = vsnprintf(&line[used], sizeof(line) - used, format, args);
    va_end(args);
    if (result < 0)
    {
        return;
    }

    if ((size_t)result >= (sizeof(line) - used))
    {
        used = sizeof(line) - 1U;
    }
    else
    {
        used += (size_t)result;
    }

    if (used > (sizeof(line) - 3U))
    {
        used = sizeof(line) - 3U;
    }
    line[used++] = '\r';
    line[used++] = '\n';
    line[used] = '\0';
    s_output(line, (uint16_t)used);
#else
    (void)level;
    (void)tag;
    (void)format;
#endif
}
