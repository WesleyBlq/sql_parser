/* 
 * File:   dispatch_command.h
 * Author: tangchao
 *
 * Created on 2013年10月31日, 下午3:05
 */

#ifndef DISPATCH_COMMAND_H
#define	DISPATCH_COMMAND_H
#include <mysql.h>
#include <vector>
#include <string>
#include "../server/connection.h"

#define QUERY_WRITE     0    
#define QUERY_READ      1
   
using namespace std;

class dispatchCommand
{
public:

    dispatchCommand()
    {
    }

    dispatchCommand(const dispatchCommand& orig)
    {
    }

    virtual ~dispatchCommand()
    {
    }
    virtual int read_or_write() = 0;
    virtual bool execute_command(Connection *conn) = 0;
    virtual bool dispatch(Connection *conn, unsigned char* buf) = 0;
    virtual int get_error() = 0;
};

class dispatch_command : public dispatchCommand
{
public:

    dispatch_command();
    dispatch_command(const dispatch_command& orig);
    virtual ~dispatch_command();

    bool execute_command(Connection *conn);
    bool dispatch(Connection *conn, unsigned char* buf);
    int get_error();
    int read_or_write();
    void debug(int command);

private:
    struct cuh
    {
        Connection* conn;
        string user;
        string host;
    };
    
    void com_refresh(Connection *conn);
    void flush_all_privileges(vector<cuh>& connections);
private:
    int error;
    int r_or_w;
    vector<string> dictDatabase;
};

#endif	/* DISPATCH_COMMAND_H */

