
#ifndef  __LOG_H__
#define  __LOG_H__


#define MAX_MSG_LEN 1024

#define HDS_LOG_LEVEL_FATAL    0
#define HDS_LOG_LEVEL_ERROR    1
#define HDS_LOG_LEVEL_WARNING  2
#define HDS_LOG_LEVEL_INFO     3
#define HDS_LOG_LEVEL_DEBUG    4

#define ERROR           0
#define USER_ERROR      1
#define WARN            2
#define DEBUG           3


extern void LOG_DEBUG(const char *fmt, ...);
extern void LOG_WARNING(const char *fmt, ...);
extern void LOG_ERROR(const char *fmt, ...);
extern void LOG_FATAL(const char *fmt, ...);
extern void LOG_INFO(const char *fmt, ...);
extern void set_log_switch_on(int logLevel);
extern void set_log_switch_off(int logLevel);

extern void TBSYS_LOG(int logLevel,const char *fmt, ...);

extern char *g_log_file_path;
extern char g_bFatal_log_is_open;
extern char g_bError_log_is_open;
extern char g_bWarn_log_is_open;
extern char g_bInfo_log_is_open;
extern char g_bDebug_log_is_open;

#endif /*__LOG_H__*/

