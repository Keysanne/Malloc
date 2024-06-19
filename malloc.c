#include "project.h"

s_malloc    info;

void	*large_alloc(size_t requestedSize)
{
	size_t totalSize = requestedSize + sizeof(Metadata);

	void* ptr = mmap(NULL, totalSize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (ptr == MAP_FAILED)
		return NULL;

	Metadata*	last 		= info._large;
	Metadata*	newBlock 	= (Metadata*)((char*)ptr + totalSize);
	
	while(last->next)
		last = last->next;
	newBlock->size 	= requestedSize;
	newBlock->previous = last;
	newBlock->addr	= ptr;
	newBlock->next 	= NULL;
	last->next 		= newBlock;
	return ptr;
}

void *customMalloc(size_t requestedSize, void* ptr, int zone_size)
{
    Metadata*    	current 	= ptr, *last = ptr;
    size_t          totalSize 	= sizeof(Metadata) + requestedSize;
    void*           addr 		= find_space(totalSize, ptr, zone_size);

    if (addr == NULL)
        return NULL;
    while((unsigned long int)last->addr < (unsigned long int)addr && last->next)
        last = last->next;
    
	Metadata*	newBlock 	= (Metadata*)((char*)addr + totalSize);

    newBlock->size 		= requestedSize;
    newBlock->previous 	= last;
    newBlock->addr 		= addr + sizeof(Metadata);
    if (last->next != NULL)
        newBlock->next 	= last->next;
    else
        newBlock->next 	= NULL;
    last->next 			= newBlock;
    current->size 		-= totalSize;
    return addr + sizeof(Metadata);
}

void    *malloc(size_t size)
{
    void    *addr;

    if (info.init == false)
        if (init_malloc() == 1)
            return NULL;
    if (size <= tiny)
        addr = customMalloc(size, info._tiny, pool_tiny);
    else if (size <= small)
        addr = customMalloc(size, info._small, pool_small);
    else
        addr = large_alloc(size);
    return addr;
}