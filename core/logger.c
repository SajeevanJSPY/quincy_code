#include "core/CORE_logger.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// color codes for ANSI escape sequences
// https://stackoverflow.com/questions/4842424/list-of-ansi-color-escape-sequences
#define RESET_COLOR "\033[0m"
#define RED_COLOR "\033[31;1m"
#define RED_COLOR_BG "\033[31;7;1m"
#define GREEN_COLOR "\033[32;1m"
#define YELLOW_COLOR "\033[33;1m"
#define BLUE_COLOR "\033[34;1m"
#define MAGENTA_COLOR "\033[35;1m"
#define CYAN_COLOR "\033[36;1m"
#define WHITE_COLOR "\033[37;1m"

static int logger_level = LOG_ERROR;
static bool log_flush;
static FILE *log_file = NULL;

const char *current_timestamp();
const char *log_to_color(log_level level);
const char *log_to_string(log_level level);

void CORE_logger_init(log_level level, const char *filename) {
    log_file = fopen(filename, "a");
    log_flush = true;
    logger_level = level;
}

void CORE_logger_shutdown() {
    if (log_file) {
        fclose(log_file);
    }
}

void CORE_logger_set_level(log_level level) { logger_level = level; }

bool CORE_logger_set_logfile(const char *filename) {
    log_file = fopen(filename, "a");
    if (!log_file) {
        return false;
    }
    return true;
}

void log_message(log_level level, const char *fmt, ...) {
    if (level > logger_level || logger_level == LOG_NOTHING) {
        return;
    }

    const char *timestamp = current_timestamp();
    const char *level_str = log_to_string(level);

    // console logging
    printf("%s[%s] [%s]%s ", log_to_color(level), timestamp, level_str,
           RESET_COLOR);
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    printf("\n");

    // file logging
    if (log_file) {
        fprintf(log_file, "[%s] [%s] ", timestamp, level_str);
        va_start(args, fmt);
        vfprintf(log_file, fmt, args);
        va_end(args);
        fprintf(log_file, "\n");
        fflush(log_file);
    }

    if (level == LOG_FATAL) {
        printf("This is a [Fatal] error, exiting the program\n");
        exit(EXIT_FAILURE);
    }
}

void log_message_info(const char *fmt, ...) {
    log_level level = LOG_INFO;
    const char *color = log_to_color(level);

    // console logging
    printf("\n\t%s", color);
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    printf("%s\n", RESET_COLOR);
}

const char *log_to_color(log_level level) {
    switch (level) {
    case LOG_TRACE:
        return CYAN_COLOR;
    case LOG_DEBUG:
        return YELLOW_COLOR;
    case LOG_INFO:
        return GREEN_COLOR;
    case LOG_WARN:
        return BLUE_COLOR;
    case LOG_ERROR:
        return RED_COLOR;
    case LOG_FATAL:
        return RED_COLOR_BG;
    default:
        return WHITE_COLOR;
    }
}

const char *log_to_string(log_level level) {
    switch (level) {
    case LOG_TRACE:
        return "TRACE";
    case LOG_DEBUG:
        return "DEBUG";
    case LOG_INFO:
        return "INFO";
    case LOG_WARN:
        return "WARN";
    case LOG_ERROR:
        return "ERROR";
    case LOG_FATAL:
        return "FATAL";
    default:
        return "UNKNOWN";
    }
}

const char *current_timestamp() {
    static char timestamp[20];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", t);
    return timestamp;
}
