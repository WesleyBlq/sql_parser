
#ifndef SQL_NON_RESERVED_KEYWORDS_H_
#define SQL_NON_RESERVED_KEYWORDS_H_

typedef struct _NonReservedKeyword
{
  const char *keyword_name;
  int keyword_type;
} NonReservedKeyword;

extern const NonReservedKeyword *non_reserved_keyword_lookup(const char *word);

#endif /* SQL_NON_RESERVED_KEYWORDS_H_ */

