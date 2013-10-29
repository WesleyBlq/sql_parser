#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include "log.h"


char *g_log_file_path = NULL;
char g_bFatal_log_is_open = 0;
char g_bError_log_is_open = 0;
char g_bWarn_log_is_open = 0;
char g_bInfo_log_is_open = 0;
char g_bDebug_log_is_open = 0;

void set_log_switch_on(int logLevel)
{
    switch (logLevel)
    {
        case HDS_LOG_LEVEL_FATAL:
            g_bFatal_log_is_open = 1;
            break;
        case HDS_LOG_LEVEL_ERROR:
            g_bError_log_is_open = 1;
            break;
        case HDS_LOG_LEVEL_WARNING:
            g_bWarn_log_is_open = 1;
            break;
        case HDS_LOG_LEVEL_INFO:
            g_bInfo_log_is_open = 1;
            break;
        case HDS_LOG_LEVEL_DEBUG:
            g_bDebug_log_is_open = 1;
            break;
        default:
            break;
    }
}

void set_log_switch_off(int logLevel)
{
    switch (logLevel)
    {
        case HDS_LOG_LEVEL_FATAL:
            g_bFatal_log_is_open = 0;
            break;
        case HDS_LOG_LEVEL_ERROR:
            g_bError_log_is_open = 0;
            break;
        case HDS_LOG_LEVEL_WARNING:
            g_bWarn_log_is_open = 0;
            break;
        case HDS_LOG_LEVEL_INFO:
            g_bInfo_log_is_open = 0;
            break;
        case HDS_LOG_LEVEL_DEBUG:
            g_bDebug_log_is_open = 0;
            break;
        default:
            break;
    }
}

static void log_msg(int logLevel, const char *msg)
{
    static FILE *log_fp = NULL;
    static int use_syslog = -1;

    if (use_syslog == -1)
    {
        const char *conf = g_log_file_path;
        if (conf == NULL)
            use_syslog = 1;
        else
        {
            use_syslog = 0;
            log_fp = fopen(conf, "a");
            if (log_fp == NULL)
            {
                fprintf(stderr, "Failed to open file %s for write.\n");
                exit(1);
            }
        }
    }

    const char *type;
    switch (logLevel)
    {
        case HDS_LOG_LEVEL_FATAL:
            type = "FATAL";
            break;
        case HDS_LOG_LEVEL_ERROR:
            type = "ERROR";
            break;
        case HDS_LOG_LEVEL_WARNING:
            type = "WARNING";
            break;
        case HDS_LOG_LEVEL_INFO:
            type = "INFO";
            break;
        case HDS_LOG_LEVEL_DEBUG:
            type = "DEBUG";
            break;
        default:
            type = "ERROR";
            break;
    }

    time_t now = time(NULL);
    char str[MAX_MSG_LEN];
    strcpy(str, ctime(&now));
    int len = strlen(str) - 1; // get rid of trailing newline

    len += snprintf(str + len, sizeof (str) - len, " %s %s", type, msg);

    // make sure we have newline
    if (str[len - 1] != '\n')
    {
        if (len + 1 < sizeof (str))
        {
            str[len++] = '\n';
            str[len] = '\0';
        }
        else
            str[len - 1] = '\n';
    }

    if (use_syslog)
        syslog(0, "%s", str);
    else
    {
        fprintf(log_fp, "%s", str);
        fflush(log_fp);
    }
}

void LOG_DEBUG(const char *fmt, ...)
{
    if (!g_bDebug_log_is_open)
    {
        return;
    }

    va_list args;
    va_start(args, fmt);
    char buf[MAX_MSG_LEN];
    vsnprintf(buf, sizeof (buf), fmt, args);
    va_end(args);
    log_msg(HDS_LOG_LEVEL_DEBUG, buf);

}

void LOG_WARNING(const char *fmt, ...)
{
    if (!g_bWarn_log_is_open)
    {
        return;
    }

    va_list args;
    va_start(args, fmt);
    char buf[MAX_MSG_LEN];
    vsnprintf(buf, sizeof (buf), fmt, args);
    va_end(args);
    log_msg(HDS_LOG_LEVEL_WARNING, buf);

}

void LOG_ERROR(const char *fmt, ...)
{
    if (!g_bError_log_is_open)
    {
        return;
    }

    va_list args;
    va_start(args, fmt);
    char buf[MAX_MSG_LEN];
    vsnprintf(buf, sizeof (buf), fmt, args);
    va_end(args);
    log_msg(HDS_LOG_LEVEL_ERROR, buf);

}

void LOG_FATAL(const char *fmt, ...)
{
    if (!g_bFatal_log_is_open)
    {
        return;
    }

    va_list args;
    va_start(args, fmt);
    char buf[MAX_MSG_LEN];
    vsnprintf(buf, sizeof (buf), fmt, args);
    va_end(args);
    log_msg(HDS_LOG_LEVEL_FATAL, buf);

    assert(0);
}

void LOG_INFO(const char *fmt, ...)
{
    if (!g_bInfo_log_is_open)
    {
        return;
    }

    va_list args;
    va_start(args, fmt);
    char buf[MAX_MSG_LEN];
    vsnprintf(buf, sizeof (buf), fmt, args);
    va_end(args);
    log_msg(HDS_LOG_LEVEL_INFO, buf);
}

void TBSYS_LOG(int logLevel, const char *fmt, ...)
{
#if 0
    switch (logLevel)
    {
        case USER_ERROR:
        case ERROR:
            LOG_ERROR(fmt, ...);
            break;
        case DEBUG:
            LOG_DEBUG(fmt, ...);
            break;
        case WARN:
            LOG_WARNING(fmt, ...);
            break;
        case INFO:
        default:
            LOG_INFO(fmt, ...);
            break;
    }
#endif    
}

