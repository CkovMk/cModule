#ifndef D_STM32F4XX_INC_SYSLOG_PORT_H
#define D_STM32F4XX_INC_SYSLOG_PORT_H

#include "hitsic_common.h"
#include "stdio.h"

#ifdef DEBUG
#define SYSLOG_DEBUG
#endif

#define HITSIC_LOG_PRINTF(...)  (printf(__VA_ARGS__))

#define HITSIC_LOG_LINEFEED ("\r\n")

#endif // ! D_STM32F4XX_INC_SYSLOG_PORT_H
