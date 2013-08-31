/************************************************************
  Copyright (C), 2013-2015
  FileName:     sql_decomposer.h
  Author:       qinbo(gqinbo@gmail.com)      
  Version :          
  Date:         
  Description:  sql语句分拆优化模块   
  History: 
      <author>  <time>   <version >     <desc>
      qinbo    2013/6/5     1.0         build this moudle  
***********************************************************/
#ifndef __SQL_DECOMPOSER_H_
#define __SQL_DECOMPOSER_H_

#include "hds_base.h"

#define PTR_ARRAY                   GPtrArray
#define Build_ptr_array             g_ptr_array_new 
#define Add_to_ptr_array            g_ptr_array_add 
#define Get_ptr_array_elem          g_ptr_array_index
#define Free_ptr_array(ptr_array)   g_ptr_array_free(ptr_array, TRUE) 

#define SQL_SUCCESS                 0
#define SQL_ERR_BEGIN               1000
#define SQL_ERR_PARSER_SYNTAX       (SQL_ERR_BEGIN + 1)


/********************************************************
                    STRUCTURES
*********************************************************/
/*store sql decomposer result*/
typedef struct _SQL_DECOMPOSER_ELEM 
{
    char        *sql;
} SQL_DECOMPOSER_ELEM;

typedef enum {
    SQL_DECOMPOSER_ERR_OK = 0,
    SQL_DECOMPOSER_ERR_UNKNOWN_CMD
} SQL_DECOMPOSER_ERROR;

#endif /*__SQL_DECOMPOSER_H_*/
