
#ifndef COMMON_OB_DEFINE_H_
#define COMMON_OB_DEFINE_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <openssl/md5.h>
#include "log.h"
#include "../include/jderror.h"
#include "../route/meta_reader.h"
#include "../route/router.h"
#include "../route/shard.h"


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


#define RAW_EXPR_BUF_SIZE   1024
#define STMT_BUF_SIZE       1024
#define SQL_PLAN_BUF_SIZE   4096

#define MAX_ERROR_MSG_ 1024


typedef struct
{
  int   err_code_;
  char  err_msg_[MAX_ERROR_MSG_];
} ErrStat;


typedef struct
{
  void*     plan_tree_;
  void*     name_pool_;     // ObStringBuf
  ErrStat   err_stat_;
  int       is_prepare_;
  string    db_name;        //record current db name
  string    host_name;      
  string    user_name;      
  string    meta_db_name;   //record meta db name 
  bool      is_show_sys_var;//this sql is "select @@xxxxx" 
  bool      has_sub_query;
} ResultPlan;


namespace jdbd
{
    namespace common
    {
        const int OB_SUCCESS = EXIT_SUCCESS;
        const int OB_ERROR = EXIT_FAILURE;
        const uint16_t OB_COMPACT_COLUMN_INVALID_ID = UINT16_MAX;
        const uint64_t OB_INVALID_ID = UINT64_MAX;

        typedef int64_t ObDateTime;
        typedef int64_t ObPreciseDateTime;
        typedef ObPreciseDateTime ObModifyTime;
        typedef ObPreciseDateTime ObCreateTime;

        const int64_t OB_MAX_SQL_LENGTH = 10240;
        const int64_t OB_MAX_SERVER_ADDR_SIZE = 128;
        const uint64_t OB_MAX_VALID_COLUMN_ID = 10240; // user table max valid column id
        const int64_t OB_MAX_TABLE_NUMBER = 2048;
        const int64_t OB_MAX_JOIN_INFO_NUMBER = 10;
        const int64_t OB_MAX_ROW_KEY_LENGTH = 16384; // 16KB
        const int64_t OB_MAX_ROW_KEY_SPLIT = 32;
        const int64_t OB_MAX_ROWKEY_COLUMN_NUMBER = 16;
        const int64_t OB_MAX_COLUMN_NAME_LENGTH = 128; //this means we can use 127 chars for a name.
        const int64_t OB_MAX_APP_NAME_LENGTH = 128;
        const int64_t OB_MAX_INSTANCE_NAME_LENGTH = 128;
        const int64_t OB_MAX_HOST_NAME_LENGTH = 128;

        const int64_t OB_MAX_DEBUG_MSG_LEN = 1024;
        const int64_t OB_MAX_COMPRESSOR_NAME_LENGTH = 128;
        const int64_t OB_MAX_TABLE_NAME_LENGTH = 256;
        const int64_t OB_MAX_FILE_NAME_LENGTH = 512;
        const int64_t OB_MAX_SECTION_NAME_LENGTH = 128;
        const int64_t OB_MAX_FLAG_NAME_LENGTH = 128;
        const int64_t OB_MAX_FLAG_VALUE_LENGTH = 512;
        const int64_t OB_MAX_TOKEN_BUFFER_LENGTH = 80;
        const int64_t OB_MAX_PACKET_LENGTH = 1 << 21; // max packet length, 2MB
        const int64_t OB_MAX_ROW_NUMBER_PER_QUERY = 65536;
        const int64_t OB_MAX_BATCH_NUMBER = 100;
        const int64_t OB_MAX_TABLET_LIST_NUMBER = 1 << 10;
        const int64_t OB_MAX_DISK_NUMBER = 16;
        const int64_t OB_MAX_TIME_STR_LENGTH = 64;
        const int64_t OB_IP_STR_BUFF = 30;
        const int64_t OB_RANGE_STR_BUFSIZ = 512;
        const int64_t OB_MAX_FETCH_CMD_LENGTH = 2048;
        const int64_t OB_MAX_EXPIRE_CONDITION_LENGTH = 512;
        const int64_t OB_MAX_COLUMN_GROUP_NUMBER = 16;
        const int64_t OB_MAX_THREAD_READ_SSTABLE_NUMBER = 16;
        const int64_t OB_MAX_GET_ROW_NUMBER = 10240;
        const uint64_t OB_FULL_ROW_COLUMN_ID = 0;
        const uint64_t OB_DELETE_ROW_COLUMN_ID = 0;
        const int64_t OB_DIRECT_IO_ALIGN_BITS = 9;
        const int64_t OB_DIRECT_IO_ALIGN = 1 << OB_DIRECT_IO_ALIGN_BITS;
        const int64_t OB_MAX_COMPOSITE_SYMBOL_COUNT = 256;
        const int64_t OB_SERVER_VERSION_LENGTH = 64;
        const int64_t OB_SERVER_TYPE_LENGTH = 64;
        const int64_t OB_MAX_USERNAME_LENGTH = 32;
        const int64_t OB_MAX_PASSWORD_LENGTH = 32;
        const int64_t OB_MAX_CIPHER_LENGTH = MD5_DIGEST_LENGTH * 2;

        const int64_t OB_MAX_RESULT_MESSAGE_LENGTH = 1024;
        const int64_t OB_MAX_LOG_BUFFER_SIZE = 1966080L; // 1.875MB

        const int32_t OB_SAFE_COPY_COUNT = 3;

        // OceanBase Log Synchronization Type
        const int64_t OB_LOG_NOSYNC = 0;
        const int64_t OB_LOG_SYNC = 1;
        const int64_t OB_LOG_DELAYED_SYNC = 2;

        const int64_t OB_MAX_UPS_LEASE_DURATION_US = INT64_MAX;

        const int64_t OB_EXECABLE = 1;
        const int64_t OB_WRITEABLE = 2;
        const int64_t OB_READABLE = 4;
        const int64_t OB_SCHEMA_START_VERSION = 100;
        const int64_t OB_SYS_PARAM_ROW_KEY_LENGTH = 192;
        const int64_t OB_MAX_SYS_PARAM_NAME_LENGTH = 128;

        const int64_t OB_MAX_PREPARE_STMT_NUM_PER_SESSION = 512;
        const int64_t OB_MAX_VAR_NUM_PER_SESSION = 1024;
        const int64_t OB_DEFAULT_SESSION_TIMEOUT = 100L * 1000L * 1000L; // 10s
        const int64_t OB_DEFAULT_STMT_TIMEOUT = 1L * 1000L * 1000L; // 1s

        //Oceanbase network protocol
        /*  4bytes    4bytes        4bytes       4bytes
         * -------------------------------------------------
         * | flag | channel id | packet code | data length |
         * -------------------------------------------------
         */
        const int OB_TBNET_HEADER_LENGTH = 16; //16 bytes packet header

        const int OB_TBNET_PACKET_FLAG = 0x416e4574;
        const int OB_SERVER_ADDR_STR_LEN = 128; //used for buffer size of easy_int_addr_to_str

        /*   3bytes   1 byte
         * ------------------
         * |   len  |  seq  |
         * ------------------
         */
        const int OB_MYSQL_PACKET_HEADER_SIZE = 4; /** 3bytes length + 1byte seq*/

        const int64_t OB_UPS_START_MAJOR_VERSION = 2;
        const int64_t OB_UPS_START_MINOR_VERSION = 1;

        const int64_t OB_NEWEST_DATA_VERSION = -2;

        const int32_t OB_CONNECTION_FREE_TIME_S = 900;

        /// @see ob_object.cpp and ob_expr_obj.cpp
        static const float FLOAT_EPSINON = static_cast<float> (1e-6);
        static const double DOUBLE_EPSINON = 1e-14;

        const uint64_t OB_UPS_MAX_MINOR_VERSION_NUM = 2048;
        const int64_t OB_MAX_COMPACTSSTABLE_NUM = 64;

        enum ObRole
        {
            OB_INVALID = 0,
            OB_ROOTSERVER = 1, // rs
            OB_CHUNKSERVER = 2, // cs
            OB_MERGESERVER = 3, // ms
            OB_UPDATESERVER = 4, // ups
        };

        static const int OB_FAKE_MS_PORT = 2828;

        static const uint64_t OB_ALL_MAX_COLUMN_ID = 65535;
        // internal columns id
        const uint64_t OB_NOT_EXIST_COLUMN_ID = 0;
        const uint64_t OB_CREATE_TIME_COLUMN_ID = 2;
        const uint64_t OB_MODIFY_TIME_COLUMN_ID = 3;
        const uint64_t OB_DEFAULT_COLUMN_GROUP_ID = 0;
        const int64_t OB_END_RESERVED_COLUMN_ID_NUM = 16;
        const uint64_t OB_APP_MIN_COLUMN_ID = 16;
        const uint64_t OB_ACTION_FLAG_COLUMN_ID = OB_ALL_MAX_COLUMN_ID - OB_END_RESERVED_COLUMN_ID_NUM + 1; /* 65520 */
        const uint64_t OB_MAX_TMP_COLUMN_ID = OB_ALL_MAX_COLUMN_ID - OB_END_RESERVED_COLUMN_ID_NUM;
        // internal columns name
        //extern const char *OB_CREATE_TIME_COLUMN_NAME;
        //extern const char *OB_MODIFY_TIME_COLUMN_NAME;
        static const char * const CLUSTER_ID_FILE = "etc/cluster.id";

        // internal tables name
        const char* const FIRST_TABLET_TABLE_NAME = "__first_tablet_entry";
        const char* const OB_ALL_COLUMN_TABLE_NAME = "__all_all_column";
        const char* const OB_ALL_JOININFO_TABLE_NAME = "__all_join_info";
        const char* const OB_ALL_SERVER_STAT_TABLE_NAME = "__all_server_stat";
        const char* const OB_ALL_SYS_PARAM_TABLE_NAME = "__all_sys_param";
        const char* const OB_ALL_SYS_CONFIG_TABLE_NAME = "__all_sys_config";
        const char* const OB_ALL_SYS_STAT_TABLE_NAME = "__all_sys_stat";
        const char* const OB_ALL_USER_TABLE_NAME = "__all_user";
        const char* const OB_ALL_TABLE_PRIVILEGE_TABLE_NAME = "__all_table_privilege";
        const char* const OB_ALL_TRIGGER_EVENT_TABLE_NAME = "__all_trigger_event";
        const char* const OB_ALL_SYS_CONFIG_STAT_TABLE_NAME = "__all_sys_config_stat";
        const char* const OB_ALL_CLUSTER = "__all_cluster";
        const char* const OB_ALL_SERVER = "__all_server";
        const char* const OB_ALL_CLIENT = "__all_client";
        const char* const OB_TABLES_SHOW_DATABASE_NAME = "__databases_show";
        const char* const OB_TABLES_SHOW_TABLE_NAME = "__tables_show";
        const char* const OB_VARIABLES_SHOW_TABLE_NAME = "__variables_show";
        const char* const OB_CREATE_TABLE_SHOW_TABLE_NAME = "__create_table_show";
        const char* const OB_TABLE_STATUS_SHOW_TABLE_NAME = "__table_status_show";
        const char* const OB_SCHEMA_SHOW_TABLE_NAME = "__schema_show";
        const char* const OB_COLUMNS_SHOW_TABLE_NAME = "__columns_show";
        const char* const OB_SERVER_STATUS_SHOW_TABLE_NAME = "__server_status_show";
        const char* const OB_PARAMETERS_SHOW_TABLE_NAME = "__parameters_show";
        // internal params
        const char* const OB_GROUP_AGG_PUSH_DOWN_PARAM = "ob_group_agg_push_down_param";
        // internal table id
        static const uint64_t OB_FIRST_META_VIRTUAL_TID = OB_INVALID_ID - 1; // not a real table
        static const uint64_t OB_NOT_EXIST_TABLE_TID = 0;
        static const uint64_t OB_FIRST_TABLET_ENTRY_TID = 1;
        static const uint64_t OB_ALL_ALL_COLUMN_TID = 2;
        static const uint64_t OB_ALL_JOIN_INFO_TID = 3;
        static const uint64_t OB_ALL_SYS_PARAM_TID = 4;
        static const uint64_t OB_ALL_SYS_STAT_TID = 5;
        static const uint64_t OB_USERS_TID = 6;
        static const uint64_t OB_TABLE_PRIVILEGES_TID = 7;
        static const uint64_t OB_ALL_CLUSTER_TID = 8;
        static const uint64_t OB_ALL_SERVER_TID = 9;
        static const uint64_t OB_TRIGGER_EVENT_TID = 10;
        static const uint64_t OB_ALL_SYS_CONFIG_TID = 11;
        static const uint64_t OB_ALL_SYS_CONFIG_STAT_TID = 12;
        static const uint64_t OB_ALL_CLIENT_TID = 13;

        ///////////////////////////////////////////////////////////
        //                 VIRUTAL TABLES                        //
        ///////////////////////////////////////////////////////////
        // VIRTUAL TABLES ID (500, 700), they should not be mutated
#define IS_VIRTUAL_TABLE(tid) ((tid) > 500 && (tid) < 700)
        static const uint64_t OB_TABLES_SHOW_TID = 501;
        static const uint64_t OB_COLUMNS_SHOW_TID = 502;
        static const uint64_t OB_VARIABLES_SHOW_TID = 503;
        static const uint64_t OB_TABLE_STATUS_SHOW_TID = 504;
        static const uint64_t OB_SCHEMA_SHOW_TID = 505;
        static const uint64_t OB_CREATE_TABLE_SHOW_TID = 506;
        static const uint64_t OB_PARAMETERS_SHOW_TID = 507;
        static const uint64_t OB_SERVER_STATUS_SHOW_TID = 508;
        static const uint64_t OB_ALL_SERVER_STAT_TID = 509;
        static const uint64_t OB_ALL_SERVER_SESSION_TID = 510;
        static const uint64_t OB_ALL_STATEMENT_TID = 511;

static const uint64_t OB_APP_MIN_TABLE_ID = 1000;

#define IS_SHOW_TABLE(tid) ((tid) >= OB_TABLES_SHOW_TID && (tid) <= OB_SERVER_STATUS_SHOW_TID)

        static const uint64_t OB_ALL_STAT_COLUMN_MAX_COLUMN_ID = 45;
        static const uint64_t OB_ALL_ALL_COLUMN_MAX_COLUMN_ID = 45;
        static const uint64_t OB_ALL_JOIN_INFO_MAX_COLUMN_ID = 45;
        static const uint64_t OB_ALL_SYS_STAT_MAX_COLUMN_ID = 45;
        static const uint64_t OB_ALL_SYS_PARAM_MAX_COLUMN_ID = 45;
        static const uint64_t OB_ALL_SYS_CONFIG_MAX_COLUMN_ID = 45;
        static const uint64_t OB_ALL_CLUSTER_MAX_COLUMN_ID = 45;
        static const uint64_t OB_ALL_SERVER_MAX_COLUMN_ID = 45;

        static const uint64_t OB_MAX_CLUSTER_NAME = 128;
        static const uint64_t OB_MAX_CLUSTER_INFO = 128;
        // internal user id
        static const uint64_t OB_ADMIN_UID = 1;
        const char* const OB_ADMIN_USER_NAME = "admin";

        /// 一个行可以包含的最大元素/列数
        static const int64_t OB_MALLOC_BLOCK_SIZE = 64 * 1024L;
        static const int64_t OB_ROW_MAX_COLUMNS_COUNT = 512; // used in ObRow
        static const int64_t OB_MAX_VARCHAR_LENGTH = OB_MALLOC_BLOCK_SIZE - 512;
        static const int64_t OB_COMMON_MEM_BLOCK_SIZE = OB_MAX_VARCHAR_LENGTH;
        static const int64_t OB_MAX_ROW_LENGTH = OB_MAX_PACKET_LENGTH - 512L * 1024L;
        static const int64_t OB_MAX_COLUMN_NUMBER = OB_ROW_MAX_COLUMNS_COUNT; // used in ObSchemaManagerV2
        static const int64_t OB_MAX_USER_DEFINED_COLUMNS_COUNT = OB_ROW_MAX_COLUMNS_COUNT - OB_APP_MIN_COLUMN_ID;

        const char* const SYS_DATE = "$SYS_DATE";
        const char* const OB_DEFAULT_COMPRESS_FUNC_NAME = "snappy_1.0";

        static const int64_t OB_MAX_CONFIG_NAME_LEN = 64;
        static const int64_t OB_MAX_CONFIG_VALUE_LEN = 1024;
        static const int64_t OB_MAX_CONFIG_INFO_LEN = 1024;
        static const int64_t OB_MAX_CONFIG_NUMBER = 1024;
        static const int64_t OB_MAX_EXTRA_CONFIG_LENGTH = 4096;

        static const int64_t OB_TABLET_MAX_REPLICA_COUNT = 6;

        const char* const OB_META_TABLE_NAME_PREFIX = "__m_";
        static const int64_t OB_META_TABLE_NAME_PREFIX_LENGTH = strlen(OB_META_TABLE_NAME_PREFIX);

        static const int64_t OB_DEFAULT_SSTABLE_BLOCK_SIZE = 64 * 1024; // 64KB
        static const int64_t OB_DEFAULT_MAX_TABLET_SIZE = 256 * 1024 * 1024; // 256MB
        static const int64_t OB_MYSQL_PACKET_BUFF_SIZE = 6 * 1024; //6KB
        static const int64_t OB_MAX_ERROR_CODE = 10000;
        static const int64_t OB_MAX_THREAD_NUM = 1024;
    } // end namespace common
} // end namespace oceanbase
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&);               \
  void operator=(const TypeName&)

// 对于 serialize 函数 pos既是输入参数又是输出参数，
// serialize把序列化的数据从(buf+pos)处开始写入，
// 写入完成后更新pos。如果写入后的数据要超出(buf+buf_len)，
// serialize返回失败。
//
// 对于 deserialize 函数 pos既是输入参数又是输出参数，
// deserialize从(buf+pos)处开始地读出数据进行反序列化，
// 完成后更新pos。如果反序列化所需数据要超出(buf+data_len)，
// deserialize返回失败。

#define NEED_SERIALIZE_AND_DESERIALIZE \
int serialize(char* buf, const int64_t buf_len, int64_t& pos) const; \
  int deserialize(const char* buf, const int64_t data_len, int64_t& pos); \
    int64_t get_serialize_size(void) const

#define INLINE_NEED_SERIALIZE_AND_DESERIALIZE \
inline int serialize(char* buf, const int64_t buf_len, int64_t& pos) const; \
  inline int deserialize(const char* buf, const int64_t data_len, int64_t& pos); \
    inline int64_t get_serialize_size(void) const

#define VIRTUAL_NEED_SERIALIZE_AND_DESERIALIZE \
virtual int serialize(char* buf, const int64_t buf_len, int64_t& pos) const; \
  virtual int deserialize(const char* buf, const int64_t data_len, int64_t& pos); \
    virtual int64_t get_serialize_size(void) const

#define PURE_VIRTUAL_NEED_SERIALIZE_AND_DESERIALIZE \
virtual int serialize(char* buf, const int64_t buf_len, int64_t& pos) const = 0; \
  virtual int deserialize(const char* buf, const int64_t data_len, int64_t& pos) = 0; \
    virtual int64_t get_serialize_size(void) const = 0

#define DEFINE_SERIALIZE(TypeName) \
  int TypeName::serialize(char* buf, const int64_t buf_len, int64_t& pos) const


#define DEFINE_DESERIALIZE(TypeName) \
  int TypeName::deserialize(const char* buf, const int64_t data_len, int64_t& pos)

#define DEFINE_GET_SERIALIZE_SIZE(TypeName) \
  int64_t TypeName::get_serialize_size(void) const


#define DATABUFFER_SERIALIZE_INFO \
  data_buffer_.get_data(), data_buffer_.get_capacity(), data_buffer_.get_position()

#ifndef UNUSED
#define UNUSED(v) ((void)(v))
#endif

#define OB_LIKELY(x)       __builtin_expect(!!(x),1)
#define OB_UNLIKELY(x)     __builtin_expect(!!(x),0)

#define ARRAYSIZEOF(a) (sizeof(a)/sizeof(a[0]))

#define OB_ASSERT(x) do{ if(!(x)) {jlog(ERROR, "assert fail, exp=%s", #x); BACKTRACE(); }assert(x);} while(false)

#define ATOMIC_CAS(val, cmpv, newv) __sync_val_compare_and_swap((val), (cmpv), (newv))
#define ATOMIC_ADD(val, addv) __sync_add_and_fetch((val), (addv))
#define ATOMIC_SUB(val, subv) __sync_sub_and_fetch((val), (subv))
#define ATOMIC_INC(val) __sync_add_and_fetch((val), 1)
#define ATOMIC_DEC(val) __sync_sub_and_fetch((val), 1)
#define __COMPILER_BARRIER() asm volatile("" ::: "memory")
#define PAUSE() asm("pause\n")


#define CACHE_ALIGN_SIZE 64
#define CACHE_ALIGNED __attribute__((aligned(CACHE_ALIGN_SIZE)))
#define DIO_ALIGN_SIZE 512
const int64_t OB_SERVER_VERSION_LENGTH = 64;

#if 0
#define OB_STAT_INC(module, args...) \
  do { \
    ObStatManager *mgr = ObStatSingleton::get_instance(); \
    if (NULL != mgr) { mgr->inc(OB_STAT_##module, 0/*table id*/, ##args); } \
  }while(0)


#define OB_STAT_SET(module, args...) \
  do { \
    ObStatManager *mgr = ObStatSingleton::get_instance(); \
    if (NULL != mgr) { mgr->set_value(OB_STAT_##module, 0, /* table id */ ##args); } \
  }while(0)


#define OB_STAT_GET(module, args...) \
  do { \
    ObStatManager *mgr = ObStatSingleton::get_instance(); \
    if (NULL != mgr) { mgr->get_stat(OB_STAT_##module, 0, ##args); } \
  }while(0)


#define OB_STAT_TABLE_INC(module, table_id, args...) \
  do { \
    ObStatManager *mgr = ObStatSingleton::get_instance(); \
    if (NULL != mgr) { mgr->inc(OB_STAT_##module,(table_id), ##args); } \
  }while(0)



#define OB_STAT_TABLE_SET(module, table_id, args...) \
  do { \
    ObStatManager *mgr = ObStatSingleton::get_instance(); \
    if (NULL != mgr) { mgr->set_value(OB_STAT_##module, (table_id), ##args); } \
  }while(0)


#define OB_STAT_TABLE_GET(module, table_id, args...) \
  do { \
    ObStatManager *mgr = ObStatSingleton::get_instance(); \
    if (NULL != mgr) { mgr->get_stat(OB_STAT_##module, (table_id), ##args); } \
  }while(0)

#endif


#endif // COMMON_DEFINE_H_
