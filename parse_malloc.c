#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "parse_malloc.h"

/*mem pool function is not implemented now*/



/* get memory from the thread obStringBuf, and not release untill thread quits */
void *parse_malloc(const size_t nbyte, void *malloc_pool)
{
    void *ptr = NULL;
    /*��ǰ�ò���û�б�ʹ��*/
    malloc_pool = malloc_pool;

    ptr = malloc(nbyte);

    if (NULL == ptr)
    {
        printf("parse_strdup gets string buffer error\n");
    }
        
    return ptr;
}

/* ptr must point to a memory allocated by parse_malloc.cpp */
void *parse_realloc(void *ptr, size_t nbyte, void *malloc_pool)
{
    void *new_ptr = NULL;
    /*��ǰ�ò���û�б�ʹ��*/
    malloc_pool = malloc_pool;

    new_ptr = realloc(ptr, nbyte);
    if (NULL == new_ptr)
    {
        printf("parse_strdup gets string buffer error\n");
    }
        
    return new_ptr;
}

char *parse_strdup(const char *str, void *malloc_pool)
{
    char *new_str = NULL;
    if (str)
    {
        size_t len = strlen(str);
        if ((new_str = (char *)parse_malloc(len + 1, malloc_pool)) != NULL)
        {
            memmove(new_str, str, len + 1);
        }
        else
        {
            printf("parse_strdup gets string buffer error\n");
        }
    }
    return new_str;
}

void parse_free(void *ptr)
{
    free(ptr);
}
