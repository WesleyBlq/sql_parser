/* 
 * File:   dispatch_command.cpp
 * Author: tangchao
 * 
 * Created on 2013年10月31日, 下午3:05
 */

/* All command is here.
 * First parse is parse protocol.
 * Second parse is parse command from client and execute some command.
 * Third parse is parse query and explain plan.
 * In fact, this is a complicated process.
 */

#include <pthread.h>
#include "../acl/sql_acl.h"
#include "../acl/privileges.h"
#include "../log/log.h"
#include "../include/jderror.h"
#include "dispatch_command.h"

extern pthread_mutex_t flush_mutex;

using namespace jdbd;
using namespace jdbd::sql;

dispatch_command::dispatch_command() : error(0), r_or_w(QUERY_READ)
{
    //dictDatabase.push_back("mysql");
    dictDatabase.push_back("information_schema");
}

dispatch_command::dispatch_command(const dispatch_command& orig)
{
}

dispatch_command::~dispatch_command()
{
}

void dispatch_command::flush_all_privileges()
{
    flush_acl();
    return;
}

/**************************************************************
Function:com_refresh
Description:Reload configs & flush memory.
Author:tangchao
Date:
Input:
Output:
Return:
Other:
 **************************************************************/
void dispatch_command::com_refresh(Connection *conn)
{
    string user;
    string host;
    
    pthread_mutex_lock(&flush_mutex);

    user = conn->getUser();
    host = conn->getHost();

    /* If super user, we reload acl. */
    if (!acl_check(user, host, SUPER_PRIV))
    {
        jlog(WARNING, "%s@%s reload acl has not enought privileges.",
                user.c_str(), host.c_str());
        conn->queryError(ERROR_ACCESS_DENY_REFRESH,
                "ERROR_ACCESS_DENY_REFRESH");
        goto failed;
    }


    /* reload acl */
    flush_all_privileges();

    /* find schema in current connection. */
    if (!acl_check(user, host))
    {
        conn->queryError(ERROR_ACCESS_RELOAD_ACL_ERROR,
                "drop itself.");
        jlog(WARNING, "User %s@%s drop itself!");
        goto failed;
    }
    
    /* add in here. */
    conn->sendOk(2, 0, 0, 0, "Query OK");

failed:
    pthread_mutex_unlock(&flush_mutex);
    return;
}

/**************************************************************
Function:dispatch
Description:dispatch command for server, the command(buf) came from client,
 * we find and distinguish between it.
Author:tangchao
Date:
Input:
Output:
Return:true or false
Other:
 **************************************************************/
bool dispatch_command::dispatch(Connection *conn, unsigned char* buf)
{
    bool res = true;
    enum enum_server_command command = (enum enum_server_command)buf[0];

    /* buff[0] is command from client. */
    conn->SetRequest(buf + 1);
    error = 0;

    /* Because the structure is not reasonable, many do not support. */
    debug(command);
    switch (command)
    {
        case COM_INIT_DB:
        {
            /* change db */
            conn->setDb((const char*) conn->getRequest());
            conn->sendOk(2, 0, 0, 0, "JDDB OK");
            goto toWaitting;
        }
        case COM_CHANGE_USER:
        {
            /* not support */
            conn->queryError(ERROR_ACCESS_DO_NOT_SUPPORT,
                    "ERROR_ACCESS_DO_NOT_SUPPORT");
            goto toWaitting;
        }
        case COM_STMT_EXECUTE:
        {
            /* Prepared statement:execute a previously prepared statement. */
            conn->queryError(ERROR_ACCESS_DO_NOT_SUPPORT,
                    "ERROR_ACCESS_DO_NOT_SUPPORT");
            goto toWaitting;
        }
        case COM_STMT_FETCH:
        {
            /* Prepared statement:fetches requested amount of rows from cursor. */
            conn->queryError(ERROR_ACCESS_DO_NOT_SUPPORT,
                    "ERROR_ACCESS_DO_NOT_SUPPORT");
            goto toWaitting;
        }
        case COM_STMT_SEND_LONG_DATA:
        {
            /* Handle long data in pieces from client. */
            conn->queryError(ERROR_ACCESS_DO_NOT_SUPPORT,
                    "ERROR_ACCESS_DO_NOT_SUPPORT");
            goto toWaitting;
        }
        case COM_STMT_PREPARE:
        {
            /* Prepared statement:create a prepared statement from it 
             * and send PS info back to the client. */
            conn->queryError(ERROR_ACCESS_DO_NOT_SUPPORT,
                    "ERROR_ACCESS_DO_NOT_SUPPORT");
            goto toWaitting;
        }
        case COM_STMT_CLOSE:
        {
            /* Delete a prepared statement from memory. */
            conn->queryError(ERROR_ACCESS_DO_NOT_SUPPORT,
                    "ERROR_ACCESS_DO_NOT_SUPPORT");
            goto toWaitting;
        }
        case COM_STMT_RESET:
        {
            /* Reset a prepared statement in case there was a recoverable error. */
            conn->queryError(ERROR_ACCESS_DO_NOT_SUPPORT,
                    "ERROR_ACCESS_DO_NOT_SUPPORT");
            goto toWaitting;
        }
        case COM_QUERY:
        {
            /* execute sql parse */
            if (conn->getRequest())
            {
                conn->setStatus(CONN_JOB_GENERATE);
            }
            break;
        }
        case COM_FIELD_LIST: // This isn't actually needed
        {
            /*
             * 1. Init TABLE_LIST
             * 2. Send field list
             */
            conn->queryError(ERROR_ACCESS_DO_NOT_SUPPORT,
                    "ERROR_ACCESS_DO_NOT_SUPPORT");
            goto toWaitting;
            break;
        }
        case COM_QUIT:
        {
            /* We don't calculate statistics for this command */
            conn->setStatus(CONN_QUIT);
            break;
        }
        case COM_BINLOG_DUMP:
        {
            goto toWaitting;
            break;
        }
        case COM_REFRESH:
        {
            /*
             * Reload configs & flush memory.
             */
            com_refresh(conn);
            goto toWaitting;
            break;
        }
        case COM_SHUTDOWN:
        {
            /* clean & close */
            break;
        }
        case COM_STATISTICS:
        {
            /* mysql client command, status. */
            conn->queryError(ERROR_ACCESS_DENY_COM_STATISTICS,
                    "Sorry, blue dolphin have not this function.");
            goto toWaitting;
        }
        case COM_PING:
        {
            /* tell client we are ok. */
            conn->sendOk(2, 0, 0, 0, "OK");
            goto toWaitting;
        }
        case COM_PROCESS_INFO:
        {
            /* show processlist. */
            conn->queryError(ERROR_ACCESS_DO_NOT_SUPPORT,
                    "ERROR_ACCESS_DO_NOT_SUPPORT");
            goto toWaitting;
        }
        case COM_PROCESS_KILL:
        {
            /* kill process, we do not support. */
            conn->queryError(ERROR_ACCESS_DO_NOT_SUPPORT,
                    "ERROR_ACCESS_DO_NOT_SUPPORT");
            goto toWaitting;
        }
        case COM_SET_OPTION:
        {
            uint opt_command = uint2korr(conn->getRequest());

            switch (opt_command)
            {
                case (int) MYSQL_OPTION_MULTI_STATEMENTS_ON:
                    //client_capabilities |= CLIENT_MULTI_STATEMENTS;
                    break;
                case (int) MYSQL_OPTION_MULTI_STATEMENTS_OFF:
                    //client_capabilities &= ~CLIENT_MULTI_STATEMENTS;
                    break;
                default:
                    conn->queryError(ERROR_SQL_UNKNOWN_COMMAND, "ERROR_SQL_UNKNOWN_COMMAND");
                    goto toWaitting;
            }
            break;
        }
        case COM_DEBUG:
        {
            /* print all variables into log. */
            break;
        }
        case COM_SLEEP:
        case COM_CONNECT: // Impossible here
        case COM_TIME: // Impossible from client
        case COM_DELAYED_INSERT:
        case COM_END:
        default:
        {
            conn->queryError(ERROR_SQL_UNKNOWN_COMMAND, "ERROR_SQL_UNKNOWN_COMMAND");
            goto toWaitting;
        }
    }

    return res;

toWaitting:
    res = false;
    return res;
}


/**************************************************
Funtion     :   execute_command
Author      :   tangchao
Date        :   2013.11.20
Description :   We sent some query to SCHEMA dictionary, sent some query to 
                data node. If query database is mysql or information_schema, it is sent to
                dictionnary. And if some query type should be sent to dictionnary, we set
                flag. And last, we set read/write flag.
Input       :   
Output      :   true or false
return      :   
**************************************************/
bool dispatch_command::execute_command(Connection *conn)
{
    QueryActuator *query = NULL;
    bool dict_or_dataNode = false;
    string user;
    string host;
    string db;
    int queryType = 0;
    vector<string>::iterator iter;
    error = 0;
    r_or_w = QUERY_READ;

    jlog(INFO, "enter dispatch_command::execute_command");

    if (NULL == conn)
    {
        jlog(FATAL, "Hit a bug.");
        return dict_or_dataNode;
    }

    query = conn->getQueryActuator();
    if (NULL == query)
    {
        jlog(FATAL, "Hit a bug.");
        return dict_or_dataNode; //for compiler through
    }
    
    queryType = query->get_query_type();
    db = query->get_result_plan().meta_db_name;

    /* If query database is information_schema or mysql, 
     * it is sent to dictionnary */
    for (iter = dictDatabase.begin(); iter != dictDatabase.end(); iter++)
    {
        if (!db.compare(*iter))
        {
            dict_or_dataNode = true;
        }
    }

    user = conn->getUser();
    host = conn->getHost();
    jlog(INFO, "query type %d", queryType);
    /* convenient */
    switch (queryType)
    {
            /* Should be sent to information_schema */
        case ObBasicStmt::T_SHOW_DATABASES:
        case ObBasicStmt::T_SHOW_TABLES:
        case ObBasicStmt::T_SHOW_VARIABLES:
        case ObBasicStmt::T_SHOW_COLUMNS:
        case ObBasicStmt::T_SHOW_SCHEMA:
        case ObBasicStmt::T_SHOW_CREATE_TABLE:
        case ObBasicStmt::T_SHOW_TABLE_STATUS:
        case ObBasicStmt::T_SHOW_SERVER_STATUS:
        case ObBasicStmt::T_SHOW_WARNINGS:
        case ObBasicStmt::T_SHOW_GRANTS:
        case ObBasicStmt::T_SHOW_PARAMETERS:
        case ObBasicStmt::T_SHOW_PROCESSLIST:
        case ObBasicStmt::T_VARIABLE_SET:
        {
            dict_or_dataNode = true;
        }
            break;
    }

    /* convenient */
    switch (queryType)
    {
            /* Read from database */
        case ObBasicStmt::T_SHOW_DATABASES:
        case ObBasicStmt::T_SHOW_TABLES:
        case ObBasicStmt::T_SHOW_VARIABLES:
        case ObBasicStmt::T_SHOW_COLUMNS:
        case ObBasicStmt::T_SHOW_SCHEMA:
        case ObBasicStmt::T_SHOW_CREATE_TABLE:
        case ObBasicStmt::T_SHOW_TABLE_STATUS:
        case ObBasicStmt::T_SHOW_SERVER_STATUS:
        case ObBasicStmt::T_SHOW_WARNINGS:
        case ObBasicStmt::T_SHOW_GRANTS:
        case ObBasicStmt::T_SHOW_PARAMETERS:
        case ObBasicStmt::T_SHOW_PROCESSLIST:
        case ObBasicStmt::T_SELECT:
        {
            r_or_w = QUERY_READ;
        }
            break;
            /* Write from database */
        case ObBasicStmt::T_VARIABLE_SET:
        case ObBasicStmt::T_DELETE:
        case ObBasicStmt::T_REPLACE:
        case ObBasicStmt::T_UPDATE:
        case ObBasicStmt::T_INSERT:
        {
            r_or_w = QUERY_WRITE;
        }
            break;
    }

    /* convenient */
    switch (queryType)
    {
            /* Read from database */
        case ObBasicStmt::T_SHOW_SCHEMA:
        case ObBasicStmt::T_SHOW_DATABASES:
        case ObBasicStmt::T_SHOW_TABLES:
        case ObBasicStmt::T_SHOW_COLUMNS:
        case ObBasicStmt::T_SHOW_VARIABLES:
        case ObBasicStmt::T_SHOW_CREATE_TABLE:
        case ObBasicStmt::T_SHOW_TABLE_STATUS:
        {
            break;
        }
        case ObBasicStmt::T_SELECT:
        {
            if (!acl_check(user, host, conn->getDb(), "tt", SELECT_PRIV))
            {
                error = ERROR_ACCESS_DENY_SELECT_TABLE;
            }
        }
            break;
            /* Write from database */
        case ObBasicStmt::T_DELETE:
        {
            if (!acl_check(user, host, conn->getDb(), "tt", DELETE_PRIV))
            {
                error = ERROR_ACCESS_DENY_SELECT_TABLE;
            }
        }
            break;
        case ObBasicStmt::T_VARIABLE_SET:
        case ObBasicStmt::T_REPLACE:
        {
            if (!acl_check(user, host, conn->getDb(), "tt", INSERT_PRIV))
            {
                error = ERROR_ACCESS_DENY_INSERT_TABLE;
            }
        }
            break;
        case ObBasicStmt::T_UPDATE:
        {
            if (!acl_check(user, host, conn->getDb(), "tt", UPDATE_PRIV))
            {
                error = ERROR_ACCESS_DENY_UPDATE_TABLE;
            }
        }
            break;
        case ObBasicStmt::T_SHOW_SERVER_STATUS:
        case ObBasicStmt::T_SHOW_WARNINGS:
        case ObBasicStmt::T_SHOW_GRANTS:
        case ObBasicStmt::T_SHOW_PARAMETERS:
        case ObBasicStmt::T_SHOW_PROCESSLIST:
        {
            if (!acl_check(user, host, SUPER_PRIV))
            {
                error = ERROR_ACCESS_DENY_NO_SUPER_PRIVILEGE;
            }
            break;
        }
    }

    /* specific */

    if (query->get_result_plan().is_show_sys_var)
    {
        dict_or_dataNode = true;
        r_or_w = QUERY_READ;
        error = 0;
    }

    jlog(INFO, "Query should be sent to %s, execute %s.",
            dict_or_dataNode ? "schema dictionary" : "data node",
            r_or_w ? "read" : "write");

    return dict_or_dataNode;
}

/**************************************************
Funtion     :   read_or_write
Author      :   tangchao
Date        :   2013.11.20
Description :   return query type, read or write.
Input       :   
Output      :   true or false
return      :   
**************************************************/
int dispatch_command::read_or_write()
{
    return this->r_or_w;
}

/**************************************************
Funtion     :   get_error
Author      :   tangchao
Date        :   2013.11.20
Description :    
Input       :   
Output      :   
return      :   
**************************************************/
int dispatch_command::get_error()
{
    return error;
}

/**************************************************
Funtion     :   debug
Author      :   tangchao
Date        :   2013.11.20
Description :   my debug, i think put here it's ok.
Input       :   
Output      :   
return      :   
**************************************************/
void dispatch_command::debug(int command)
{
    switch (command)
    {
        case COM_INIT_DB:
        {
            jlog(INFO, "COM_INIT_DB");
            break;
        }
        case COM_CHANGE_USER:
        {
            jlog(INFO, "COM_CHANGE_USER");
            break;
        }
        case COM_STMT_EXECUTE:
        {
            jlog(INFO, "COM_STMT_EXECUTE");
            break;
        }
        case COM_STMT_FETCH:
        {
            jlog(INFO, "COM_STMT_FETCH");
            break;
        }
        case COM_STMT_SEND_LONG_DATA:
        {
            jlog(INFO, "COM_STMT_SEND_LONG_DATA");
            break;
        }
        case COM_STMT_PREPARE:
        {
            jlog(INFO, "COM_STMT_PREPARE");
            break;
        }
        case COM_STMT_CLOSE:
        {
            jlog(INFO, "COM_STMT_CLOSE");
            break;
        }
        case COM_STMT_RESET:
        {
            jlog(INFO, "COM_STMT_RESET");
            break;
        }
        case COM_QUERY:
        {
            jlog(INFO, "COM_QUERY");
            break;
        }
        case COM_FIELD_LIST: // This isn't actually needed
        {
            jlog(INFO, "COM_FIELD_LIST");
            break;
        }
        case COM_QUIT:
        {
            jlog(INFO, "COM_QUIT");

            break;
        }
        case COM_BINLOG_DUMP:
        {
            jlog(INFO, "COM_BINLOG_DUMP");
            break;
        }
        case COM_REFRESH:
        {
            jlog(INFO, "COM_REFRESH");

            break;
        }
        case COM_SHUTDOWN:
        {
            jlog(INFO, "COM_SHUTDOWN");
            break;
        }
        case COM_STATISTICS:
        {
            jlog(INFO, "COM_STATISTICS");

            break;
        }
        case COM_PING:
        {
            jlog(INFO, "COM_PING");

            break;
        }
        case COM_PROCESS_INFO:
        {
            jlog(INFO, "COM_PROCESS_INFO");
            break;
        }
        case COM_PROCESS_KILL:
        {
            jlog(INFO, "COM_PROCESS_KILL");
            break;
        }
        case COM_SET_OPTION:
        {
            jlog(INFO, "COM_SET_OPTION");
            break;
        }
        case COM_DEBUG:
        {
            jlog(INFO, "COM_DEBUG");
            break;
        }
        case COM_SLEEP:
        {
            jlog(INFO, "COM_SLEEP");
            break;
        }
        case COM_CONNECT: // Impossible here
        {
            jlog(INFO, "COM_CONNECT");
            break;
        }
        case COM_TIME: // Impossible from client
        {
            jlog(INFO, "COM_TIME");
            break;
        }
        case COM_DELAYED_INSERT:
        {
            jlog(INFO, "COM_DELAYED_INSERT");
            break;
        }
        case COM_END:
        {
            jlog(INFO, "COM_END");
            break;
        }
        default:
        {
            jlog(INFO, "Unknown command.");
            break;
        }
    }
}
