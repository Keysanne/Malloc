#ifndef PROJECT_H
# define PROJECT_H

#include <stddef.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdbool.h>

#define tiny 		4096
#define pool_tiny 	409600
#define small 		40960
#define pool_small 	4096000


typedef enum	type
{
	TINY,
	SMALL,
	LARGE
}				type_zone;

typedef struct  Metadata
{
    size_t              size;
    void*               addr;
    struct Metadata* 	next;
    struct Metadata* 	previous;
}               Metadata;

typedef struct  s_malloc
{
    bool    			init;
	unsigned long int 	total;

	void*	_tiny;
	void*	_small;
	void*	_large;
}               s_malloc;

void	*malloc(size_t size);
void	free(void *ptr);
void	*realloc(void *ptr, size_t size);
void 	show_alloc_mem();

int			init_malloc();
type_zone	find_zone(void* ptr);
void		*find_space(int size, void* zone, int zone_size);


void printint(int nb);
void printadress(unsigned long int ptr);


#endif