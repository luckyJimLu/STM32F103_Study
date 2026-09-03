#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include "autoconf.h"

#define APP_VERSION_MAJOR 1
#define APP_VERSION_MINOR 1
#define APP_VERSION_PATCH 0

#if CONFIG_APP_POLL_INTERVAL_MS > CONFIG_APP_LED_BLINK_INTERVAL_MS
#error "Application poll interval must not exceed heartbeat interval"
#endif

#endif
