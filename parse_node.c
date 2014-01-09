#include <stdio.h>
#include "parse_node.h"
#include "parse_malloc.h"
#include "sql_item_type.h"


int count_child(ParseNode* root);
void merge_child(ParseNode* node, ParseNode* source_tree, int* index);

const char* get_type_name(int type)
{
	switch(type){
	case T_INT : return "T_INT";
	case T_STRING : return "T_STRING";
	case T_BINARY : return "T_BINARY";
	case T_DATE : return "T_DATE";     // WE may need time and timestamp here
	case T_FLOAT : return "T_FLOAT";
	case T_DOUBLE : return "T_DOUBLE";
	case T_DECIMAL : return "T_DECIMAL";
	case T_BOOL : return "T_BOOL";
	case T_NULL : return "T_NULL";
	case T_QUESTIONMARK : return "T_QUESTIONMARK";
	case T_UNKNOWN : return "T_UNKNOWN";
	case T_REF_COLUMN : return "T_REF_COLUMN";
	case T_REF_EXPR : return "T_REF_EXPR";
	case T_REF_QUERY : return "T_REF_QUERY";
	case T_HINT : return "T_HINT";     // Hint message from rowkey
	case T_IDENT : return "T_IDENT";
	case T_STAR : return "T_STAR";
	case T_SYSTEM_VARIABLE : return "T_SYSTEM_VARIABLE";
	case T_TEMP_VARIABLE : return "T_TEMP_VARIABLE";
	case T_TYPE_INTEGER : return "T_TYPE_INTEGER";
	case T_TYPE_FLOAT : return "T_TYPE_FLOAT";
	case T_TYPE_DOUBLE : return "T_TYPE_DOUBLE";
	case T_TYPE_DECIMAL : return "T_TYPE_DECIMAL";
	case T_TYPE_BOOLEAN : return "T_TYPE_BOOLEAN";
	case T_TYPE_DATE : return "T_TYPE_DATE";
	case T_TYPE_TIME : return "T_TYPE_TIME";
	case T_TYPE_DATETIME : return "T_TYPE_DATETIME";
	case T_TYPE_TIMESTAMP : return "T_TYPE_TIMESTAMP";
	case T_TYPE_CHARACTER : return "T_TYPE_CHARACTER";
	case T_TYPE_VARCHAR : return "T_TYPE_VARCHAR";
	case T_TYPE_CREATETIME : return "T_TYPE_CREATETIME";
	case T_TYPE_MODIFYTIME : return "T_TYPE_MODIFYTIME";
	case T_OP_NEG : return "T_OP_NEG";   // negative
	case T_OP_POS : return "T_OP_POS";   // positive
	case T_OP_ADD : return "T_OP_ADD";
	case T_OP_MINUS : return "T_OP_MINUS";
	case T_OP_MUL : return "T_OP_MUL";
	case T_OP_DIV : return "T_OP_DIV";
	case T_OP_POW : return "T_OP_POW";
	case T_OP_REM : return "T_OP_REM";   // remainder
	case T_OP_MOD : return "T_OP_MOD";
	case T_OP_EQ : return "T_OP_EQ";      /* 2. Bool operators */
	case T_OP_LE : return "T_OP_LE";
	case T_OP_LT : return "T_OP_LT";
	case T_OP_GE : return "T_OP_GE";
	case T_OP_GT : return "T_OP_GT";
	case T_OP_NE : return "T_OP_NE";
	case T_OP_IS : return "T_OP_IS";
	case T_OP_IS_NOT : return "T_OP_IS_NOT";
	case T_OP_BTW : return "T_OP_BTW";
	case T_OP_NOT_BTW : return "T_OP_NOT_BTW";
	case T_OP_LIKE : return "T_OP_LIKE";
	case T_OP_NOT_LIKE : return "T_OP_NOT_LIKE";
	case T_OP_NOT : return "T_OP_NOT";
	case T_OP_AND : return "T_OP_AND";
	case T_OP_OR : return "T_OP_OR";
	case T_OP_IN : return "T_OP_IN";
	case T_OP_NOT_IN : return "T_OP_NOT_IN";
	case T_OP_ARG_CASE : return "T_OP_ARG_CASE";
	case T_OP_CASE : return "T_OP_CASE";
	case T_OP_ROW : return "T_OP_ROW";
	case T_OP_EXISTS : return "T_OP_EXISTS";
	case T_OP_CNN : return "T_OP_CNN";  /* 3. String operators */
	case T_FUN_SYS : return "T_FUN_SYS";                    // system functions, CHAR_LENGTH, ROUND, etc.
	case T_OP_LEFT_PARAM_END : return "T_OP_LEFT_PARAM_END";
	case T_MAX_OP : return "T_MAX_OP";
	case T_FUN_SYS_CAST : return "T_FUN_SYS_CAST";               // special system function : CAST(val AS type)
	case T_OP_NAME_FIELD : return "T_OP_NAME_FIELD";
	case T_FUN_MAX : return "T_FUN_MAX";
	case T_FUN_MIN : return "T_FUN_MIN";
	case T_FUN_SUM : return "T_FUN_SUM";
	case T_FUN_COUNT : return "T_FUN_COUNT";
	case T_FUN_AVG : return "T_FUN_AVG";
	case T_DELETE : return "T_DELETE";
	case T_SELECT : return "T_SELECT";
	case T_UPDATE : return "T_UPDATE";
	case T_INSERT : return "T_INSERT";
	case T_EXPLAIN : return "T_EXPLAIN";
	case T_LINK_NODE : return "T_LINK_NODE";
	case T_ASSIGN_LIST : return "T_ASSIGN_LIST";
	case T_ASSIGN_ITEM : return "T_ASSIGN_ITEM";
	case T_STMT_LIST : return "T_STMT_LIST";
	case T_EXPR_LIST : return "T_EXPR_LIST";
	case T_WHEN_LIST : return "T_WHEN_LIST";
	case T_PROJECT_LIST : return "T_PROJECT_LIST";
	case T_PROJECT_ITEM : return "T_PROJECT_ITEM";
	case T_FROM_LIST : return "T_FROM_LIST";
	case T_SET_UNION : return "T_SET_UNION";
	case T_SET_INTERSECT : return "T_SET_INTERSECT";
	case T_SET_EXCEPT : return "T_SET_EXCEPT";
	case T_WHERE_CLAUSE : return "T_WHERE_CLAUSE";
	case T_LIMIT_CLAUSE : return "T_LIMIT_CLAUSE";
	case T_SORT_LIST : return "T_SORT_LIST";
	case T_SORT_KEY : return "T_SORT_KEY";
	case T_SORT_ASC : return "T_SORT_ASC";
	case T_SORT_DESC : return "T_SORT_DESC";
	case T_ALL : return "T_ALL";
	case T_DISTINCT : return "T_DISTINCT";
	case T_ALIAS : return "T_ALIAS";
	case T_PROJECT_STRING : return "T_PROJECT_STRING";
	case T_COLUMN_LIST : return "T_COLUMN_LIST";
	case T_VALUE_LIST : return "T_VALUE_LIST";
	case T_VALUE_VECTOR : return "T_VALUE_VECTOR";
	case T_JOINED_TABLE : return "T_JOINED_TABLE";
	case T_JOIN_INNER : return "T_JOIN_INNER";
	case T_JOIN_FULL : return "T_JOIN_FULL";
	case T_JOIN_LEFT : return "T_JOIN_LEFT";
	case T_JOIN_RIGHT : return "T_JOIN_RIGHT";
	case T_CASE : return "T_CASE";
	case T_WHEN : return "T_WHEN";
	case T_CREATE_TABLE : return "T_CREATE_TABLE";
	case T_TABLE_ELEMENT_LIST : return "T_TABLE_ELEMENT_LIST";
	case T_TABLE_OPTION_LIST : return "T_TABLE_OPTION_LIST";
	case T_PRIMARY_KEY : return "T_PRIMARY_KEY";
	case T_COLUMN_DEFINITION : return "T_COLUMN_DEFINITION";
	case T_COLUMN_ATTRIBUTES : return "T_COLUMN_ATTRIBUTES";
	case T_CONSTR_NOT_NULL : return "T_CONSTR_NOT_NULL";
	case T_CONSTR_NULL : return "T_CONSTR_NULL";
	case T_CONSTR_DEFAULT : return "T_CONSTR_DEFAULT";
	case T_CONSTR_AUTO_INCREMENT : return "T_CONSTR_AUTO_INCREMENT";
	case T_CONSTR_PRIMARY_KEY : return "T_CONSTR_PRIMARY_KEY";
	case T_IF_NOT_EXISTS : return "T_IF_NOT_EXISTS";
	case T_IF_EXISTS : return "T_IF_EXISTS";
	case T_EXPIRE_INFO : return "T_EXPIRE_INFO";
	case T_TABLET_MAX_SIZE : return "T_TABLET_MAX_SIZE";
	case T_TABLET_BLOCK_SIZE : return "T_TABLET_BLOCK_SIZE";
	case T_REPLICA_NUM : return "T_REPLICA_NUM";
	case T_COMPRESS_METHOD : return "T_COMPRESS_METHOD";
	case T_USE_BLOOM_FILTER : return "T_USE_BLOOM_FILTER";
	case T_CONSISTENT_MODE : return "T_CONSISTENT_MODE";
	case T_DROP_TABLE : return "T_DROP_TABLE";
	case T_TABLE_LIST : return "T_TABLE_LIST";
	case T_ALTER_TABLE : return "T_ALTER_TABLE";
	case T_ALTER_ACTION_LIST : return "T_ALTER_ACTION_LIST";
	case T_TABLE_RENAME : return "T_TABLE_RENAME";
	case T_COLUMN_DROP : return "T_COLUMN_DROP";
	case T_COLUMN_ALTER : return "T_COLUMN_ALTER";
	case T_COLUMN_RENAME : return "T_COLUMN_RENAME";
	case T_ALTER_SYSTEM : return "T_ALTER_SYSTEM";
	case T_SYTEM_ACTION_LIST : return "T_SYTEM_ACTION_LIST";
	case T_SYSTEM_ACTION : return "T_SYSTEM_ACTION";
	case T_CLUSTER : return "T_CLUSTER";
	case T_SERVER_ADDRESS : return "T_SERVER_ADDRESS";
    case T_SHOW_DATABASES:  return "T_SHOW_DATABASES";
	case T_SHOW_TABLES : return "T_SHOW_TABLES";
	case T_SHOW_VARIABLES : return "T_SHOW_VARIABLES";
	case T_SHOW_COLUMNS : return "T_SHOW_COLUMNS";
	case T_SHOW_SCHEMA : return "T_SHOW_SCHEMA";
	case T_SHOW_CREATE_TABLE : return "T_SHOW_CREATE_TABLE";
	case T_SHOW_TABLE_STATUS : return "T_SHOW_TABLE_STATUS";
	case T_SHOW_PARAMETERS : return "T_SHOW_PARAMETERS";
	case T_SHOW_SERVER_STATUS : return "T_SHOW_SERVER_STATUS";
	case T_SHOW_WARNINGS : return "T_SHOW_WARNINGS";
	case T_SHOW_GRANTS : return "T_SHOW_GRANTS";
	case T_SHOW_LIMIT : return "T_SHOW_LIMIT";
	case T_CREATE_USER : return "T_CREATE_USER";
	case T_CREATE_USER_SPEC : return "T_CREATE_USER_SPEC";
	case T_DROP_USER : return "T_DROP_USER";
	case T_SET_PASSWORD : return "T_SET_PASSWORD";
	case T_RENAME_USER : return "T_RENAME_USER";
	case T_RENAME_INFO : return "T_RENAME_INFO";
	case T_LOCK_USER : return "T_LOCK_USER";
	case T_GRANT : return "T_GRANT";
	case T_PRIVILEGES : return "T_PRIVILEGES";
	case T_PRIV_LEVEL : return "T_PRIV_LEVEL";
	case T_PRIV_TYPE : return "T_PRIV_TYPE";
	case T_USERS : return "T_USERS";
	case T_REVOKE : return "T_REVOKE";
	case T_BEGIN : return "T_BEGIN";
	case T_COMMIT : return "T_COMMIT";
	case T_PREPARE : return "T_PREPARE";
	case T_DEALLOCATE : return "T_DEALLOCATE";
	case T_EXECUTE : return "T_EXECUTE";
	case T_ARGUMENT_LIST : return "T_ARGUMENT_LIST";
	case T_VARIABLE_SET : return "T_VARIABLE_SET";
	case T_VAR_VAL : return "T_VAR_VAL";
	case T_ROLLBACK : return "T_ROLLBACK";
	case T_HINT_OPTION_LIST : return "T_HINT_OPTION_LIST";
	case T_READ_STATIC : return "T_READ_STATIC";
	case T_MAX : return "T_MAX";
	default:return "Unknown";
	}
}



const char* get_type_symbol(int type)
{
	switch(type){
    case T_OP_EQ : 
        return " = ";      /* 2. Bool operators */
    case T_OP_LE : 
        return " <= ";
    case T_OP_LT : 
        return " < ";
    case T_OP_GE : 
        return " >= ";
    case T_OP_GT : 
        return " > ";
    case T_OP_NE : 
        return " != ";
    case T_OP_NOT:
        return " ! ";
    case T_OP_BTW:
        return " BETWEEN ";
    case T_OP_NOT_BTW:
        return " NOT BETWEEN ";
    case T_FUN_MAX : 
        return " MAX";
    case T_FUN_MIN : 
        return " MIN";
    case T_FUN_SUM : 
        return " SUM";
    case T_FUN_COUNT : 
        return " COUNT";
    case T_FUN_AVG : 
        return " AVG";
    case T_OP_IN:
        return " IN ";
    case T_OP_NOT_IN:
        return " NOT IN ";
    case T_OP_OR:
        return " OR ";
    case T_OP_AND:
        return " AND ";
    case T_OP_EXISTS:
        return " EXIST ";
    case T_OP_LIKE:
        return " LIKE ";
    case T_OP_NOT_LIKE:
        return " NOT LIKE ";
    case T_OP_IS:
        return " IS ";
    case T_OP_IS_NOT:
        return " IS NOT ";
    case T_OP_POS:
    case T_OP_NEG:
    default:
        return " Unknown ";
    }
}


void destroy_tree(ParseNode* root)
{
  int i;
  if(root == 0)
    return;
  for(i = 0; i < root->num_child_; ++i)
  {
    destroy_tree(root->children_[i]);
  }
  if(root->str_value_ != NULL)
  {
    parse_free((char*)root->str_value_);
  }
  if(root->num_child_)
  {
    parse_free(root->children_);
  }
  parse_free(root);
}

void print_tree(ParseNode* root, int level)
{
  int i;
  for(i = 0; i < level; ++i)
    fprintf(stderr,"    ");
  if(root == 0)
  {
    fprintf(stderr,"|-NULL\n");
    return;
  }

  fprintf(stderr,"|-%s", get_type_name(root->type_));
  switch(root->type_)
  {
  case T_BOOL:
    if (root->value_ == 1)
      fprintf(stderr," : TRUE\n");
    else if (root->value_ == 0)
      fprintf(stderr," : FALSE\n");
    else
      fprintf(stderr," : UNKNOWN\n");
    break;
  case T_BINARY:
    fprintf(stderr," : \\x");
    for(i = 0; i < root->value_; ++i)
    {
      fprintf(stderr,"%02x", (unsigned char)root->str_value_[i]);
    }
    fprintf(stderr,"\n");
    break;
  case T_INT:
  case T_FLOAT:
  case T_DOUBLE:
  case T_DECIMAL:
  case T_STRING:
  case T_DATE:
  case T_HINT:
  case T_IDENT:
    fprintf(stderr," : %s\n", root->str_value_);
    break;
  case T_FUN_SYS:
    fprintf(stderr," : %s\n", root->str_value_);
    break;
  default:
    fprintf(stderr,"\n");
    break;
  }
  for(i = 0; i < root->num_child_; ++i)
  {
    print_tree(root->children_[i], level+1);
  }
}

ParseNode* new_node(void *malloc_pool, SqlItemType type, int num)
{
  ParseNode* node = (ParseNode*)parse_malloc(sizeof(ParseNode), malloc_pool);
  if (node != NULL)
  {
    memset(node, 0 , sizeof(ParseNode));

    node->type_ = type;
    node->num_child_ = num;
    if(num > 0)
    {
      int64_t alloc_size = sizeof(ParseNode*) * num ;
      //node->children_ = (ParseNode**)malloc(alloc_size);
      node->children_ = (ParseNode**)parse_malloc(alloc_size, malloc_pool);
      if (node->children_ != NULL)
      {
        memset(node->children_, 0, alloc_size);
      }
      else
      {
        parse_free(node);
      }
    }
    else
    {
      node->children_ = 0;
    }
  }
  return node;
}

int count_child(ParseNode* root)
{
  if(root == 0) return 0;

  int count = 0;
  if(root->type_ != T_LINK_NODE)
  {
    return 1;
  }
  int i;
  for(i = 0; i < root->num_child_; ++i)
  {
    count += count_child(root->children_[i]);
  }
  return count;
}

void merge_child(ParseNode* node, ParseNode* source_tree, int* index)
{
  // assert(node);
  if (node == NULL || source_tree == NULL)
    return;

  if(source_tree->type_ == T_LINK_NODE)
  {
    int i;
    for(i = 0; i < source_tree->num_child_; ++i)
    {
      merge_child(node, source_tree->children_[i], index);
      source_tree->children_[i] = 0;
    }
    destroy_tree(source_tree);
  }
  else
  {
    assert(*index >= 0 && *index < node->num_child_);
    node->children_[*index] = source_tree;
    ++(*index);
  }
}

ParseNode* merge_tree(void *malloc_pool, SqlItemType node_tag, ParseNode* source_tree)
{
  int index = 0;
  int num = 0;
  ParseNode* node;
  if(source_tree == NULL)
    return NULL;
  num = count_child(source_tree);
  if ((node = new_node(malloc_pool, node_tag, num)) != NULL)
  {
    merge_child(node, source_tree, &index);
    assert(index == num);
  }
  return node;
}

ParseNode* new_terminal_node(void *malloc_pool, SqlItemType type)
{
  return new_node(malloc_pool, type, 0);
}

ParseNode* new_non_terminal_node(void *malloc_pool, SqlItemType node_tag, int num, ...)
{
  assert(num>0);
  va_list va;
  int i;

  ParseNode* node = new_node(malloc_pool, node_tag, num);
  if (node != NULL)
  {
    va_start(va, num);
    for( i = 0; i < num; ++i)
    {
      node->children_[i] = va_arg(va, ParseNode*);
    }
    va_end(va);
  }
  return node;
}

char* copy_expr_string(ParseResult* p, int expr_start, int expr_end)
{
  char *expr_string = NULL;
  if (p->input_sql_ != NULL && expr_start >= 0 && expr_end >= 0 && expr_end >= expr_start)
  {
    int len = expr_end - expr_start + 1;
    expr_string = (char*)parse_malloc(len + 1, p->malloc_pool_);
    if (expr_string != NULL)
    {
      memmove(expr_string, p->input_sql_ + expr_start - 1, len);
      expr_string[len] = '\0';
    }
  }
  return expr_string;
}
