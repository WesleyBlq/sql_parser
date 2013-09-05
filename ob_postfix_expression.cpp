/*
 * (C) 2007-2011 Taobao Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * ob_postfix_expression.cpp is for what ...
 *
 * Version: $id: ob_postfix_expression.cpp, v 0.1 7/29/2011 14:39 xiaochu Exp $
 *
 * Authors:
 *   xiaochu <xiaochu.yh@taobao.com>
 *     - some work details if you want
 *
 * last update:
 * 2012/5/30 change name space oceanbase::common to oceanbase::sql
 *           modify calc interface to adapt ExprItem
 *
 */


#include "ob_postfix_expression.h"
#include "ob_type_convertor.h"
#include "common/utility.h"
#include "common/ob_tsi_factory.h"
#include "common/ob_obj_cast.h"
#include "common/ob_schema.h"
#include "sql/ob_item_type_str.h"
using namespace oceanbase::sql;

namespace oceanbase
{
  namespace sql
  {
    bool ObPostfixExpression::ExprUtil::is_column_idx(const ObObj &obj)
    {
      int64_t val = 0;
      bool ret = true;
      if (OB_SUCCESS != obj.get_int(val) || COLUMN_IDX != val)
      {
        ret = false;
      }
      return ret;
    }
    bool ObPostfixExpression::ExprUtil::is_const_obj(const ObObj &obj)
    {
      int64_t val = 0;
      bool ret = true;
      if (OB_SUCCESS != obj.get_int(val) || CONST_OBJ != val)
      {
        ret = false;
      }
      return ret;
    }
    bool ObPostfixExpression::ExprUtil::is_op(const ObObj &obj)
    {
      int64_t val = 0;
      bool ret = true;
      if (OB_SUCCESS != obj.get_int(val) || OP != val)
      {
        ret = false;
      }
      return ret;
    }
    bool ObPostfixExpression::ExprUtil::is_end(const ObObj &obj)
    {
      int64_t val = 0;
      bool ret = true;
      if (OB_SUCCESS != obj.get_int(val) || END != val)
      {
        ret = false;
      }
      return ret;
    }
    bool ObPostfixExpression::ExprUtil::is_op_of_type(const ObObj &obj, ObItemType type)
    {
      int64_t val = 0;
      bool ret = true;
      if (OB_SUCCESS != obj.get_int(val) || type != val)
      {
        ret = false;
      }
      return ret;
    }

    bool ObPostfixExpression::ExprUtil::is_value(const ObObj &obj, int64_t value)
    {
      int64_t val = 0;
      bool ret = true;
      if (OB_SUCCESS != obj.get_int(val) || value != val)
      {
        ret = false;
      }
      return ret;
    }


    int ExprItem::assign(const common::ObObj &obj)
    {
      int ret = OB_SUCCESS;
      switch(obj.get_type())
      {
        case ObNullType:
          type_ = T_NULL;
          break;
        case ObIntType:
          type_ = T_INT;
          obj.get_int(value_.int_);
          break;
        case ObFloatType:
          type_ = T_FLOAT;
          obj.get_float(value_.float_);
          break;
        case ObDoubleType:
          type_ = T_DOUBLE;
          obj.get_double(value_.double_);
          break;
        case ObPreciseDateTimeType:
          type_ = T_DATE;
          obj.get_precise_datetime(value_.datetime_);
          break;
        case ObVarcharType:
          type_ = T_STRING;
          obj.get_varchar(string_);
          break;
        case ObBoolType:
          type_ = T_BOOL;
          obj.get_bool(value_.bool_);
          break;
        case ObDecimalType:
          ret = OB_NOT_SUPPORTED;
          break;
        default:
          ret = OB_ERR_UNEXPECTED;
          break;
      }
      return ret;
    }

    /*     初始化数学运算操作调用表 */
    op_call_func_t ObPostfixExpression::call_func[T_MAX_OP - T_MIN_OP - 1] = {
      /*   WARNING: 下面的顺序不可以调换，
       *   需要与(ob_item_tpye.h) ExprType enum定义对应
       */
      ObPostfixExpression::minus_func, /* T_OP_NEG */
      ObPostfixExpression::plus_func, /* T_OP_POS */
      ObPostfixExpression::add_func, /* T_OP_ADD */
      ObPostfixExpression::sub_func, /* T_OP_MINUS */
      ObPostfixExpression::mul_func, /* T_OP_MUL */
      ObPostfixExpression::div_func, /* T_OP_DIV */
      ObPostfixExpression::nop_func, /* TODO: T_OP_POW */
      ObPostfixExpression::mod_func, /* T_OP_REM */
      ObPostfixExpression::mod_func, /* T_OP_MOD */
      ObPostfixExpression::eq_func,  /* T_OP_EQ */
      ObPostfixExpression::le_func,  /* T_OP_LE */
      ObPostfixExpression::lt_func,  /* T_OP_LT */
      ObPostfixExpression::ge_func,  /* T_OP_GE */
      ObPostfixExpression::gt_func,  /* T_OP_GT */
      ObPostfixExpression::neq_func, /* T_OP_NE */
      ObPostfixExpression::is_func,  /* T_OP_IS */
      ObPostfixExpression::is_not_func,/* T_OP_IS_NOT */
      ObPostfixExpression::btw_func, /* T_OP_BTW */
      ObPostfixExpression::not_btw_func, /* T_OP_NOT_BTW */
      ObPostfixExpression::like_func,/* T_OP_LIKE */
      ObPostfixExpression::not_like_func, /* T_OP_NOT_LIKE */
      ObPostfixExpression::not_func, /* T_OP_NOT */
      ObPostfixExpression::and_func, /* T_OP_AND */
      ObPostfixExpression::or_func,  /* T_OP_OR */
      ObPostfixExpression::in_func, /*  T_OP_IN */
      ObPostfixExpression::not_in_func, /* T_OP_NOT_IN */
      ObPostfixExpression::arg_case_func, /* T_OP_AGR_CASE */
      ObPostfixExpression::case_func, /* T_OP_CASE */
      ObPostfixExpression::row_func, /* T_OP_ROW */
      ObPostfixExpression::nop_func, /* TODO: T_OP_EXISTS */
      ObPostfixExpression::concat_func, /* T_OP_CNN */
      ObPostfixExpression::nop_func, // T_FUN_SYS
      ObPostfixExpression::left_param_end_func, // T_OP_LEFT_PARAM_END
    };

    // system function table
    op_call_func_t ObPostfixExpression::SYS_FUNCS_TAB[SYS_FUNC_NUM] =
    {
      ObPostfixExpression::sys_func_length, // SYS_FUNC_LENGTH
      ObPostfixExpression::sys_func_substr, // SYS_FUNC_SUBSTR
      ObPostfixExpression::sys_func_cast,             // SYS_FUNC_CAST
      ObPostfixExpression::sys_func_cur_time,         // SYS_FUNC_CUR_TIME
      ObPostfixExpression::sys_func_cur_date,         // SYS_FUNC_CUR_DATE
      ObPostfixExpression::sys_func_cur_timestamp,    // SYS_FUNC_CUR_TIMESTAMP
      ObPostfixExpression::sys_func_cur_user,         // SYS_FUNC_CUR_USER
      ObPostfixExpression::sys_func_trim,             // SYS_FUNC_TRIM
      ObPostfixExpression::sys_func_lower,            // SYS_FUNC_LOWER
      ObPostfixExpression::sys_func_upper,            // SYS_FUNC_UPPER
      ObPostfixExpression::sys_func_coalesce,         // SYS_FUNC_COALESCE
      ObPostfixExpression::sys_func_hex,         // SYS_FUNC_HEX
      ObPostfixExpression::sys_func_unhex,         // SYS_FUNC_UNHEX
      ObPostfixExpression::sys_func_ip_to_int,         // SYS_FUNC_IP_TO_INT
      ObPostfixExpression::sys_func_int_to_ip,         // SYS_FUNC_INT_TO_IP
    };

    const char* const ObPostfixExpression::SYS_FUNCS_NAME[SYS_FUNC_NUM] =
    {
      "length",
      "substr",
      "cast",
      "current_time",
      "current_date",
      "current_timestamp",
      "current_user",
      "trim",
      "lower",
      "upper",
      "coalesce",
      "hex",
      "unhex",
      "ip2int",
      "int2ip"
    };

    int32_t ObPostfixExpression::SYS_FUNCS_ARGS_NUM[SYS_FUNC_NUM] =
    {
      1,
      TWO_OR_THREE,
      2,
      0,
      0,
      0,
      0,
      3,/*trim*/
      1,
      1,
      MORE_THAN_ZERO,
      1,
      1,
      1,
      1
    };

    ObPostfixExpression::ObPostfixExpression()
      :stack_(NULL),
       did_int_div_as_double_(false),
       str_buf_(0, DEF_STRING_BUF_SIZE)
    {
    }

    ObPostfixExpression::~ObPostfixExpression()
    {
    }

    ObPostfixExpression& ObPostfixExpression::operator=(const ObPostfixExpression &other)
    {
      int ret = OB_SUCCESS;
      int i = 0;
      this->expr_.clear();
      if (OB_SUCCESS != (ret = str_buf_.reset()))
      {
        TBSYS_LOG(WARN, "fail to reset string buffer");
      }
      else if (&other != this)
      {
        ObObj obj;
        expr_.reserve(other.expr_.count());
        for (i = 0; i < other.expr_.count(); i++)
        {
          if (ObVarcharType == other.expr_[i].get_type())
          {
            if(OB_SUCCESS != (ret = str_buf_.write_obj(other.expr_[i], &obj)))
            {
              TBSYS_LOG(ERROR, "fail to write object to string buffer. ret=%d", ret);
            }
            else if (OB_SUCCESS != (ret = expr_.push_back(obj)))
            {
              TBSYS_LOG(WARN, "failed to add item, err=%d", ret);
            }
          }
          else
          {
            if (OB_SUCCESS != (ret = expr_.push_back(other.expr_[i])))
            {
              TBSYS_LOG(WARN, "failed to add item, err=%d", ret);
            }
          }
        }
      }
      return *this;
    }

    int ObPostfixExpression::get_sys_func(const common::ObString &sys_func, ObSqlSysFunc &func_type) const
    {
#define OB_POSTFIX_EXPRESSION_GET_SYS_FUNC(SYS_FUNC_ID) \
      else if (sys_func.length() == static_cast<int64_t>(strlen(SYS_FUNCS_NAME[SYS_FUNC_ID])) \
          && 0 == strncasecmp(SYS_FUNCS_NAME[SYS_FUNC_ID], sys_func.ptr(), sys_func.length())) \
      { \
        func_type = SYS_FUNC_ID; \
      }

      int ret = OB_SUCCESS;
      if (0)
      {
        // if (0) so that the macro works
      }
      OB_POSTFIX_EXPRESSION_GET_SYS_FUNC(SYS_FUNC_LENGTH)
      OB_POSTFIX_EXPRESSION_GET_SYS_FUNC(SYS_FUNC_SUBSTR)
      OB_POSTFIX_EXPRESSION_GET_SYS_FUNC(SYS_FUNC_CAST)
      OB_POSTFIX_EXPRESSION_GET_SYS_FUNC(SYS_FUNC_CUR_TIME)
      OB_POSTFIX_EXPRESSION_GET_SYS_FUNC(SYS_FUNC_CUR_DATE)
      OB_POSTFIX_EXPRESSION_GET_SYS_FUNC(SYS_FUNC_CUR_TIMESTAMP)
      OB_POSTFIX_EXPRESSION_GET_SYS_FUNC(SYS_FUNC_CUR_USER)
      OB_POSTFIX_EXPRESSION_GET_SYS_FUNC(SYS_FUNC_TRIM)
      OB_POSTFIX_EXPRESSION_GET_SYS_FUNC(SYS_FUNC_LOWER)
      OB_POSTFIX_EXPRESSION_GET_SYS_FUNC(SYS_FUNC_UPPER)
      OB_POSTFIX_EXPRESSION_GET_SYS_FUNC(SYS_FUNC_COALESCE)
      OB_POSTFIX_EXPRESSION_GET_SYS_FUNC(SYS_FUNC_HEX)
      OB_POSTFIX_EXPRESSION_GET_SYS_FUNC(SYS_FUNC_UNHEX)
      OB_POSTFIX_EXPRESSION_GET_SYS_FUNC(SYS_FUNC_IP_TO_INT)
      OB_POSTFIX_EXPRESSION_GET_SYS_FUNC(SYS_FUNC_INT_TO_IP)
      else
      {
        ret = OB_ERR_UNKNOWN_SYS_FUNC;
      }
      return ret;
#undef OB_POSTFIX_EXPRESSION_GET_SYS_FUNC
    }

    int ObPostfixExpression::add_expr_obj(const ObObj &obj)
    {
      int ret = OB_SUCCESS;
      ObObj obj2;
      if (obj.get_type() == ObVarcharType)
      {
        if (OB_SUCCESS != (ret = str_buf_.write_obj(obj, &obj2)))
        {
          TBSYS_LOG(WARN, "fail to write object to string buffer. err=%d", ret);
        }
        else if (OB_SUCCESS != (ret = expr_.push_back(obj2)))
        {
          TBSYS_LOG(WARN, "fail to push object to expr array. err=%d", ret);
        }
      }
      else if (OB_SUCCESS != (ret = expr_.push_back(obj)))
      {
        TBSYS_LOG(WARN, "fail to push object to expr array. err=%d", ret);
      }
      return ret;
    }

    int ObPostfixExpression::add_expr_item(const ExprItem &item)
    {
      int ret = OB_SUCCESS;
      ObObj item_type;
      ObObj obj, obj2;
      ObSqlSysFunc sys_func;
      switch(item.type_)
      {
        case T_STRING:
        case T_BINARY:
          item_type.set_int(CONST_OBJ);
          obj.set_varchar(item.string_);
          if (OB_SUCCESS != (ret = str_buf_.write_obj(obj, &obj2)))
          {
            TBSYS_LOG(WARN, "fail to write object to string buffer. err=%d", ret);
          }
          else if (OB_SUCCESS != (ret = expr_.push_back(item_type)))
          {}
          else if (OB_SUCCESS != (ret = expr_.push_back(obj2)))
          {}
          break;
        case T_FLOAT:
          item_type.set_int(CONST_OBJ);
          obj.set_float(item.value_.float_);
          if (OB_SUCCESS != (ret = expr_.push_back(item_type)))
          {}
          else if (OB_SUCCESS != (ret = expr_.push_back(obj)))
          {}
          break;
        case T_DOUBLE:
          item_type.set_int(CONST_OBJ);
          obj.set_double(item.value_.double_);
          if (OB_SUCCESS != (ret = expr_.push_back(item_type)))
          {}
          else if (OB_SUCCESS != (ret = expr_.push_back(obj)))
          {}
          break;
        case T_DECIMAL:
          TBSYS_LOG(WARN, "literal as decimal not support yet");
          ret = OB_NOT_SUPPORTED;
          break;
        case T_INT:
          item_type.set_int(CONST_OBJ);
          obj.set_int(item.value_.int_);
          if (OB_SUCCESS != (ret = expr_.push_back(item_type)))
          {}
          else if (OB_SUCCESS != (ret = expr_.push_back(obj)))
          {}
          break;
        case T_BOOL:
          item_type.set_int(CONST_OBJ);
          obj.set_bool(item.value_.bool_);
          if (OB_SUCCESS != (ret = expr_.push_back(item_type)))
          {}
          else if (OB_SUCCESS != (ret = expr_.push_back(obj)))
          {}
          break;
        case T_DATE:
          item_type.set_int(CONST_OBJ);
          obj.set_precise_datetime(item.value_.datetime_);
          if (OB_SUCCESS != (ret = expr_.push_back(item_type)))
          {}
          else if (OB_SUCCESS != (ret = expr_.push_back(obj)))
          {}
          break;
        case T_QUESTIONMARK:
        case T_SYSTEM_VARIABLE:
        case T_TEMP_VARIABLE:
          item_type.set_int(CONST_OBJ);
          obj.set_ext(item.value_.int_);
          TBSYS_LOG(DEBUG, "expr system variable ptr=%p",
                    (void*)item.value_.int_);
          if (OB_SUCCESS != (ret = expr_.push_back(item_type)))
          {}
          else if (OB_SUCCESS != (ret = expr_.push_back(obj)))
          {}
          break;
        case T_NULL:
          item_type.set_int(CONST_OBJ);
          obj.set_null();
          if (OB_SUCCESS != (ret = expr_.push_back(item_type)))
          {}
          else if (OB_SUCCESS != (ret = expr_.push_back(obj)))
          {}
          break;
        case T_REF_COLUMN:
          item_type.set_int(COLUMN_IDX);
          obj.set_int(item.value_.cell_.tid);
          obj2.set_int(item.value_.cell_.cid);
          if (OB_SUCCESS != (ret = expr_.push_back(item_type)))
          {}
          else if (OB_SUCCESS != (ret = expr_.push_back(obj)))
          {}
          else if (OB_SUCCESS != (ret = expr_.push_back(obj2)))
          {}
          break;
        case T_REF_QUERY:
          TBSYS_LOG(ERROR, "TODO... not implement yet");
          ret = OB_NOT_SUPPORTED;
          break;
        case T_OP_EXISTS:
        case T_OP_POS:
        case T_OP_NEG:
        case T_OP_ADD:
        case T_OP_MINUS:
        case T_OP_MUL:
        case T_OP_DIV:
        case T_OP_REM:
        case T_OP_POW:
        case T_OP_MOD:
        case T_OP_LE:
        case T_OP_LT:
        case T_OP_EQ:
        case T_OP_GE:
        case T_OP_GT:
        case T_OP_NE:
        case T_OP_LIKE:
        case T_OP_NOT_LIKE:
        case T_OP_AND:
        case T_OP_OR:
        case T_OP_NOT:
        case T_OP_IS:
        case T_OP_IS_NOT:
        case T_OP_BTW:
        case T_OP_NOT_BTW:
        case T_OP_CNN:
        case T_OP_IN:
        case T_OP_NOT_IN:
        case T_OP_ARG_CASE:
        case T_OP_CASE:
        case T_OP_ROW:
        case T_OP_LEFT_PARAM_END:
          item_type.set_int(OP);
          obj.set_int(item.type_); // op type
          obj2.set_int(item.value_.int_); // operands count
          if (OB_SUCCESS != (ret = expr_.push_back(item_type)))
          {}
          else if (OB_SUCCESS != (ret = expr_.push_back(obj)))
          {}
          else if (OB_SUCCESS != (ret = expr_.push_back(obj2)))
          {}
          break;
        case T_FUN_SYS:
          item_type.set_int(OP);
          obj.set_int(item.type_); // system function
          obj2.set_int(item.value_.int_); // operands count
          if (OB_SUCCESS != (ret = get_sys_func(item.string_, sys_func)))
          {
            TBSYS_LOG(WARN, "unknown system function=%.*s", item.string_.length(), item.string_.ptr());
          }
          else if (OB_SUCCESS != (ret = expr_.push_back(item_type)))
          {}
          else if (OB_SUCCESS != (ret = expr_.push_back(obj)))
          {}
          else if (OB_SUCCESS != (ret = expr_.push_back(obj2)))
          {}
          else
          {
            obj2.set_int(sys_func);
            ret = expr_.push_back(obj2);
          }
          break;
        default:
          TBSYS_LOG(WARN, "unknown expr item type=%d", item.type_);
          ret = OB_INVALID_ARGUMENT;
          break;
      }
      return ret;
    }

    int ObPostfixExpression::add_expr_item_end()
    {
      int ret = OB_SUCCESS;
      ObObj obj;
      obj.set_int(END);
      if (OB_SUCCESS != (ret = expr_.push_back(obj)))
      {
        TBSYS_LOG(WARN, "failed to add END, err=%d", ret);
      }
      return ret;
    }

    int ObPostfixExpression::merge_expr(const ObPostfixExpression &expr1, const ObPostfixExpression &expr2, const ExprItem &op)
    {
      int ret = OB_SUCCESS;
      for(int64_t i = 0; ret == OB_SUCCESS && i < expr1.expr_.count() - 1; i++)
      {
        ret = this->expr_.push_back(expr1.expr_[i]);

      }
      for(int64_t i = 0; ret == OB_SUCCESS && i < expr2.expr_.count() - 1; i++)
      {
        ret = this->expr_.push_back(expr2.expr_[i]);

      }
      if (ret == OB_SUCCESS)
      {
        ret = add_expr_item(op);
      }
      if (ret == OB_SUCCESS)
      {
        ret = add_expr_item_end();
      }
      if (ret != OB_SUCCESS)
      {
        TBSYS_LOG(ERROR, "Generate new expression faild, ret=%d", ret);
      }
      return ret;
    }

    int ObPostfixExpression::calc(const common::ObRow &row, const ObObj *&composite_val)
    {
      int ret = OB_SUCCESS;
      int64_t type = 0;
      int64_t value = 0;
      int64_t value2 = 0;
      int64_t sys_func = 0;
      int idx = 0;
      ObExprObj result;
      int idx_i = 0;
      ObPostExprExtraParams *extra_params = GET_TSI_MULT(ObPostExprExtraParams, TSI_SQL_EXPR_EXTRA_PARAMS_1);
      // get the stack for calculation
      ObPostfixExpressionCalcStack *stack = GET_TSI_MULT(ObPostfixExpressionCalcStack, TSI_SQL_EXPR_STACK_1);
      if (NULL == stack || NULL == extra_params)
      {
        TBSYS_LOG(ERROR, "no memory for postfix expression extra params and stack");
        ret = OB_ALLOCATE_MEMORY_FAILED;
      }
      else
      {
        stack_ = stack->stack_;
        extra_params->did_int_div_as_double_ = did_int_div_as_double_;
      }

      while (OB_SUCCESS == ret)
      {
        // 获得数据类型:列id、数字、操作符、结束标记
        if (OB_SUCCESS != (ret = expr_[idx++].get_int(type)))
        {
          TBSYS_LOG(WARN, "fail to get int value. unexpected! ret=%d idx=%d", ret, idx-1);
          ret = OB_ERR_UNEXPECTED;
          break;
        }
        else if(type <= BEGIN_TYPE || type >= END_TYPE)
        {
          TBSYS_LOG(WARN, "unsupported operand type [type:%ld]", value);
          ret = OB_ERR_UNEXPECTED;
          break;
        }
        else if (END == type)   // expr_中以END符号表示结束
        {
          if (idx_i != 1)
          {
            TBSYS_LOG(WARN, "calculation stack must be empty. check the code for bugs. idx_i=%d", idx_i);
            ret = OB_ERR_UNEXPECTED;
          }
          else if (OB_SUCCESS != (ret = stack_[--idx_i].to(result_)))
          {
            TBSYS_LOG(WARN, "failed to convert exprobj to obj, err=%d", ret);
          }
          else
          {
            composite_val = &result_;
          }
          break;
        }
        else if (idx_i < 0
                 || idx_i >= ObPostfixExpressionCalcStack::STACK_SIZE
                 || idx > expr_.count())
        {
          TBSYS_LOG(WARN,"calculation stack overflow [stack.index:%d] "
                    "or run out of operand [operand.used:%d,operand.avaliable:%ld]", idx_i, idx, expr_.count());
          ret = OB_ERR_UNEXPECTED;
          break;
        }
        else
        {
          // do calculation
          switch(type)
          {
            case COLUMN_IDX:
              if (OB_SUCCESS != (ret = expr_[idx++].get_int(value)))
              {
                TBSYS_LOG(WARN,"get_int error [err:%d]", ret);
              }
              else if (OB_SUCCESS  != (ret = expr_[idx++].get_int(value2)))
              {
                TBSYS_LOG(WARN,"get_int error [err:%d]", ret);
              }
              else
              {
                const ObObj *cell = NULL;
                if (OB_SUCCESS != (ret = row.get_cell(static_cast<uint64_t>(value),
                                                      static_cast<uint64_t>(value2), cell)))
                {
                  TBSYS_LOG(WARN, "fail to get cell from row. err=%d tid=%ld cid=%ld",
                            ret, value, value2);
                }
                else
                {
                  stack_[idx_i++].assign(*cell);
                }
              }
              break;
            case CONST_OBJ:
              if (expr_[idx].get_type() == ObExtendType)
              {
                int64_t obj_addr = common::OB_INVALID_ID;
                expr_[idx++].get_ext(obj_addr);
                TBSYS_LOG(DEBUG, "get ext value=%s addr=%p",
                          to_cstring(*(reinterpret_cast<ObObj *>(obj_addr))),
                          (void*)obj_addr);
                stack_[idx_i++].assign(*(reinterpret_cast<ObObj *>(obj_addr)));
              }
              else
              {
                stack_[idx_i++].assign(expr_[idx++]);
              }
              break;
            case OP:
              // 根据OP的类型，从堆栈中弹出1个或多个操作数，进行计算
              if (OB_SUCCESS != (ret = expr_[idx++].get_int(value)))
              {
                TBSYS_LOG(WARN,"get operator type failed [err:%d]", ret);
              }
              else if (OB_UNLIKELY(value <= T_MIN_OP || value >= T_MAX_OP))
              {
                TBSYS_LOG(WARN,"unsupported operator type [type:%ld]", value);
                ret = OB_ERR_UNEXPECTED;
              }
              else if(OB_SUCCESS != (ret = expr_[idx++].get_int(value2 /*param_count*/)))
              {
                 TBSYS_LOG(WARN,"get_int error [err:%d]", ret);
              }
              else
              {
                extra_params->operand_count_ = static_cast<int32_t>(value2);
                extra_params->str_buf_ = &str_buf_;
                if (OB_UNLIKELY(T_FUN_SYS == value))
                {
                  if(OB_SUCCESS != (ret = expr_[idx++].get_int(sys_func)))
                  {
                    TBSYS_LOG(WARN, "failed to get sys func, err=%d", ret);
                  }
                  else if (0 > sys_func || sys_func >= SYS_FUNC_NUM)
                  {
                    TBSYS_LOG(WARN, "invalid sys function type=%ld", sys_func);
                    ret = OB_ERR_UNEXPECTED;
                  }
                  else if (OB_SUCCESS != (ret = SYS_FUNCS_TAB[sys_func](stack_, idx_i, result, *extra_params)))
                  {
                    TBSYS_LOG(WARN, "failed to call sys func, err=%d func=%ld", ret, sys_func);
                  }
                  else
                  {
                    stack_[idx_i++] = result;
                  }
                }
                else
                {
                  if (OB_LIKELY(OB_SUCCESS == (ret = (this->call_func[value - T_MIN_OP - 1])(stack_, idx_i, result, *extra_params))))
                  {
                    stack_[idx_i++] = result;
                  }
                  else if (OB_NO_RESULT == ret)
                  {
                    // nop
                    ret = OB_SUCCESS;
                  }
                  else
                  {
                    TBSYS_LOG(WARN, "call calculation function error [value:%ld, idx_i:%d, err:%d]",
                              value, idx_i, ret);
                  }
                }
              }
              break;
            default:
              ret = OB_ERR_UNEXPECTED;
              TBSYS_LOG(WARN,"unexpected [type:%ld]", type);
              break;
          } // end switch
        }   // end else
      } // end while

      return ret;
    }


    int ObPostfixExpression::is_const_expr(bool &is_type) const
    {
      return check_expr_type((int64_t)CONST_OBJ, is_type, 3);
    }

    int ObPostfixExpression::is_column_index_expr(bool &is_type) const
    {
      return ObPostfixExpression::check_expr_type((int64_t)COLUMN_IDX, is_type, 4);
    }


    int ObPostfixExpression::check_expr_type(const int64_t type_val, bool &is_type, const int64_t stack_size) const
    {
      int err = OB_SUCCESS;
      int64_t expr_type = -1;
      is_type = false;
      if (expr_.count() == stack_size)
      {
        if (ObIntType == expr_[0].get_type())
        {
          if (OB_SUCCESS != (err = expr_[0].get_int(expr_type)))
          {
            TBSYS_LOG(WARN, "fail to get int value.err=%d", err);
          }
          else if (type_val == expr_type)
          {
            is_type = true;
          }
        }
      }
      return err;
    }

    int ObPostfixExpression::get_column_index_expr(uint64_t &tid, uint64_t &cid, bool &is_type) const
    {
      int err = OB_SUCCESS;
      int64_t expr_type = -1;
      is_type = false;
      if (4 == expr_.count())
      {
        if (ObIntType == expr_[0].get_type())
        {
          if (OB_SUCCESS != (err = expr_[0].get_int(expr_type)))
          {
            TBSYS_LOG(WARN, "fail to get int value.err=%d", err);
          }
          else if ((int64_t)COLUMN_IDX == expr_type)
          {
            if (OB_SUCCESS != (err = expr_[1].get_int((int64_t&)tid)))
            {
              TBSYS_LOG(WARN, "fail to get int value.err=%d", err);
            }
            else if (OB_SUCCESS != (err = expr_[2].get_int((int64_t&)cid)))
            {
              TBSYS_LOG(WARN, "fail to get int value.err=%d", err);
            }
            else
            {
              is_type = true;
            }
          }
        }
      }
      return err;
    }


    inline static bool test_expr_int(const ObPostfixExpression::ExprArray &expr, int i, int64_t expected)
    {
      int64_t val = 0;
      return ObIntType == expr[i].get_type()
        && OB_SUCCESS == expr[i].get_int(val)
        && expected == val;
    }

    bool ObPostfixExpression::is_equijoin_cond(ExprItem::SqlCellInfo &c1, ExprItem::SqlCellInfo &c2) const
    {
      bool ret = false;
      // COL_IDX|tid|cid|COL_IDX|tid|cid|OP|EQ|2|END
      if (expr_.count() == 10)
      {
        if (test_expr_int(expr_, 0, COLUMN_IDX)
            && test_expr_int(expr_, 3, COLUMN_IDX)
            && test_expr_int(expr_, 6, OP)
            && test_expr_int(expr_, 7, T_OP_EQ)
            && test_expr_int(expr_, 8, 2))
        {
          ret = true;
          int64_t val = 0;
          if (ObIntType == expr_[1].get_type()
              && OB_SUCCESS == expr_[1].get_int(val))
          {
            c1.tid = val;
          }
          else
          {
            ret = false;
          }
          if (ObIntType == expr_[2].get_type()
              && OB_SUCCESS == expr_[2].get_int(val))
          {
            c1.cid = val;
          }
          else
          {
            ret = false;
          }
          if (ObIntType == expr_[4].get_type()
              && OB_SUCCESS == expr_[4].get_int(val))
          {
            c2.tid = val;
          }
          else
          {
            ret = false;
          }
          if (ObIntType == expr_[5].get_type()
              && OB_SUCCESS == expr_[5].get_int(val))
          {
            c2.cid = val;
          }
          else
          {
            ret = false;
          }
        }
      }
      return ret;
    }

    bool ObPostfixExpression::is_simple_condition(bool real_val, uint64_t &column_id, int64_t &cond_op,
                                                  ObObj &const_val) const
    {
      int err = OB_SUCCESS;
      int64_t type_val = -1;
      int64_t cid = OB_INVALID_ID;
      bool is_simple_cond_type = false;


      do{
        if (expr_.count() == (3+2+3+1)) /*cid(3) + const_operand(2) + operator(3) + end(1) */
        {
          /* (1) cid */
          if (ObIntType != expr_[0].get_type())
          {
            // not int val, pass
            break;
          }
          else if(OB_SUCCESS != (err = expr_[0].get_int(type_val)))
          {
            TBSYS_LOG(WARN, "fail to get int value.err=%d", err);
            break;
          }
          else if (type_val != COLUMN_IDX)
          {
            break;
          }
          else if (OB_SUCCESS != (err = expr_[2].get_int(cid)))
          {
            TBSYS_LOG(WARN, "fail to get int value.err=%d", err);
            break;
          }
          /* (2) const_opr */
          else if (ObIntType != expr_[3].get_type())
          {
            // not int val, pass
            break;
          }
          else if (OB_SUCCESS != (err = expr_[3].get_int(type_val)))
          {
            TBSYS_LOG(WARN, "fail to get int value.err=%d", err);
            break;
          }
          else if (type_val != CONST_OBJ)
          {
            break;
          }
          /* (3) op */
          else if (ObIntType != expr_[5].get_type())
          {
            // not int val, pass
            break;
          }
          else if (OB_SUCCESS != (err = expr_[5].get_int(type_val)))
          {
            TBSYS_LOG(WARN, "fail to get int value.err=%d", err);
            break;
          }
          else if (type_val != OP)
          {
            break;
          }
          else if (ObIntType != expr_[6].get_type())
          {
            // not int val, pass
            break;
          }
          else if (OB_SUCCESS != (err = expr_[6].get_int(type_val)))
          {
            TBSYS_LOG(WARN, "fail to get int value.err=%d", err);
            break;
          }
          else if ((type_val < T_OP_EQ || type_val >= T_OP_NE) && (type_val != T_OP_IS))
          {
            break;
          }
          /* (4) result */
          else
          {
            if (real_val && ObExtendType == expr_[4].get_type()) // question mark
            {
              int64_t obj_addr = common::OB_INVALID_ID;
              expr_[4].get_ext(obj_addr);
              const_val = *(reinterpret_cast<ObObj *>(obj_addr));
              TBSYS_LOG(DEBUG, "using variable, const_val=%s", to_cstring(const_val));
            }
            else
            {
              const_val = expr_[4];
            }
            column_id = (uint64_t)cid;
            cond_op = type_val;
            is_simple_cond_type = true;
          }
        }
      } while(0);
      return is_simple_cond_type;
    }

    bool ObPostfixExpression::is_simple_between(bool real_val, uint64_t &column_id, int64_t &cond_op,
                                                ObObj &cond_start, ObObj &cond_end) const
    {
      int err = OB_ERROR;
      int64_t type_val = -1;
      int64_t cid = OB_INVALID_ID;
      bool is_simple_cond_type = false;
      do{
        if (expr_.count() == (3+2+2+3+1)) /*cid(3) + const_opr(2) + const_opr(2) + operator(3) + end(1) */
        {
          /* (1) cid */
          if (ObIntType != expr_[0].get_type())
          {
            // not int val, pass
            break;
          }
          else if(OB_SUCCESS != (err = expr_[0].get_int(type_val)))
          {
            TBSYS_LOG(WARN, "fail to get int value.err=%d", err);
            break;
          }
          else if (type_val != COLUMN_IDX)
          {
            break;
          }
          else if (OB_SUCCESS != (err = expr_[2].get_int(cid)))
          {
            TBSYS_LOG(WARN, "fail to get int value.err=%d", err);
            break;
          }
          /* (2) const_opr 1 and const_opr 2 */
          else if (ObIntType != expr_[3].get_type())
          {
            // not int val, pass
            break;
          }
          else if (OB_SUCCESS != (err = expr_[3].get_int(type_val)))
          {
            TBSYS_LOG(WARN, "fail to get int value.err=%d", err);
            break;
          }
          else if (type_val != CONST_OBJ)
          {
            break;
          }
          else if (ObIntType != expr_[5].get_type())
          {
            // not int val, pass
            break;
          }
          else if (OB_SUCCESS != (err = expr_[5].get_int(type_val)))
          {
            TBSYS_LOG(WARN, "fail to get int value.err=%d", err);
            break;
          }
          else if (type_val != CONST_OBJ)
          {
            break;
          }
          else
          {
            if (real_val && ObExtendType == expr_[4].get_type()) // question mark
            {
              int64_t obj_addr = common::OB_INVALID_ID;
              expr_[4].get_ext(obj_addr);
              cond_start = *(reinterpret_cast<ObObj *>(obj_addr));
              TBSYS_LOG(DEBUG, "using variable, cond_start=%s", to_cstring(cond_start));
            }
            else
            {
              cond_start = expr_[4];
            }
            if (real_val && ObExtendType == expr_[6].get_type()) // question mark
            {
              int64_t obj_addr = common::OB_INVALID_ID;
              expr_[6].get_ext(obj_addr);
              cond_end = *(reinterpret_cast<ObObj *>(obj_addr));
              TBSYS_LOG(DEBUG, "using variable, cond_end=%s", to_cstring(cond_end));
            }
            else
            {
              cond_end = expr_[6];
            }
          }
          /* (3) op */
          if (OB_SUCCESS != err)
          {
            // pass
            break;
          }
          else if (ObIntType != expr_[7].get_type())
          {
            // not int val, pass
            break;
          }
          else if (OB_SUCCESS != (err = expr_[7].get_int(type_val)))
          {
            TBSYS_LOG(WARN, "fail to get int value.err=%d", err);
            break;
          }
          else if (type_val != OP)
          {
            break;
          }
          else if (ObIntType != expr_[8].get_type())
          {
            // not int val, pass
            break;
          }
          else if (OB_SUCCESS != (err = expr_[8].get_int(type_val)))
          {
            TBSYS_LOG(WARN, "fail to get int value.err=%d", err);
            break;
          }
          else if (type_val != T_OP_BTW)
          {
            break;
          }
          else
          {
            /* result */
            column_id = (uint64_t)cid;
            cond_op = type_val;
            is_simple_cond_type = true;
            err = OB_SUCCESS;
          }
        }
        else
        {
          TBSYS_LOG(DEBUG, "not a valid simple between function");
          err = OB_INVALID_ARGUMENT;
        }
      } while(0);
      return is_simple_cond_type;
    }


    DEFINE_SERIALIZE(ObPostfixExpression)
    {
      int ret = OB_SUCCESS;
      int i = 0;
      ObObj obj;
      obj.set_int(expr_.count());
      if (OB_SUCCESS != (ret = obj.serialize(buf, buf_len, pos)))
      {
        TBSYS_LOG(WARN, "fail to serialize postfix expression size. ret=%d", ret);
      }
      else
      {
        for (i = 0; i < expr_.count(); i++)
        {
          if (OB_UNLIKELY(expr_[i].get_type() == ObExtendType))
          {
            int64_t obj_addr = common::OB_INVALID_ID;
            ObObj *val = NULL;
            ObObj tmp_val;
            if (OB_SUCCESS != (ret = expr_[i].get_ext(obj_addr)))
            {
              TBSYS_LOG(WARN,"get_ext error [err:%d]", ret);
              break;
            }
            else if ((val = reinterpret_cast<ObObj *>(obj_addr)) == NULL)
            {
              ret = OB_ERR_UNEXPECTED;
              TBSYS_LOG(WARN,"Wrong place holder address [err:%d]", ret);
              break;
            }
            else if (OB_SUCCESS != (ret = val->serialize(buf, buf_len, pos)))
            {
              TBSYS_LOG(WARN, "fail to serialize expr[%d]. ret=%d", i, ret);
              break;
            }
          }
          else if (OB_SUCCESS != (ret = expr_[i].serialize(buf, buf_len, pos)))
          {
            TBSYS_LOG(WARN, "fail to serialize expr[%d]. ret=%d count=%ld", i, ret, expr_.count());
            break;
          }
        }
      }
      return ret;
    }

    // single row expression checker
    // ONLY: (x,x,x) in ((x,x,x))
    bool ObPostfixExpression::is_simple_in_expr(const ObRowkeyInfo &info, ObArray<ObRowkey> &rowkey_array,
        common::PageArena<ObObj,common::ModulePageAllocator> &rowkey_objs_allocator) const
    {
      int err = OB_SUCCESS;
      int64_t rowkey_column_count = 0;
      int64_t index = 0;
      int64_t len = expr_.count();
      int64_t dim = 0, dim2 = 0;
      int64_t row_count = 0;
      int64_t row = 0;
      int64_t val_idx = 0;
      bool is_simple_expr = false;
      ObRowkey rowkey;
      ObObj *rowkey_objs = NULL;
      ObRowkeyColumn rowkey_column;
      int64_t cid = OB_INVALID_ID;
      if (len > 16)
      {
        // check 1: (OP, T_OP_IN, 2), (END)
        if (!ExprUtil::is_end(expr_.at(len-1)) || !ExprUtil::is_value(expr_.at(len-2), 2L) ||
            !ExprUtil::is_op_of_type(expr_.at(len-3), T_OP_IN) || !ExprUtil::is_op(expr_.at(len-4)))
        {
          // TBSYS_LOG(DEBUG, "not simple in expr. len=%ld. %d, %d, %d, %d", len,
          //    ExprUtil::is_end(expr_.at(len-1)), ExprUtil::is_value(expr_.at(len-2), 2L),
          //    ExprUtil::is_op_of_type(expr_.at(len-3), T_OP_IN), ExprUtil::is_op(expr_.at(len-4)));
        }
        // check 2: (OP, T_OP_ROW, row_count)
        // support getting multi row,
        // for example, (a,b) in ((1,2), (3,4), (5,6)), row_count = 3, dim = 2
        else if (OB_SUCCESS != expr_.at(len-5).get_int(row_count) || !ExprUtil::is_op_of_type(expr_.at(len-6), T_OP_ROW) ||
            !ExprUtil::is_op(expr_.at(len-7)))
        {
          // TBSYS_LOG(DEBUG, "not simple in expr. len=%ld", len);
        }
        // check 3: (OP, T_OP_ROW, dim)
        else if (OB_SUCCESS != expr_.at(len-8).get_int(dim) || !ExprUtil::is_op_of_type(expr_.at(len-9), T_OP_ROW) ||
            !ExprUtil::is_op(expr_.at(len-10)))
        {
          // TBSYS_LOG(DEBUG, "not simple in expr. len=%ld", len);
        }
        else
        {
          const int64_t single_row_len = dim * 2 + 3;
          len = (len - 7) - (row_count * single_row_len);  // support multi row, 'dim' columns, each column takes two objects
          val_idx = len;
          OB_ASSERT(dim > 0);
          OB_ASSERT(len > 6);
          if (dim <= 0 || len <= 6)
          {
            // TBSYS_LOG(DEBUG, "not simple in expr. len=%ld", len);
          }
          // check 4: (OP, T_OP_LEFT_PARAM_END, 2)
          else if (!ExprUtil::is_value(expr_.at(len-1), 2L) || !ExprUtil::is_op_of_type(expr_.at(len-2), T_OP_LEFT_PARAM_END) ||
              !ExprUtil::is_op(expr_.at(len-3)))
          {
            // TBSYS_LOG(DEBUG, "not simple in expr. len=%ld", len);
          }
          // check 5: (OP, T_OP_ROW, ?)
          else if (OB_SUCCESS != expr_.at(len-4).get_int(dim2) || !ExprUtil::is_op_of_type(expr_.at(len-5), T_OP_ROW) ||
              !ExprUtil::is_op(expr_.at(len-6)))
          {
            // TBSYS_LOG(DEBUG, "not simple in expr. len=%ld.%ld, %d, %d", len,
            //    dim2, ExprUtil::is_op_of_type(expr_.at(len-5), T_OP_ROW), ExprUtil::is_op(expr_.at(len-6)));
          }
          else if (dim != dim2)
          {
            // TBSYS_LOG(DEBUG, "not simple in expr. len=%ld. dim=%ld", len, dim);
          }
          else if (dim == info.get_size())
          {
            len = len - (dim * 3 + 6); // 3 = COLUMN_IDX, TID, CID
            if (len == 0)
            {
              // extra values from expression
              // extra 1: rowkey columns
              int64_t size = info.get_size();
              for (index = 0; index < size && index < dim && OB_SUCCESS == err; index++)
              {
                if (OB_SUCCESS != (err = info.get_column(index, rowkey_column)))
                {
                  TBSYS_LOG(ERROR, "get rowkey column fail. index=%ld, size=%ld", index, size);
                }
                else
                {
                  if (OB_SUCCESS != expr_.at(index * 3 + 2).get_int(cid)) // 3=COLUMN_REF, TID, CID
                  {
                    TBSYS_LOG(ERROR, "fail to get int value from expr_.at(2)");
                  }
                  if (rowkey_column.column_id_ == static_cast<uint64_t>(cid))
                  {
                    rowkey_column_count++;
                  }
                  else
                  {
                    break;
                  }
                }
              }
              if ((OB_SUCCESS == err) && (rowkey_column_count == size))
              {
                if (NULL != (rowkey_objs = rowkey_objs_allocator.alloc(row_count * rowkey_column_count * sizeof(ObObj))))
                {
                  for (row = 0; row < row_count; row++)
                  {
                    // extra 2: values
                    for (index = 0; index < rowkey_column_count; index++)
                    {
                      // TODO: check every T_OP_ROW dim, all must be equal. currently skipped this step
                      const int64_t offset = val_idx + row * single_row_len + (index * 2 + 1); // 2=CONST,VALUE
                      if (ObExtendType == expr_.at(offset).get_type())
                      {
                        int64_t obj_addr = common::OB_INVALID_ID;
                        expr_.at(offset).get_ext(obj_addr);
                        rowkey_objs[index] = *(reinterpret_cast<ObObj *>(obj_addr));
                      }
                      else
                      {
                        rowkey_objs[index] = expr_.at(offset);
                      }
                      // TBSYS_LOG(DEBUG, "index=%ld, at=%ld, val=%s", index, offset, to_cstring(rowkey_objs[index]));
                    }
                    rowkey.assign(rowkey_objs, rowkey_column_count);
                    if (OB_SUCCESS!= (err = rowkey_array.push_back(rowkey)))
                    {
                      TBSYS_LOG(ERROR, "fail to push rowkey to array. err=%d", err);
                    }
                    rowkey_objs += rowkey_column_count;
                  }
                }
                else
                {
                  TBSYS_LOG(ERROR, "fail to alloc memory");
                  err = OB_ALLOCATE_MEMORY_FAILED;
                }
                if (OB_SUCCESS == err)
                {
                  is_simple_expr = true;
                }
              }
            }
            else
            {
              // TBSYS_LOG(DEBUG, "not simple in expr. len=%ld. dim=%ld", len, dim);
            }
          }
        }
      }
      return is_simple_expr;
    }

    DEFINE_DESERIALIZE(ObPostfixExpression)
    {
      int ret = OB_SUCCESS;
      int i = 0;
      ObObj obj;
      ObObj obj2;
      int64_t val = 0;
      reset();
      if (OB_SUCCESS != (ret = obj.deserialize(buf, data_len, pos)))
      {
        TBSYS_LOG(WARN, "fail to deserialize obj. ret=%d. buf=%p, data_len=%ld, pos=%ld",
            ret, buf, data_len, pos);
      }
      else if (ObIntType != obj.get_type())
      {
        TBSYS_LOG(WARN, "unexpected obj type. actual type:%d, expected:%d", obj.get_type(), ObIntType);
        ret = OB_ERR_UNEXPECTED;
      }
      else
      {
        if ((OB_SUCCESS != (ret = obj.get_int(val))) || (val <= 0))
        {
          TBSYS_LOG(WARN, "fail to get int value. ret=%d, expr_.count()%ld", ret, val);
        }
        else
        {
          int expr_count = static_cast<int32_t>(val);
          for (i = 0; i < expr_count; i++)
          {
            if (OB_SUCCESS != (ret = obj.deserialize(buf, data_len, pos)))
            {
              TBSYS_LOG(WARN, "fail to deserialize obj. ret=%d. buf=%p, data_len=%ld, pos=%ld",
                  ret, buf, data_len, pos);
              break;
            }
            else if (ObVarcharType == obj.get_type())
            {
              if (OB_SUCCESS != (ret = str_buf_.write_obj(obj, &obj2)))
              {
                TBSYS_LOG(WARN, "fail to write object to string buffer. ret=%d", ret);
              }
              else if (OB_SUCCESS != (ret = expr_.push_back(obj2)))
              {
                TBSYS_LOG(WARN, "failed to add item, err=%d", ret);
              }
            }
            else
            {
              if (OB_SUCCESS != (ret = expr_.push_back(obj)))
              {
                TBSYS_LOG(WARN, "failed to add item, err=%d", ret);
              }
            }
          }
        }
      }
      return ret;
    }

    DEFINE_GET_SERIALIZE_SIZE(ObPostfixExpression)
    {
      int64_t size = 0;
      int i = 0;
      ObObj obj;
      obj.set_int(expr_.count());
      size += obj.get_serialize_size();
      for (i = 0; i < expr_.count(); i++)
      {
        size += expr_[i].get_serialize_size();
      }
      return size;
    }

    /************************************************************************/
    /*****************   function implementation     ************************/
    /************************************************************************/
    inline int ObPostfixExpression::nop_func(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      UNUSED(params);
      UNUSED(stack_i);
      UNUSED(idx_i);
      UNUSED(result);
      TBSYS_LOG(WARN, "function not implemented!");
      return OB_NOT_IMPLEMENT;
    }

    inline int ObPostfixExpression::reserved_func(const ObExprObj &obj1, const ObExprObj &obj2, ObExprObj &result)
    {
      int err = OB_INVALID_ARGUMENT;
      UNUSED(obj1);
      UNUSED(obj2);
      UNUSED(result);
      return err;
    }


    /* compare function list:
     * >   gt_func
     * >=  ge_func
     * <=  le_func
     * <   lt_func
     * ==  eq_func
     * !=  neq_func
     */
    inline int ObPostfixExpression::gt_func(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      int err = OB_SUCCESS;
      UNUSED(params);
      if (NULL == stack_i)
      {
        TBSYS_LOG(WARN, "stack pointer is NULL.");
        err = OB_INVALID_ARGUMENT;
      }
      else if (idx_i < 2)
      {
        TBSYS_LOG(WARN, "no enough operand in the stack. current size:%d", idx_i);
        err = OB_INVALID_ARGUMENT;
      }
      else
      {
        stack_i[idx_i-2].gt(stack_i[idx_i-1], result);
        idx_i -= 2;
      }
      return err;
    }

    inline int ObPostfixExpression::ge_func(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      int err = OB_SUCCESS;
      UNUSED(params);
      if (NULL == stack_i)
      {
        TBSYS_LOG(WARN, "stack pointer is NULL.");
        err = OB_INVALID_ARGUMENT;
      }
      else if (idx_i < 2)
      {
        TBSYS_LOG(WARN, "no enough operand in the stack. current size:%d", idx_i);
        err = OB_INVALID_ARGUMENT;
      }
      else
      {
        stack_i[idx_i-2].ge(stack_i[idx_i-1], result);
        idx_i -= 2;
      }
      return err;
    }

    inline int ObPostfixExpression::le_func(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      int err = OB_SUCCESS;
      UNUSED(params);
      if (NULL == stack_i)
      {
        TBSYS_LOG(WARN, "stack pointer is NULL.");
        err = OB_INVALID_ARGUMENT;
      }
      else if (idx_i < 2)
      {
        TBSYS_LOG(WARN, "no enough operand in the stack. current size:%d", idx_i);
        err = OB_INVALID_ARGUMENT;
      }
      else
      {
        stack_i[idx_i-2].le(stack_i[idx_i-1], result);
        idx_i -= 2;
      }
      return err;
    }

    inline int ObPostfixExpression::lt_func(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      int err = OB_SUCCESS;
      UNUSED(params);
      if (NULL == stack_i)
      {
        TBSYS_LOG(WARN, "stack pointer is NULL.");
        err = OB_INVALID_ARGUMENT;
      }
      else if (idx_i < 2)
      {
        TBSYS_LOG(WARN, "no enough operand in the stack. current size:%d", idx_i);
        err = OB_INVALID_ARGUMENT;
      }
      else
      {
        stack_i[idx_i-2].lt(stack_i[idx_i-1], result);
        idx_i -= 2;
      }
      return err;
    }

    inline int ObPostfixExpression::eq_func(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      int err = OB_SUCCESS;
      UNUSED(params);
      if (NULL == stack_i)
      {
        TBSYS_LOG(WARN, "stack pointer is NULL.");
        err = OB_INVALID_ARGUMENT;
      }
      else if (idx_i < 2)
      {
        TBSYS_LOG(WARN, "no enough operand in the stack. current size:%d", idx_i);
        err = OB_INVALID_ARGUMENT;
      }
      else
      {
        stack_i[idx_i-2].eq(stack_i[idx_i-1], result);
        idx_i -= 2;
      }
      return err;
    }

    inline int ObPostfixExpression::neq_func(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      int err = OB_SUCCESS;
      UNUSED(params);
      if (NULL == stack_i)
      {
        TBSYS_LOG(WARN, "stack pointer is NULL.");
        err = OB_INVALID_ARGUMENT;
      }
      else if (idx_i < 2)
      {
        TBSYS_LOG(WARN, "no enough operand in the stack. current size:%d", idx_i);
        err = OB_INVALID_ARGUMENT;
      }
      else
      {
        stack_i[idx_i-2].ne(stack_i[idx_i-1], result);
        idx_i -= 2;
      }
      return err;
    }

    inline int ObPostfixExpression::is_not_func(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      int err = OB_SUCCESS;
      UNUSED(params);
      if (NULL == stack_i)
      {
        TBSYS_LOG(WARN, "stack pointer is NULL.");
        err = OB_INVALID_ARGUMENT;
      }
      else if (idx_i < 2)
      {
        TBSYS_LOG(WARN, "no enough operand in the stack. current size:%d", idx_i);
        err = OB_INVALID_ARGUMENT;
      }
      else
      {
        stack_i[idx_i-2].is_not(stack_i[idx_i-1], result);
        idx_i -= 2;
      }
      return err;
    }

    inline int ObPostfixExpression::is_func(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      int err = OB_SUCCESS;
      UNUSED(params);
      if (NULL == stack_i)
      {
        TBSYS_LOG(WARN, "stack pointer is NULL.");
        err = OB_INVALID_ARGUMENT;
      }
      else if (idx_i < 2)
      {
        TBSYS_LOG(WARN, "no enough operand in the stack. current size:%d", idx_i);
        err = OB_INVALID_ARGUMENT;
      }
      else
      {
        stack_i[idx_i-2].is(stack_i[idx_i-1], result);
        idx_i -= 2;
      }
      return err;
    }


    inline int ObPostfixExpression::add_func(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      int err = OB_SUCCESS;
      UNUSED(params);
      if (NULL == stack_i)
      {
        TBSYS_LOG(WARN, "stack pointer is NULL.");
        err = OB_INVALID_ARGUMENT;
      }
      else if (idx_i < 2)
      {
        TBSYS_LOG(WARN, "no enough operand in the stack. current size:%d", idx_i);
        err = OB_INVALID_ARGUMENT;
      }
      else
      {
        stack_i[idx_i-2].add(stack_i[idx_i-1], result);
        idx_i -= 2;
      }
      return err;
    }


    inline int ObPostfixExpression::sub_func(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      int err = OB_SUCCESS;
      UNUSED(params);
      if (NULL == stack_i)
      {
        TBSYS_LOG(WARN, "stack pointer is NULL.");
        err = OB_INVALID_ARGUMENT;
      }
      else if (idx_i < 2)
      {
        TBSYS_LOG(WARN, "no enough operand in the stack. current size:%d", idx_i);
        err = OB_INVALID_ARGUMENT;
      }
      else
      {
        stack_i[idx_i-2].sub(stack_i[idx_i-1], result);
        idx_i -= 2;
      }
      return err;
    }


    inline int ObPostfixExpression::mul_func(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      int err = OB_SUCCESS;
      UNUSED(params);
      if (NULL == stack_i)
      {
        TBSYS_LOG(WARN, "stack pointer is NULL.");
        err = OB_INVALID_ARGUMENT;
      }
      else if (idx_i < 2)
      {
        TBSYS_LOG(WARN, "no enough operand in the stack. current size:%d", idx_i);
        err = OB_INVALID_ARGUMENT;
      }
      else
      {
        stack_i[idx_i-2].mul(stack_i[idx_i-1], result);
        idx_i -= 2;
      }
      return err;
    }


    inline int ObPostfixExpression::div_func(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      int err = OB_SUCCESS;
      if (NULL == stack_i)
      {
        TBSYS_LOG(WARN, "stack pointer is NULL.");
        err = OB_INVALID_ARGUMENT;
      }
      else if (idx_i < 2)
      {
        TBSYS_LOG(WARN, "no enough operand in the stack. current size:%d", idx_i);
        err = OB_INVALID_ARGUMENT;
      }
      else
      {
        stack_i[idx_i-2].div(stack_i[idx_i-1], result, params.did_int_div_as_double_);
        idx_i -= 2;
      }
      return err;
    }

    inline int ObPostfixExpression::mod_func(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      int err = OB_SUCCESS;
      UNUSED(params);
      if (NULL == stack_i)
      {
        TBSYS_LOG(WARN, "stack pointer is NULL.");
        err = OB_INVALID_ARGUMENT;
      }
      else if (idx_i < 2)
      {
        TBSYS_LOG(WARN, "no enough operand in the stack. current size:%d", idx_i);
        err = OB_INVALID_ARGUMENT;
      }
      else
      {
        stack_i[idx_i-2].mod(stack_i[idx_i-1], result);
        idx_i -= 2;
      }
      return err;
    }


    inline int ObPostfixExpression::and_func(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      int err = OB_SUCCESS;
      UNUSED(params);
      if (NULL == stack_i)
      {
        TBSYS_LOG(WARN, "stack pointer is NULL.");
        err = OB_INVALID_ARGUMENT;
      }
      else if (idx_i < 2)
      {
        TBSYS_LOG(WARN, "no enough operand in the stack. current size:%d", idx_i);
        err = OB_INVALID_ARGUMENT;
      }
      else
      {
        stack_i[idx_i-2].land(stack_i[idx_i-1], result);
        idx_i -= 2;
      }
      return err;
    }

    inline int ObPostfixExpression::or_func(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      int err = OB_SUCCESS;
      UNUSED(params);
      if (NULL == stack_i)
      {
        TBSYS_LOG(WARN, "stack pointer is NULL.");
        err = OB_INVALID_ARGUMENT;
      }
      else if (idx_i < 2)
      {
        TBSYS_LOG(WARN, "no enough operand in the stack. current size:%d", idx_i);
        err = OB_INVALID_ARGUMENT;
      }
      else
      {
        stack_i[idx_i-2].lor(stack_i[idx_i-1], result);
        idx_i -= 2;
      }
      return err;
    }

    inline int ObPostfixExpression::minus_func(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      int err = OB_SUCCESS;
      UNUSED(params);
      if (NULL == stack_i)
      {
        TBSYS_LOG(WARN, "stack pointer is NULL.");
        err = OB_INVALID_ARGUMENT;
      }
      else if (idx_i < 1)
      {
        TBSYS_LOG(WARN, "no enough operand in the stack. current size:%d", idx_i);
        err = OB_INVALID_ARGUMENT;
      }
      else
      {
        stack_i[idx_i-1].negate(result);
        idx_i -= 1;
      }
      return err;
    }


    inline int ObPostfixExpression::plus_func(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      int err = OB_SUCCESS;
      UNUSED(params);
      if (NULL == stack_i)
      {
        TBSYS_LOG(WARN, "stack pointer is NULL.");
        err = OB_INVALID_ARGUMENT;
      }
      else if (idx_i < 1)
      {
        TBSYS_LOG(WARN, "no enough operand in the stack. current size:%d", idx_i);
        err = OB_INVALID_ARGUMENT;
      }
      else
      {
        // don't touch it whatever the type is
        result = stack_i[idx_i-1];
        idx_i -= 1;
      }
      return err;
    }



    inline int ObPostfixExpression::not_func(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      int err = OB_SUCCESS;
      UNUSED(params);
      if (NULL == stack_i)
      {
        TBSYS_LOG(WARN, "stack pointer is NULL.");
        err = OB_INVALID_ARGUMENT;
      }
      else if (idx_i < 1)
      {
        TBSYS_LOG(WARN, "no enough operand in the stack. current size:%d", idx_i);
        err = OB_INVALID_ARGUMENT;
      }
      else
      {
        stack_i[idx_i-1].lnot(result);
        idx_i -= 1;
      }
      return err;
    }

    inline int ObPostfixExpression::sys_func_substr(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      int err = OB_SUCCESS;
      ObString varchar;
      ObString res_varchar;

      if (NULL == stack_i)
      {
        TBSYS_LOG(WARN, "stack pointer is NULL.");
        err = OB_INVALID_ARGUMENT;
      }
      else if (idx_i < params.operand_count_)
      {
        TBSYS_LOG(WARN, "no enough operand in the stack. current size:%d", idx_i);
        err = OB_INVALID_ARGUMENT;
      }
      else
      {
        //TBSYS_LOG(INFO, "params.operand_count_ = %d, [3]=%s, [2]=%s, [1]=%s",
        //    params.operand_count_, to_cstring(stack_i[idx_i-3]), to_cstring(stack_i[idx_i-2]), to_cstring(stack_i[idx_i-1]));

        if (params.operand_count_ == 2)
        {
          err = stack_i[idx_i-2].substr(stack_i[idx_i-1], result, *params.str_buf_);
        }
        else if (params.operand_count_ == 3)
        {
          err = stack_i[idx_i-3].substr(stack_i[idx_i-2], stack_i[idx_i-1], result, *params.str_buf_);
        }
        else
        {
          err = OB_ERR_UNEXPECTED;
          TBSYS_LOG(WARN, " unexpected operand count %d", params.operand_count_);
        }
        idx_i -= params.operand_count_;
      }
      return err;

    }
    inline int ObPostfixExpression::like_func(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      int err = OB_SUCCESS;
      UNUSED(params);
      if (NULL == stack_i)
      {
        TBSYS_LOG(WARN, "stack pointer is NULL.");
        err = OB_INVALID_ARGUMENT;
      }
      else if (idx_i < 2)
      {
        TBSYS_LOG(WARN, "no enough operand in the stack. current size:%d", idx_i);
        err = OB_INVALID_ARGUMENT;
      }
      else
      {
        err = stack_i[idx_i-2].like(stack_i[idx_i-1], result);
        idx_i -= 2;
      }
      return err;
    }

    inline int ObPostfixExpression::left_param_end_func(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      int ret = OB_SUCCESS;
      int dim = params.operand_count_;
      if (OB_SUCCESS != (ret = const_cast<ObPostExprExtraParams &>(params).in_row_operator_.push_row(stack_i, idx_i, 1)))
      {
        TBSYS_LOG(WARN, "fail to push row into in_row_operator_. ret=%d", ret);
      }
      else
      {
        result.set_int((int64_t)dim);
      }
      return ret;
    }

    inline int ObPostfixExpression::row_func(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      int ret = OB_SUCCESS;
      int row_count = params.operand_count_;
      if (NULL == stack_i)
      {
        TBSYS_LOG(WARN, "stack pointer is NULL.");
        ret = OB_INVALID_ARGUMENT;
      }
      else if (idx_i < row_count)
      {
        TBSYS_LOG(WARN, "no enough operand in the stack. current size:%d, row_count=%d", idx_i, row_count);
        ret = OB_INVALID_ARGUMENT;
      }
      else
      {
        if (OB_SUCCESS != (ret = const_cast<ObPostExprExtraParams &>(params).in_row_operator_.push_row(stack_i, idx_i, row_count)))
        {
          TBSYS_LOG(WARN, "fail to push row to row operator. ret=%d", ret);
        }
        else
        {
          //TBSYS_LOG(INFO, "idx_i=%d, row_count=%d", idx_i, row_count);
          result.set_int((int64_t)row_count);
        }
      }
      return ret;
    }

    inline int ObPostfixExpression::in_func(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      // in的算法
      //
      // 例1.
      // 2 IN (3, 4) 的后缀表达式为
      // [栈顶] 2, 3, 4, Row(2), IN(2)
      // in_row_operator_中数据的layout为：
      // 2 3 4
      // width = 1
      //
      // 例2.
      // (1, 3) IN ((3, 4), (1, 2))的后缀表达式为
      // [栈顶] 1, 3, Row(2), 3, 4, Row(2), 1, 2, Row(2), Row(2), IN(2)
      // in_row_operator_中数据的layout为：
      // 1 3 3 4 1 2
      // width = 2
      //
      // 显然，根据width，取出前width个数，逐个往后比较即可计算得到in的结果
      // note: 1. 该后缀表达式计算中，左操作数先出栈 2. 最后一个T_OP_ROW操作被实际上忽略
      //
      int ret = OB_SUCCESS;
      if (NULL == stack_i)
      {
        TBSYS_LOG(WARN, "stack pointer is NULL.");
        ret = OB_INVALID_ARGUMENT;
      }
      else if (idx_i < 2)
      {
        TBSYS_LOG(WARN, "no enough operand in the stack. current size:%d", idx_i);
        ret = OB_INVALID_ARGUMENT;
      }
      else
      {
        if (OB_SUCCESS != (ret = const_cast<ObPostExprExtraParams &>(params).in_row_operator_.get_result(stack_i, idx_i, result)))
        {
          TBSYS_LOG(WARN, "fail to get IN operation result. ret=%d", ret);
        }
      }
      return ret;
    }

    inline int ObPostfixExpression::not_in_func(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      int ret = in_func(stack_i, idx_i, result, params);
      result.lnot(result);
      return ret;
    }

    int ObPostfixExpression::not_like_func(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      int err = OB_SUCCESS;
      UNUSED(params);
      if (NULL == stack_i)
      {
        TBSYS_LOG(WARN, "stack pointer is NULL.");
        err = OB_INVALID_ARGUMENT;
      }
      else if (idx_i < 2)
      {
        TBSYS_LOG(WARN, "no enough operand in the stack. current size:%d", idx_i);
        err = OB_INVALID_ARGUMENT;
      }
      else
      {
        stack_i[idx_i-2].not_like(stack_i[idx_i-1], result);
        idx_i -= 2;
      }
      return err;
    }

    int ObPostfixExpression::btw_func(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      int ret = OB_SUCCESS;
      UNUSED(params);
      if (NULL == stack_i)
      {
        TBSYS_LOG(WARN, "stack pointer is NULL.");
        ret = OB_INVALID_ARGUMENT;
      }
      else if (idx_i < 3)
      {
        TBSYS_LOG(WARN, "no enough operand in the stack. current size:%d", idx_i);
        ret = OB_INVALID_ARGUMENT;
      }
      else
      {
        stack_i[idx_i-3].btw(stack_i[idx_i-2], stack_i[idx_i-1], result);
        idx_i -= 3;
      }
      return ret;
    }

    int ObPostfixExpression::not_btw_func(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      int ret = OB_SUCCESS;
      UNUSED(params);
      if (NULL == stack_i)
      {
        TBSYS_LOG(WARN, "stack pointer is NULL.");
        ret = OB_INVALID_ARGUMENT;
      }
      else if (idx_i < 3)
      {
        TBSYS_LOG(WARN, "no enough operand in the stack. current size:%d", idx_i);
        ret = OB_INVALID_ARGUMENT;
      }
      else
      {
        stack_i[idx_i-3].not_btw(stack_i[idx_i-2], stack_i[idx_i-1], result);
        idx_i -= 3;
      }
      return ret;
    }

    const char * ObPostfixExpression::get_sys_func_name(enum ObSqlSysFunc func_id)
    {
      const char *ret;
      if (func_id >= SYS_FUNC_LENGTH && func_id < SYS_FUNC_NUM)
      {
        ret = SYS_FUNCS_NAME[func_id];
      }
      else
      {
        ret = "";
        TBSYS_LOG(ERROR, "unexpected sql sys func type %d", func_id);
      }
      return ret;
    }

    int ObPostfixExpression::get_sys_func_param_num(const ObString& name, int32_t& param_num)
    {
      int ret = OB_SUCCESS;
      int32_t i = 0;
      for (i = SYS_FUNC_LENGTH; i < SYS_FUNC_NUM; i++)
      {
        if (static_cast<int32_t>(strlen(SYS_FUNCS_NAME[i])) == name.length()
          && strncasecmp(SYS_FUNCS_NAME[i], name.ptr(), name.length()) == 0)
          break;
      }
      if (i >= SYS_FUNC_LENGTH && i < SYS_FUNC_NUM)
      {
        param_num = SYS_FUNCS_ARGS_NUM[i];
      }
      else
      {
        ret = OB_ERR_FUNCTION_UNKNOWN;
        TBSYS_LOG(WARN, "Unknown function '%.*s', ret=%d", name.length(), name.ptr(), ret);
      }
      return ret;
    }

    inline int ObPostfixExpression::sys_func_ip_to_int(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      int err = OB_SUCCESS;
      UNUSED(params);
      if (OB_UNLIKELY(NULL == stack_i))
      {
        TBSYS_LOG(WARN, "stack pointer is NULL.");
        err = OB_INVALID_ARGUMENT;
      }
      else if (OB_UNLIKELY(idx_i < 1))
      {
        TBSYS_LOG(WARN, "no enough operand in the stack. current size:%d", idx_i);
        err = OB_INVALID_ARGUMENT;
      }
      else
      {
        stack_i[idx_i - 1].ip_to_int(result);
        idx_i -= 1;
      }
      return err;
    }
    inline int ObPostfixExpression::sys_func_int_to_ip(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      int err = OB_SUCCESS;
      UNUSED(params);
      if (OB_UNLIKELY(NULL == stack_i))
      {
        TBSYS_LOG(WARN, "stack pointer is NULL.");
        err = OB_INVALID_ARGUMENT;
      }
      else if (OB_UNLIKELY(idx_i < 1))
      {
        TBSYS_LOG(WARN, "no enough operand in the stack. current size:%d", idx_i);
        err = OB_INVALID_ARGUMENT;
      }
      else
      {
        stack_i[idx_i - 1].int_to_ip(result, *(params.str_buf_));
        idx_i -= 1;
      }
      return err;
    }
    inline int ObPostfixExpression::sys_func_unhex(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      int err = OB_SUCCESS;
      UNUSED(params);
      if (OB_UNLIKELY(NULL == stack_i))
      {
        TBSYS_LOG(WARN, "stack pointer is NULL.");
        err = OB_INVALID_ARGUMENT;
      }
      else if (OB_UNLIKELY(idx_i < 1))
      {
        TBSYS_LOG(WARN, "no enough operand in the stack. current size:%d", idx_i);
        err = OB_INVALID_ARGUMENT;
      }
      else
      {
        stack_i[idx_i - 1].unhex(result, *(params.str_buf_));
        idx_i -= 1;
      }
      return err;
    }
    inline int ObPostfixExpression::sys_func_hex(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      int err = OB_SUCCESS;
      UNUSED(params);
      if (OB_UNLIKELY(NULL == stack_i))
      {
        TBSYS_LOG(WARN, "stack pointer is NULL.");
        err = OB_INVALID_ARGUMENT;
      }
      else if (OB_UNLIKELY(idx_i < 1))
      {
        TBSYS_LOG(WARN, "no enough operand in the stack. current size:%d", idx_i);
        err = OB_INVALID_ARGUMENT;
      }
      else
      {
        stack_i[idx_i - 1].hex(result, *(params.str_buf_));
        idx_i -= 1;
      }
      return err;
    }
    inline int ObPostfixExpression::sys_func_length(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      int err = OB_SUCCESS;
      UNUSED(params);
      if (OB_UNLIKELY(NULL == stack_i))
      {
        TBSYS_LOG(WARN, "stack pointer is NULL.");
        err = OB_INVALID_ARGUMENT;
      }
      else if (OB_UNLIKELY(idx_i < 1))
      {
        TBSYS_LOG(WARN, "no enough operand in the stack. current size:%d", idx_i);
        err = OB_INVALID_ARGUMENT;
      }
      else
      {
        stack_i[idx_i-1].varchar_length(result);
        idx_i -= 1;
      }
      return err;
    }

    inline int ObPostfixExpression::sys_func_cast(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      int err = OB_SUCCESS;
      if (OB_UNLIKELY(NULL == stack_i || NULL == params.str_buf_))
      {
        TBSYS_LOG(WARN, "stack_i=%p, str_buf_=%p.", stack_i, params.str_buf_);
        err = OB_INVALID_ARGUMENT;
      }
      else if (OB_UNLIKELY(idx_i < 2))
      {
        TBSYS_LOG(WARN, "no enough operand in the stack. current size:%d", idx_i);
        err = OB_INVALID_ARGUMENT;
      }
      else
      {
        int64_t literal_type = 0;
        int32_t dest_type = 0;
        if (OB_SUCCESS != (err = stack_i[idx_i-1].get_int(literal_type)))
        {
          TBSYS_LOG(WARN, "fail to get int value. actual type = %d. err=%d", stack_i[idx_i-1].get_type(), err);
        }
        else
        {
          // convert literal data type to inner data type
          dest_type = convert_item_type_to_obj_type(static_cast<ObItemType>(literal_type));
          if (OB_SUCCESS == err)
          {
            if (OB_SUCCESS != (err = stack_i[idx_i-2].cast_to(dest_type, result, *params.str_buf_)))
            {
              TBSYS_LOG(WARN, "fail to cast data from type %d to type %d. err=%d", stack_i[idx_i-2].get_type(), dest_type, err);
            }
          }
        }
        idx_i -= 2;
      }
      return err;
    }

    inline int ObPostfixExpression::sys_func_cur_time(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      UNUSED(stack_i);
      UNUSED(idx_i);
      UNUSED(params);

      struct timeval t;
      gettimeofday(&t, NULL);
      result.set_datetime(static_cast<int64_t>(t.tv_sec));
      return OB_SUCCESS;
    }

    inline int ObPostfixExpression::sys_func_cur_date(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      UNUSED(stack_i);
      UNUSED(idx_i);
      UNUSED(params);

      struct timeval t;
      gettimeofday(&t, NULL);
      result.set_datetime(static_cast<int64_t>(t.tv_sec));
      return OB_SUCCESS;
    }

    inline int ObPostfixExpression::sys_func_cur_timestamp(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      UNUSED(stack_i);
      UNUSED(idx_i);
      UNUSED(params);

      struct timeval t;
      gettimeofday(&t, NULL);
      result.set_precise_datetime(static_cast<int64_t>(t.tv_sec * 1000LL * 1000LL + t.tv_usec));
      return OB_SUCCESS;
    }

    inline int ObPostfixExpression::sys_func_cur_user(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      UNUSED(stack_i);
      UNUSED(idx_i);
      UNUSED(result);
      UNUSED(params);
      return OB_NOT_SUPPORTED;
    }

    inline int ObPostfixExpression::sys_func_trim(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      int err = OB_SUCCESS;
      if (NULL == stack_i || NULL == params.str_buf_)
      {
        TBSYS_LOG(WARN, "stack_i=%p, str_buf_=%p.", stack_i, params.str_buf_);
        err = OB_INVALID_ARGUMENT;
      }
      else if (idx_i < 3)
      {
        TBSYS_LOG(WARN, "no enough operand in the stack. current size:%d", idx_i);
        err = OB_INVALID_ARGUMENT;
      }
      else
      {
        if (OB_SUCCESS != (err = stack_i[idx_i-1].trim(stack_i[idx_i-3], stack_i[idx_i-2], result, *params.str_buf_)))
        {
          TBSYS_LOG(WARN, "fail to trim value. err=%d", err);
        }
        idx_i -= 3;
      }
      return err;
    }

    inline int ObPostfixExpression::sys_func_lower(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      int err = OB_SUCCESS;
      if (NULL == stack_i || NULL == params.str_buf_)
      {
        TBSYS_LOG(WARN, "stack_i=%p, str_buf_=%p.", stack_i, params.str_buf_);
        err = OB_INVALID_ARGUMENT;
      }
      else if (idx_i < 1)
      {
        TBSYS_LOG(WARN, "no enough operand in the stack. current size:%d", idx_i);
        err = OB_INVALID_ARGUMENT;
      }
      else
      {
        if (OB_SUCCESS != (err = stack_i[idx_i-1].lower_case(result, *params.str_buf_)))
        {
          TBSYS_LOG(WARN, "fail to get lower value. err=%d", err);
        }
        idx_i -= 1;
      }
      return err;
    }

    inline int ObPostfixExpression::sys_func_upper(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      int err = OB_SUCCESS;
      if (NULL == stack_i || NULL == params.str_buf_)
      {
        TBSYS_LOG(WARN, "stack_i=%p, str_buf_=%p.", stack_i, params.str_buf_);
        err = OB_INVALID_ARGUMENT;
      }
      else if (idx_i < 1)
      {
        TBSYS_LOG(WARN, "no enough operand in the stack. current size:%d", idx_i);
        err = OB_INVALID_ARGUMENT;
      }
      else
      {
        if (OB_SUCCESS != (err = stack_i[idx_i-1].upper_case(result, *params.str_buf_)))
        {
          TBSYS_LOG(WARN, "fail to get lower value. err=%d", err);
        }
        idx_i -= 1;
      }
      return err;
    }

    inline int ObPostfixExpression::sys_func_coalesce(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      int err = OB_SUCCESS;
      ObObj obj;
      if (NULL == stack_i)
      {
        TBSYS_LOG(WARN, "stack pointer is NULL.");
        err = OB_INVALID_ARGUMENT;
      }
      else if (idx_i < params.operand_count_)
      {
        TBSYS_LOG(WARN, "no enough operand in the stack. current size:%d", idx_i);
        err = OB_INVALID_ARGUMENT;
      }
      else
      {
        result.set_null();
        for (int i = params.operand_count_; i > 0; i--)
        {
          if (!stack_i[idx_i - i].is_null())
          {
            if (OB_SUCCESS != (err = stack_i[idx_i - i].to(obj)))
            {
              TBSYS_LOG(WARN, "fail to copy object. err=%d", err);
            }
            else
            {
              result.assign(obj);
            }
            break;
          }
        }
        idx_i -= params.operand_count_;
      }
      return err;
    }

    inline int ObPostfixExpression::concat_func(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      int err = OB_SUCCESS;
      if (OB_UNLIKELY(NULL == stack_i || NULL == params.str_buf_))
      {
        TBSYS_LOG(WARN, "stack pointer=%p, str_buf_=%p", stack_i, params.str_buf_);
        err = OB_INVALID_ARGUMENT;
      }
      else if (idx_i < 2)
      {
        TBSYS_LOG(WARN, "no enough operand in the stack. current size:%d", idx_i);
        err = OB_INVALID_ARGUMENT;
      }
      else
      {
        if (OB_SUCCESS != (err = stack_i[idx_i-2].concat(stack_i[idx_i-1], result, *params.str_buf_)))
        {
          err = OB_SUCCESS;
          result.set_null();
        }
        idx_i -= 2;
      }
      return err;
    }

    int ObPostfixExpression::arg_case_func(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      int ret = OB_SUCCESS;
      int arg_pos = idx_i - params.operand_count_;
      ObExprObj cmp;
      int i = 0;
      bool match_when = false;
      if (NULL == stack_i)
      {
        TBSYS_LOG(WARN, "stack pointer is NULL.");
        ret = OB_INVALID_ARGUMENT;
      }
      else if (params.operand_count_ < 3 || idx_i < params.operand_count_)
      {
        TBSYS_LOG(WARN, "no enough operand in the stack. current size:%d. expect more than:%d", idx_i, params.operand_count_);
        ret = OB_INVALID_ARGUMENT;
      }
      else
      {
        // case 1:
        // case c1 when 10 then expr1 else expr2  ==postfix stack==>
        // c1(idx_i-4), 10(idx_i-3), expr1(idx_i-2), expr2(idx_i-1), T_OP_ARG_CASE
        // params.operand_count_ = 4
        //
        // case 2:
        // case c1 when 10 then expr1  ==postfix stack==>
        // c1(idx_i-3), 10(idx_i-2), expr1(idx_i-1), T_OP_ARG_CASE
        // params.operand_count_ = 3
        //
        for (i = idx_i - (params.operand_count_ - 1); i < idx_i - 1; i += 2)
        {
          stack_i[arg_pos].eq(stack_i[i], cmp);
          //TBSYS_LOG(DEBUG, "i=%d,arg_pos=%d,cmp_case_when(%s,%s)", i, arg_pos, to_cstring(stack_i[arg_pos]), to_cstring(stack_i[i]));
          if (cmp.is_true()) // match when
          {
            result = stack_i[i+1];
            match_when = true;
            break;
          }
        }
        if (false == match_when)
        {
          if (params.operand_count_ % 2 == 0)
          {
            result = stack_i[idx_i - 1]; // match else
          }
          else
          {
            result.set_null(); // no else in expression, then match nothing
          }
        }
        if (OB_SUCCESS == ret)
        {
          idx_i -= params.operand_count_;
        }
      }
      return ret;
    }

    int ObPostfixExpression::case_func(ObExprObj *stack_i, int &idx_i, ObExprObj &result, const ObPostExprExtraParams &params)
    {
      int ret = OB_SUCCESS;
      int i = 0;
      bool match_when = false;
      if (NULL == stack_i)
      {
        TBSYS_LOG(WARN, "stack pointer is NULL.");
        ret = OB_INVALID_ARGUMENT;
      }
      else if (params.operand_count_ < 3 || idx_i < params.operand_count_)
      {
        TBSYS_LOG(WARN, "no enough operand in the stack. current size:%d. expect more than:%d", idx_i, params.operand_count_);
        ret = OB_INVALID_ARGUMENT;
      }
      else
      {
        // case 1:
        // case when false then expr1 else expr2  ==postfix stack==>
        // false(idx_i-3), expr1(idx_i-2), expr2(idx_i-1), T_OP_ARG_CASE
        // params.operand_count_ = 3
        //
        // case 2:
        // case when false then expr1  ==postfix stack==>
        // false(idx_i-2), expr1(idx_i-1), T_OP_ARG_CASE
        // params.operand_count_ = 2
        //
        for (i = idx_i - params.operand_count_; i < idx_i; i += 2)
        {
          if (stack_i[i].is_true())
          {
            result = stack_i[i+1];
            match_when = true;
            break;
          }
        }
        if (false == match_when)
        {
          if (params.operand_count_ % 2 != 0)
          {
            result = stack_i[idx_i - 1]; // match else
          }
          else
          {
            result.set_null(); // no else in expression, then match nothing
          }
        }
        if (OB_SUCCESS == ret)
        {
          idx_i -= params.operand_count_;
        }
      }
      return ret;
    }



    int64_t ObPostfixExpression::to_string(char* buf, const int64_t buf_len) const
    {
      int64_t pos = 0;
      int err = OB_SUCCESS;
      int idx = 0;
      int64_t type = 0;
      int64_t value = 0;
      int64_t value2 = 0;
      int64_t sys_func = 0;
      while(idx < expr_.count() && OB_SUCCESS == err)
      {
        expr_[idx++].get_int(type);
        if (END == type)
        {
          break;
        }
        else if(type <= BEGIN_TYPE || type >= END_TYPE)
        {
          break;
        }
        switch(type)
        {
          case COLUMN_IDX:
            if (OB_SUCCESS  != (err = expr_[idx++].get_int(value)))
            {
              TBSYS_LOG(WARN,"get_int error [err:%d]", err);
            }
            else if (OB_SUCCESS  != (err = expr_[idx++].get_int(value2)))
            {
              TBSYS_LOG(WARN,"get_int error [err:%d]", err);
            }
            else
            {
              uint64_t tid = static_cast<uint64_t>(value);
              if (OB_INVALID_ID == tid)
              {
                databuff_printf(buf, buf_len, pos, "COL<NULL,%lu>|", static_cast<uint64_t>(value2));
              }
              else
              {
                databuff_printf(buf, buf_len, pos, "COL<%lu,%lu>|", tid, static_cast<uint64_t>(value2));
              }
            }
            break;
          case CONST_OBJ:
            pos += expr_[idx].to_string(buf+pos, buf_len-pos);
            databuff_printf(buf, buf_len, pos, "|");
            idx++;
            break;
          case OP:
            // 根据OP的类型，从堆栈中弹出1个或多个操作数，进行计算
            if (OB_SUCCESS != (err = expr_[idx++].get_int(value)))
            {
              TBSYS_LOG(WARN,"get_int error [err:%d]", err);
            }
            else if (value <= T_MIN_OP || value >= T_MAX_OP)
            {
              TBSYS_LOG(WARN,"unsupported operator type [type:%ld]", value);
              err = OB_INVALID_ARGUMENT;
            }
            else if(OB_SUCCESS != (err = expr_[idx++].get_int(value2 /*param_count*/)))
            {
              TBSYS_LOG(WARN,"get_int error [err:%d]", err);
            }
            else
            {
              if (OB_UNLIKELY(T_FUN_SYS == value))
              {
                if(OB_SUCCESS != (err = expr_[idx++].get_int(sys_func)))
                {
                  TBSYS_LOG(WARN, "failed to get sys func, err=%d", err);
                }
                else if (0 > sys_func || sys_func >= SYS_FUNC_NUM)
                {
                  TBSYS_LOG(WARN, "invalid sys function type=%ld", sys_func);
                  err = OB_ERR_UNEXPECTED;
                }
                else
                {
                  databuff_printf(buf, buf_len, pos, "%s<%ld>|", SYS_FUNCS_NAME[sys_func], value2);
                }
              }
              else
              {
                databuff_printf(buf, buf_len, pos, "%s<%ld>|", ob_op_func_str(static_cast<ObItemType>(value)), value2);
              }
            }
            break;
          default:
            err = OB_ERR_UNEXPECTED;
            TBSYS_LOG(WARN,"unexpected [type:%ld]", type);
            break;
        }
      } // end while
      return pos;
    }

  } /* sql */
} /* namespace */
