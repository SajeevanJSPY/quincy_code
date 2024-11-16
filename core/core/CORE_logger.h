#ifndef __CORE__LOGGER_H
#define __CORE__LOGGER_H

#include "CORE_defines.h"


typedef enum {
    LOG_TRACE,
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LOG_FATAL,

	LOG_NOTHING
} log_level;


CORE_API void CORE_logger_init(log_level level, const char *filename);
CORE_API void CORE_logger_shutdown();
CORE_API void CORE_logger_set_level(log_level level);
CORE_API bool CORE_logger_set_logfile(const char *filename);


void log_message(log_level level, const char *fmt, ...);
void log_message_info(const char *fmt, ...);

// log macros for different log levels
#define LOG_TRACE(fmt, ...) log_message(LOG_TRACE, fmt, ##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...) log_message(LOG_DEBUG, fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...) log_message(LOG_INFO, fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...) log_message(LOG_WARN, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) log_message(LOG_ERROR, fmt, ##__VA_ARGS__)
#define LOG_FATAL(fmt, ...) log_message(LOG_FATAL, fmt, ##__VA_ARGS__)
#define INFO(fmt, ...) log_message_info(fmt, ##__VA_ARGS__)


#endif // __CORE__LOGGER_H
