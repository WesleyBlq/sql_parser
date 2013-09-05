/*
 *  (C) 2007-2010 Taobao Inc.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 *
 *         ????.cpp is for what ...
 *
 *  Version: $Id: ipvsadm.c,v 1.27 2005/12/10 16:00:07 wensong Exp $
 *
 *  Authors:
 *     qushan <qushan@taobao.com>
 *        - some work details if you want
 */
#ifndef OCEANBASE_COMMON_UTILITY_H_
#define OCEANBASE_COMMON_UTILITY_H_

#include <stdint.h>
#include <execinfo.h>
#include <unistd.h>
#include <algorithm>
#include <stdarg.h>
#include <string>
#include "ob_define.h"
#include "ob_obj_type.h"
#include "log.h"

using namespace std;
using namespace oceanbase::common;

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
  oceanbase::common::__has_##member##__<type, sign>::value

namespace oceanbase
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
    void databuff_printf(char *buf, const int64_t buf_len, int64_t& pos, const char* fmt, ...) __attribute__ ((format (printf, 4, 5)));
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
} // end namespace oceanbase


#endif //OCEANBASE_COMMON_UTILITY_H_
