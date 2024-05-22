#ifndef PROJECT_H
# define PROJECT_H

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdbool.h>

#define tiny 1000
#define small 10000

typedef struct  g_list
{
    unsigned long   addr;
    int             type;
    size_t          size;
    struct t_list  *next;
}               t_list;

typedef struct  g_malloc
{
    bool            init;
    
    void            *small_addr;
    unsigned int    small_size;

    void            *tiny_addr;
    unsigned int    tiny_size;

    t_list          *all_alloc;
}               t_malloc;

void free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);
void show_alloc_mem();

int    init_malloc();


#endif