#ifndef PROJECT_H
# define PROJECT_H

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct  g_list
{
    unsigned long   addr;
    int             type;
    size_t          size;
    struct t_list  *next;
}               t_list;

typedef struct  g_malloc
{
    bool    init;
    
    unsigned long   small_addr;
    unsigned long   small_size;

    unsigned long   tiny_addr;
    unsigned long   tiny_size;

    t_list          *all_alloc;
}               t_malloc;


t_malloc    info =  /*GLOBAL*/
{
    .init = false,
    .all_alloc = NULL,
};

void free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);
void show_alloc_mem();

#endif