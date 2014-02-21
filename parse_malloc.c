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

char *parse_strndup(const char *str, size_t nbyte, void *malloc_pool)
{
    char *new_str = NULL;
    if (str)
    {
        if ((new_str = (char *)parse_malloc(nbyte, malloc_pool)) != NULL)
        {
            memmove(new_str, str, nbyte);
        }
        else
        {
            printf("parse_strdup gets string buffer error");
        }
    }
    return new_str;
}

char *parse_strdup(const char *str, void *malloc_pool)
{
    char *new_str = NULL;
    if (str)
    {
        new_str = parse_strndup(str, strlen(str) + 1, malloc_pool);
    }
    return new_str;
}

void parse_free(void *ptr)
{
    if  (ptr == 0)
        return;
    
    free(ptr);
    ptr = NULL;
}

