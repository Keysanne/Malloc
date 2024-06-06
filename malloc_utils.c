#include "project.h"

extern s_malloc    info;

void *initializeMemoryPool(int size)
{
    void* ptr = mmap(NULL, size + sizeof(Metadata), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (ptr == MAP_FAILED)
        return NULL;

    Metadata* header 	= ptr;
    
	header->size		= size;
    header->addr        = ptr;
    header->next        = NULL;
    header->previous    = NULL;
	return ptr;
}

int	init_malloc()
{
	info._tiny 	=  initializeMemoryPool(pool_tiny);
	info._small = initializeMemoryPool(pool_small);
	info._large = initializeMemoryPool(0);
	if (info._tiny == NULL || info._small == NULL || info._large == NULL)
	{
		if (info._tiny != NULL)
			munmap(info._tiny, pool_tiny + sizeof(Metadata));
		if (info._small != NULL)
			munmap(info._small, pool_small + sizeof(Metadata));
		if (info._large != NULL)
			munmap(info._large,sizeof(Metadata));
		return 1;
	}
	info.init = true;
	return 0;
}

void    *jump(void* addr, int nbOfJump)
{
    for (int i = 0; i < nbOfJump; i++ )
		addr++;
	return addr;
}

void   *findSpace(int size, void* zone, int zone_size)
{
    Metadata*	list 	= zone;
    void*		my_heap = list->addr;

    if (list->size < size)
        return NULL;
    list = list->next;
    if (list == NULL)
        return my_heap;
    for( ; list; list = list->next)
    {
        if ((unsigned long int)list->addr - (unsigned long int)my_heap > size + sizeof(Metadata))
            break;
        my_heap = jump(list->addr, list->size);
    }
    if ((unsigned long int)my_heap + size + sizeof(Metadata) < (unsigned long int)zone + zone_size)
        return my_heap;
    return NULL;
}