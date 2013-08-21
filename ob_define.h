/*
 *   (C) 2007-2010 Taobao Inc.
 *
 *
 *
 *   Version: 0.1
 *
 *   Authors:
 *      qushan <qushan@taobao.com>
 *        - some work details if you want
 *      Author Name ...
 *
 */
#ifndef OCEANBASE_COMMON_OB_DEFINE_H_
#define OCEANBASE_COMMON_OB_DEFINE_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <openssl/md5.h>

namespace oceanbase
{
  namespace common
  {
    const int OB_SUCCESS = EXIT_SUCCESS;
    const int OB_ERROR = EXIT_FAILURE;

    const uint16_t OB_COMPACT_COLUMN_INVALID_ID = UINT16_MAX;
    const uint64_t OB_INVALID_ID = UINT64_MAX;
    const int OB_INVALID_INDEX = -1;
    const int64_t OB_INVALID_VERSION = -1;
    const int64_t OB_MAX_ITERATOR = 16;

    //////////////////////////////////////////////////////////////// begin ob error code
    //error code for common -1 ---- -1000
    const int OB_OBJ_TYPE_ERROR = -1;
    const int OB_INVALID_ARGUMENT = -2;
    const int OB_ARRAY_OUT_OF_RANGE = -3;
    const int OB_SERVER_LISTEN_ERROR = -4;
    const int OB_INIT_TWICE = -5;
    const int OB_NOT_INIT = -6;
    const int OB_NOT_SUPPORTED = -7;
    const int OB_ITER_END = -8;
    const int OB_IO_ERROR = -9;
    const int OB_ERROR_FUNC_VERSION = -10;
    const int OB_PACKET_NOT_SENT = -11;
    const int OB_RESPONSE_TIME_OUT = -12;
    const int OB_ALLOCATE_MEMORY_FAILED = -13;
    const int OB_MEM_OVERFLOW = -14;
    const int OB_ERR_SYS = -15;
    const int OB_ERR_UNEXPECTED = -16;
    const int OB_ENTRY_EXIST = -17;
    const int OB_ENTRY_NOT_EXIST = -18;
    const int OB_SIZE_OVERFLOW = -19;
    const int OB_REF_NUM_NOT_ZERO = -20;
    const int OB_CONFLICT_VALUE = -21;
    const int OB_ITEM_NOT_SETTED = -22;
    const int OB_EAGAIN = -23;
    const int OB_BUF_NOT_ENOUGH = -24;
    const int OB_PARTIAL_FAILED = -25;
    const int OB_READ_NOTHING = -26;
    const int OB_FILE_NOT_EXIST = -27;
    const int OB_DISCONTINUOUS_LOG = -28;
    const int OB_SCHEMA_ERROR = -29;
    const int OB_DATA_NOT_SERVE = -30;       // not host this data
    const int OB_UNKNOWN_OBJ = -31;
    const int OB_NO_MONITOR_DATA = -32;
    const int OB_SERIALIZE_ERROR = -33;
    const int OB_DESERIALIZE_ERROR = -34;
    const int OB_AIO_TIMEOUT = -35;
    const int OB_NEED_RETRY = -36; // need retry
    const int OB_TOO_MANY_SSTABLE = -37;
    const int OB_NOT_MASTER = -38; // !!! don't modify this value, OB_NOT_MASTER = -38
    const int OB_TOKEN_EXPIRED = -39;
    const int OB_ENCRYPT_FAILED = -40;
    const int OB_DECRYPT_FAILED = -41;
    const int OB_USER_NOT_EXIST = -42;
    const int OB_PASSWORD_WRONG = -43;
    const int OB_SKEY_VERSION_WRONG = -44;
    const int OB_NOT_A_TOKEN = -45;
    const int OB_NO_PERMISSION = -46;
    const int OB_COND_CHECK_FAIL = -47;
    const int OB_NOT_REGISTERED = -48;
    const int OB_PROCESS_TIMEOUT = -49;
    const int OB_NOT_THE_OBJECT = -50;
    const int OB_ALREADY_REGISTERED = -51;
    const int OB_LAST_LOG_RUINNED = -52;
    const int OB_NO_CS_SELECTED = -53;
    const int OB_NO_TABLETS_CREATED = -54;
    const int OB_INVALID_ERROR = -55;
    const int OB_CONN_ERROR = -56;
    const int OB_DECIMAL_OVERFLOW_WARN = -57;
    const int OB_DECIMAL_UNLEGAL_ERROR = -58;
    const int OB_OBJ_DIVIDE_BY_ZERO = -59;
    const int OB_OBJ_DIVIDE_ERROR = -60;
    const int OB_NOT_A_DECIMAL = -61;
    const int OB_DECIMAL_PRECISION_NOT_EQUAL = -62;
    const int OB_EMPTY_RANGE = -63; // get emptry range
    const int OB_SESSION_KILLED = -64;
    const int OB_LOG_NOT_SYNC = -65;
    const int OB_DIR_NOT_EXIST = -66;
    const int OB_NET_SESSION_END = -67;
    const int OB_INVALID_LOG = -68;
    const int OB_FOR_PADDING = -69;
    const int OB_INVALID_DATA = -70;
    const int OB_ALREADY_DONE = -71;
    const int OB_CANCELED = -72;
    const int OB_LOG_SRC_CHANGED = -73;
    const int OB_LOG_NOT_ALIGN = -74;
    const int OB_LOG_MISSING = -75;
    const int OB_NEED_WAIT = -76;
    const int OB_NOT_IMPLEMENT = -77;
    const int OB_DIVISION_BY_ZERO = -78;
    const int OB_VALUE_OUT_OF_RANGE = -79;
    const int OB_EXCEED_MEM_LIMIT = -80;
    const int OB_RESULT_UNKNOWN = -81;
    const int OB_ERR_DATA_FORMAT = -82;
    const int OB_MAYBE_LOOP = -83;
    const int OB_NO_RESULT= -84;
    const int OB_QUEUE_OVERFLOW = -85;
    const int OB_LOCK_NOT_MATCH = -100;
    const int OB_DEAD_LOCK = -101;
    const int OB_PARTIAL_LOG = -102;
    const int OB_CHECKSUM_ERROR = -103;
    const int OB_INIT_FAIL = -104;
    const int OB_READ_ZERO_LOG = -110;
    const int OB_SWITCH_LOG_NOT_MATCH = -111;
    const int OB_LOG_NOT_START = -112;
    const int OB_IN_FATAL_STATE = -113;
    const int OB_IN_STOP_STATE = -114;
    const int OB_UPS_MASTER_EXISTS = -115;
    const int OB_LOG_NOT_CLEAR = -116;
    const int OB_FILE_ALREADY_EXIST = -117;
    const int OB_UNKNOWN_PACKET = -118;
    const int OB_TRANS_ROLLBACKED = -119;
    const int OB_LOG_TOO_LARGE = -120;

    const int OB_RPC_SEND_ERROR = -121;
    const int OB_RPC_POST_ERROR = -122;
    const int OB_LIBEASY_ERROR = -123;
    const int OB_CONNECT_ERROR = -124;
    const int OB_NOT_FREE = -125;
    const int OB_INIT_SQL_CONTEXT_ERROR = -126;
    const int OB_SKIP_INVALID_ROW = -127;

    const int OB_SYS_CONFIG_TABLE_ERROR = -131;
    const int OB_READ_CONFIG_ERROR = -132;

    const int OB_TRANS_NOT_MATCH = -140;
    const int OB_TRANS_IS_READONLY = -141;
    const int OB_ROW_MODIFIED = -142;
    const int OB_VERSION_NOT_MATCH = -143;
    const int OB_BAD_ADDRESS = -144;
    const int OB_DUPLICATE_COLUMN = -145;
    const int OB_ENQUEUE_FAILED= -146;
    const int OB_INVALID_CONFIG = -147;

    //error code for chunk server -1001 ---- -2000
    const int OB_CS_CACHE_NOT_HIT = -1001;   // 缓存没有命中
    const int OB_CS_TIMEOUT = -1002;         // 超时
    const int OB_CS_TABLET_NOT_EXIST = -1008; // tablet not exist
    const int OB_CS_EAGAIN = -1010;           //重试

    const int OB_GET_NEXT_COLUMN = -1011;
    const int OB_GET_NEXT_ROW = -1012; // for internal use, scan next row.
    //const int OB_DESERIALIZE_ERROR = -1013;//反序列化失败
    const int OB_INVALID_ROW_KEY = -1014;//不合法的rowKey
    const int OB_SEARCH_MODE_NOT_IMPLEMENT = -1015; // search mode not implement, internal error
    const int OB_INVALID_BLOCK_INDEX = -1016; // illegal block index data, internal error
    const int OB_INVALID_BLOCK_DATA = -1017;  // illegal block data, internal error
    const int OB_SEARCH_NOT_FOUND = -1018;    // value not found? for cs_get
    const int OB_BEYOND_THE_RANGE = -1020;    // search key or range not in current tablet
    const int OB_CS_COMPLETE_TRAVERSAL = -1021; //complete traverse block cache
    const int OB_END_OF_ROW = -1022;
    const int OB_CS_MERGE_ERROR = -1024;
    const int OB_CS_SCHEMA_INCOMPATIBLE = -1025;
    const int OB_CS_SERVICE_NOT_STARTED = -1026;
    const int OB_CS_LEASE_EXPIRED = -1027;
    const int OB_CS_MERGE_HAS_TIMEOUT = -1028;
    const int OB_CS_TABLE_HAS_DELETED = -1029;
    const int OB_CS_MERGE_CANCELED = -1030;
    const int OB_CS_COMPRESS_LIB_ERROR = -1031;
    const int OB_CS_OUTOF_DISK_SPACE = -1032;
    const int OB_CS_MIGRATE_IN_EXIST = -1033;
    const int OB_AIO_BUF_END_BLOCK = -1034;
    const int OB_AIO_EOF = -1035;
    const int OB_AIO_BUSY = -1036;
    const int OB_WRONG_SSTABLE_DATA = -1037;
    const int OB_COLUMN_GROUP_NOT_FOUND = -1039;
    const int OB_NO_IMPORT_SSTABLE = -1040;
    const int OB_IMPORT_SSTABLE_NOT_EXIST = -1041;

    //error code for update server -2001 ---- -3000
    const int OB_UPS_TRANS_RUNNING = -2001;     // 事务正在执行
    const int OB_FREEZE_MEMTABLE_TWICE = -2002; // memtable has been frozen
    const int OB_DROP_MEMTABLE_TWICE = -2003;   // memtable has been dropped
    const int OB_INVALID_START_VERSION = -2004; // memtable start version invalid
    const int OB_UPS_NOT_EXIST = -2005;         // not exist
    const int OB_UPS_ACQUIRE_TABLE_FAIL = -2006;// acquire table via version fail
    const int OB_UPS_INVALID_MAJOR_VERSION = -2007;
    const int OB_UPS_TABLE_NOT_FROZEN = -2008;
    const int OB_UPS_CHANGE_MASTER_TIMEOUT = -2009;
    const int OB_FORCE_TIME_OUT = -2010;

    //error code for root server -3001 ---- -4000
    const int OB_ERROR_TIME_STAMP = -3001;
    const int OB_ERROR_INTRESECT = -3002;
    const int OB_ERROR_OUT_OF_RANGE = -3003;
    const int OB_RS_STATUS_INIT = -3004;
    const int OB_IMPORT_NOT_IN_SERVER = -3005;
    const int OB_FIND_OUT_OF_RANGE = -3006;
    const int OB_CONVERT_ERROR = -3007;
    const int OB_MS_ITER_END = -3008;

    //error code for merge server -4000 ---- -5000
    const int OB_INNER_STAT_ERROR = -4001;     // inner stat check error
    const int OB_OLD_SCHEMA_VERSION = -4002;   // find old schema version
    const int OB_INPUT_PARAM_ERROR = -4003;    // check input param error
    const int OB_NO_EMPTY_ENTRY = -4004;       // not find empty entry
    const int OB_RELEASE_SCHEMA_ERROR = -4005; // release schema error
    const int OB_ITEM_COUNT_ERROR = -4006;     // fullfill item count error
    const int OB_OP_NOT_ALLOW = -4007;         // fetch new schema not allowed
    const int OB_CHUNK_SERVER_ERROR = -4008;   // chunk server cached is error
    const int OB_NO_NEW_SCHEMA = -4009;        // no new schema when parse error
    const int OB_MS_SUB_REQ_TOO_MANY = -4010; // too many sub scan request

    // SQL specific error code, -5000 ~ -6000
    const int OB_ERR_SQL_START = -5000;
    const int OB_ERR_PARSER_INIT = -5000;
    const int OB_ERR_PARSE_SQL = -5001;
    const int OB_ERR_RESOLVE_SQL = -5002;
    const int OB_ERR_GEN_PLAN = -5003;
    const int OB_ERR_UNKNOWN_SYS_FUNC = -5004;
    const int OB_ERR_PARSER_MALLOC_FAILED = -5005;
    const int OB_ERR_PARSER_SYNTAX = -5006;
    const int OB_ERR_COLUMN_SIZE = -5007;
    const int OB_ERR_COLUMN_DUPLICATE = -5008;
    const int OB_ERR_COLUMN_UNKNOWN = -5009;
    const int OB_ERR_OPERATOR_UNKNOWN = -5010;
    const int OB_ERR_STAR_DUPLICATE = -5011;
    const int OB_ERR_ILLEGAL_ID = -5012;
    const int OB_ERR_WRONG_POS = -5013;
    const int OB_ERR_ILLEGAL_VALUE = -5014;
    const int OB_ERR_COLUMN_AMBIGOUS = -5015;
    const int OB_ERR_LOGICAL_PLAN_FAILD = -5016;
    const int OB_ERR_SCHEMA_UNSET = -5017;
    const int OB_ERR_ILLEGAL_NAME = -5018;
    const int OB_ERR_TABLE_UNKNOWN = -5019;
    const int OB_ERR_TABLE_DUPLICATE = -5020;
    const int OB_ERR_NAME_TRUNCATE = -5021;
    const int OB_ERR_EXPR_UNKNOWN = -5022;
    const int OB_ERR_ILLEGAL_TYPE = -5023;
    const int OB_ERR_PRIMARY_KEY_DUPLICATE = -5024;
    const int OB_ERR_ALREADY_EXISTS = -5025;
    const int OB_ERR_CREATETIME_DUPLICATE = -5026;
    const int OB_ERR_MODIFYTIME_DUPLICATE = -5027;
    const int OB_ERR_ILLEGAL_INDEX = -5028;
    const int OB_ERR_INVALID_SCHEMA = -5029;
    const int OB_ERR_INSERT_NULL_ROWKEY = -5030; // SQLSTATE '23000'
    const int OB_ERR_COLUMN_NOT_FOUND = -5031;   // SQLSTATE '42S22'
    const int OB_ERR_DELETE_NULL_ROWKEY = -5032;
    const int OB_ERR_INSERT_INNER_JOIN_COLUMN = -5033;
    const int OB_ERR_USER_EMPTY = -5034;
    const int OB_ERR_USER_NOT_EXIST = -5035;
    const int OB_ERR_NO_PRIVILEGE = -5036;
    const int OB_ERR_NO_AVAILABLE_PRIVILEGE_ENTRY = -5037;
    const int OB_ERR_WRONG_PASSWORD = -5038;
    const int OB_ERR_USER_IS_LOCKED = -5039;
    const int OB_ERR_UPDATE_ROWKEY_COLUMN = -5040;
    const int OB_ERR_UPDATE_JOIN_COLUMN = -5041;
    const int OB_ERR_INVALID_COLUMN_NUM = -5042; // SQLSTATE 'S1002'
    const int OB_ERR_PREPARE_STMT_UNKNOWN = -5043; // SQLSTATE 'HY007'
    const int OB_ERR_VARIABLE_UNKNOWN = -5044;
    const int OB_ERR_SESSION_INIT = -5045;
    const int OB_ERR_OLDER_PRIVILEGE_VERSION = -5046;
    const int OB_ERR_LACK_OF_ROWKEY_COL = -5047;
    const int OB_ERR_EXCLUSIVE_LOCK_CONFLICT = -5048;
    const int OB_ERR_SHARED_LOCK_CONFLICT = -5049;
    const int OB_ERR_USER_EXIST = -5050;
    const int OB_ERR_PASSWORD_EMPTY = -5051;
    const int OB_ERR_GRANT_PRIVILEGES_TO_CREATE_TABLE = -5052;
    const int OB_ERR_WRONG_DYNAMIC_PARAM = -5053; // SQLSTATE '07001'
    const int OB_ERR_PARAM_SIZE = -5054;
    const int OB_ERR_FUNCTION_UNKNOWN = -5055;
    const int OB_ERR_CREAT_MODIFY_TIME_COLUMN = -5056;
    const int OB_ERR_MODIFY_PRIMARY_KEY = -5057;
    const int OB_ERR_PARAM_DUPLICATE = -5058;
    const int OB_ERR_TOO_MANY_SESSIONS = -5059;
    const int OB_ERR_TRANS_ALREADY_STARTED = -5060;
    const int OB_ERR_TOO_MANY_PS = -5061;
    const int OB_ERR_NOT_IN_TRANS = -5062;
    const int OB_ERR_HINT_UNKNOWN = -5063;

    const int OB_ERR_SQL_END = -5999;
#define IS_SQL_ERR(e) (OB_ERR_SQL_END >= e && OB_ERR_SQL_START <= e)
    //////////////////////////////////////////////////////////////// end of ob error code

    typedef int64_t    ObDateTime;
    typedef int64_t    ObPreciseDateTime;
    typedef ObPreciseDateTime ObModifyTime;
    typedef ObPreciseDateTime ObCreateTime;

    const int64_t OB_MAX_SQL_LENGTH = 10240;
    const int64_t OB_MAX_SERVER_ADDR_SIZE = 128;
    const uint64_t OB_MAX_VALID_COLUMN_ID = 10240;   // user table max valid column id
    const int64_t OB_MAX_TABLE_NUMBER = 2048;
    const int64_t OB_MAX_JOIN_INFO_NUMBER = 10;
    const int64_t OB_MAX_ROW_KEY_LENGTH = 16384; // 16KB
    const int64_t OB_MAX_ROW_KEY_SPLIT = 32;
    const int64_t OB_MAX_ROWKEY_COLUMN_NUMBER = 16;
    const int64_t OB_MAX_COLUMN_NAME_LENGTH = 128;  //this means we can use 127 chars for a name.
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
    const int64_t OB_MAX_PACKET_LENGTH = 1<<21; // max packet length, 2MB
    const int64_t OB_MAX_ROW_NUMBER_PER_QUERY = 65536;
    const int64_t OB_MAX_BATCH_NUMBER = 100;
    const int64_t OB_MAX_TABLET_LIST_NUMBER = 1<<10;
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
    const int64_t OB_DIRECT_IO_ALIGN = 1<<OB_DIRECT_IO_ALIGN_BITS;
    const int64_t OB_MAX_COMPOSITE_SYMBOL_COUNT = 256;
    const int64_t OB_SERVER_VERSION_LENGTH = 64;
    const int64_t OB_SERVER_TYPE_LENGTH = 64;
    const int64_t OB_MAX_USERNAME_LENGTH = 32;
    const int64_t OB_MAX_PASSWORD_LENGTH = 32;
    const int64_t OB_MAX_CIPHER_LENGTH = MD5_DIGEST_LENGTH * 2;

    const int64_t OB_MAX_RESULT_MESSAGE_LENGTH = 1024;
    const int64_t OB_MAX_LOG_BUFFER_SIZE = 1966080L;  // 1.875MB

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
    const int OB_TBNET_HEADER_LENGTH = 16;  //16 bytes packet header

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
    static const float FLOAT_EPSINON = static_cast<float>(1e-6);
    static const double DOUBLE_EPSINON = 1e-14;

    const uint64_t OB_UPS_MAX_MINOR_VERSION_NUM = 2048;
    const int64_t OB_MAX_COMPACTSSTABLE_NUM = 64;

    enum ObRole
    {
      OB_INVALID = 0,
      OB_ROOTSERVER = 1,  // rs
      OB_CHUNKSERVER = 2, // cs
      OB_MERGESERVER = 3, // ms
      OB_UPDATESERVER = 4,// ups
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
    const char* const OB_ALL_TRIGGER_EVENT_TABLE_NAME= "__all_trigger_event";
    const char* const OB_ALL_SYS_CONFIG_STAT_TABLE_NAME = "__all_sys_config_stat";
    const char* const OB_ALL_CLUSTER = "__all_cluster";
    const char* const OB_ALL_SERVER = "__all_server";
    const char* const OB_ALL_CLIENT = "__all_client";
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
    static const uint64_t OB_TABLES_SHOW_TID = 501; // VIRTUAL TABLES start from 501, they should not be mutated
    static const uint64_t OB_COLUMNS_SHOW_TID = 502;
    static const uint64_t OB_VARIABLES_SHOW_TID = 503;
    static const uint64_t OB_TABLE_STATUS_SHOW_TID = 504;
    static const uint64_t OB_SCHEMA_SHOW_TID = 505;
    static const uint64_t OB_CREATE_TABLE_SHOW_TID = 506;
    static const uint64_t OB_PARAMETERS_SHOW_TID = 507;
    static const uint64_t OB_SERVER_STATUS_SHOW_TID = 508;
    static const uint64_t OB_ALL_SERVER_STAT_TID = 509;
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
    static const int64_t OB_MALLOC_BLOCK_SIZE = 64*1024L;
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

    static const int64_t OB_DEFAULT_SSTABLE_BLOCK_SIZE = 64*1024; // 64KB
    static const int64_t OB_DEFAULT_MAX_TABLET_SIZE = 256*1024*1024; // 256MB
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
#ifndef UNUSED
#define UNUSED(v) ((void)(v))
#endif

#define DATABUFFER_SERIALIZE_INFO \
  data_buffer_.get_data(), data_buffer_.get_capacity(), data_buffer_.get_position()

#define OB_LIKELY(x)       __builtin_expect(!!(x),1)
#define OB_UNLIKELY(x)     __builtin_expect(!!(x),0)

#define ARRAYSIZEOF(a) (sizeof(a)/sizeof(a[0]))

#define OB_ASSERT(x) do{ if(!(x)) TBSYS_LOG(ERROR, "assert fail, exp=%s", #x); assert(x);} while(false)

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




#endif // OCEANBASE_COMMON_DEFINE_H_
