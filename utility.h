#ifndef COMMON_UTILITY_H_
#define COMMON_UTILITY_H_

#include <stdint.h>
#include <execinfo.h>
#include <unistd.h>
#include <algorithm>
#include <stdarg.h>
#include <string>
#include "../include/jderror.h"
#include "ob_define.h"
#include "ob_obj_type.h"
#include "log.h"

using namespace std;
using namespace jdbd::common;

/* Limits of integral types. */
#ifndef INT8_MIN
#define INT8_MIN               (-128)
#endif
#ifndef INT16_MIN
#define INT16_MIN              (-32767-1)
#endif
#ifndef INT32_MIN
#define INT32_MIN              (-2147483647-1)
#endif
#ifndef INT8_MAX
#define INT8_MAX               (127)
#endif
#ifndef INT16_MAX
#define INT16_MAX              (32767)
#endif
#ifndef INT32_MAX
#define INT32_MAX              (2147483647)
#endif
#ifndef UINT8_MAX
#define UINT8_MAX              (255U)
#endif
#ifndef UINT16_MAX
#define UINT16_MAX             (65535U)
#endif
#ifndef UINT32_MAX
#define UINT32_MAX             (4294967295U)
#endif

#ifndef INT64_MAX
#define INT64_MAX               (9223372036854775807LL)
#endif

#ifndef UINT64_MAX
#define UINT64_MAX              (18446744073709551615ULL)
#endif

extern int ob_write_string(const string &src, string &dst);
//BEGIN: Added by qinbo for add print stack process
#ifndef BACKTRACE
#define BACKTRACE() \
 do \
 { \
    void *array[100];   \
    int size = backtrace(array, 100);\
    char **strings; \
    int i;  \
    strings = backtrace_symbols(array, size);\
    printf("\nObtained %d stack frames:\n", size);\
    free(strings);  \
    char cmd[64] = "addr2line -C -f -e ";   \
    char* prog = cmd + strlen(cmd); \
    readlink("/proc/self/exe", prog, sizeof(cmd) - strlen(cmd) - 1);\
    FILE* fp = popen(cmd, "w");\
    if (fp != NULL)\
    {\
        for (i = 0; i < size-2; ++i)\
        {\
            fprintf(fp, "%p\n", array[i]);\
        }\
        pclose(fp);\
    }\
    int fd = open("coredump.log", O_CREAT | O_WRONLY);\
    backtrace_symbols_fd(array, size, fd);\
    close(fd);\
 } \
 while (false)
#endif
//END: Added by qinbo for add print stack process

#define STR_BOOL(b) ((b) ? "true" : "false")

#ifndef htonll
#define htonll(i) \
  ( \
  (((uint64_t)i & 0x00000000000000ff) << 56) | \
  (((uint64_t)i & 0x000000000000ff00) << 40) | \
  (((uint64_t)i & 0x0000000000ff0000) << 24) | \
  (((uint64_t)i & 0x00000000ff000000) << 8) | \
  (((uint64_t)i & 0x000000ff00000000) >> 8) | \
  (((uint64_t)i & 0x0000ff0000000000) >> 24) | \
  (((uint64_t)i & 0x00ff000000000000) >> 40) | \
  (((uint64_t)i & 0xff00000000000000) >> 56)   \
  )
#endif

#define DEFAULT_TIME_FORMAT "%Y-%m-%d %H:%M:%S"

#define HAS_MEMBER(type, sign, member) \
  jdbd::common::__has_##member##__<type, sign>::value

namespace jdbd
{
    namespace common
    {
        int64_t lower_align(int64_t input, int64_t align);
        int64_t upper_align(int64_t input, int64_t align);
        bool is2n(int64_t input);
        bool all_zero(const char *buffer, const int64_t size);
        bool all_zero_small(const char *buffer, const int64_t size);
        const char* get_file_path(const char* file_dir, const char* file_name);
        char* str_trim(char *str);
        char* ltrim(char *str);
        char* rtrim(char *str);
        const char *inet_ntoa_r(const uint64_t ipport);
        void databuff_printf(char *buf, const int64_t buf_len, int64_t& pos, const char* fmt, ...) __attribute__((format(printf, 4, 5)));
        const char *time2str(const int64_t time_s, const char *format = DEFAULT_TIME_FORMAT);
        const char* strtype(ObObjType type);
        //const char* strtype(ObObjType type);

        template <bool c>
        struct BoolType
        {
            static const bool value = c;
        };
        typedef BoolType<false> FalseType;
        typedef BoolType<true> TrueType;

        template <typename T>
        int64_t to_string(const T &obj, char *buffer, const int64_t buffer_size)
        {
            return obj.to_string(buffer, buffer_size);
        }
        template <>
        int64_t to_string<string>(const string &obj, char *buffer, const int64_t buffer_size);

    } // end namespace common
} // end namespace jdbd


#endif //COMMON_UTILITY_H_
