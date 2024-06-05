#include "project.h"

s_malloc    info;

void *customMalloc(size_t requestedSize, void* ptr, int zone_size)
{
    Metadata*    	current = (Metadata*)ptr, *last = (Metadata*)ptr;
    size_t          totalSize = sizeof(Metadata) + requestedSize;
    void*           addr = findSpace(totalSize, ptr, zone_size);

    if (addr == NULL)
        return NULL;
    while((unsigned long int)last->addr < (unsigned long int)addr && last->next)
        last = last->next;
    Metadata* newBlock = (Metadata*)((char*)addr + totalSize);
    newBlock->size = requestedSize;
    newBlock->previous = last;
    newBlock->addr = addr + sizeof(Metadata);
    if (last->next != NULL)
        newBlock->next = last->next;
    else
        newBlock->next = NULL;
    last->next = newBlock;
    current->size -= totalSize;
    return addr + sizeof(Metadata);
}

void    *ft_malloc(size_t size)
{
    void    *addr;

    if (info.init == false)
        if (init_malloc() == 1)
            return NULL;
    if (size <= tiny)
        addr = customMalloc(size, info._tiny, pool_tiny);
    else if (size <= small)
        addr = customMalloc(size, info._small, pool_small);
    // else
    //     addr = large_alloc(size);
    return addr;
}

int main()
{
    char *test, *test1, *test2;

    test  = ft_malloc(100);
    test1 = ft_malloc(500);
    test2 = ft_malloc(10);

    printf("s_zo:%p  -  %p\nt_zo:%p  -  %p\n", info._small, info._small + pool_small,  info._tiny, info._tiny + pool_tiny);
    printf("1st: %p\n2nd: %p\n3rd: %p\n",test, test1, test2);

    return 0;
}