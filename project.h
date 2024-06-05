#ifndef PROJECT_H
# define PROJECT_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdbool.h>

#define tiny 		1000
#define pool_tiny 	100000
#define small 		10000
#define pool_small 	1000000


typedef struct  Metadata
{
    size_t              size;
    void*               addr;
    struct Metadata* 	next;
    struct Metadata* 	previous;
}               Metadata;

typedef struct  s_malloc
{
    bool    init;

	void*	_tiny;
	void*	_small;
	void*	_large;
}               s_malloc;

void	*ft_malloc(size_t size);
void	ft_free(void *ptr);
void	*ft_realloc(void *ptr, size_t size);
void 	show_alloc_mem();

int		init_malloc();
void	*findSpace(int size, void* zone, int zone_size);

#endif