#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

typedef struct  Metadata
{
    size_t              size;
    void*               addr;
    struct Metadata* 	next;
    struct Metadata* 	previous;
}               Metadata;

#define POOL_SIZE 1000000

void* memoryPool;

void *initializeMemoryPool(int size)
{
    void* ptr = mmap(NULL, size + sizeof(Metadata), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (ptr == MAP_FAILED)
    {
        printf("Failed to allocate memory pool");
        exit(1);
    }
    Metadata* header = (Metadata*)ptr;
    header->size		= size;
    header->addr        = ptr;
    header->next        = NULL;
    header->previous    = NULL;
	return ptr;
}

void    *jump(void* addr, int nbOfJump)
{
    for (int i = 0; i < nbOfJump; i++ )
		addr++;
	return addr;
}

void   *findSpace(int size, void* ptr, int zone_size)
{
    Metadata *list = (Metadata*)ptr;
    void        *my_heap = list->addr;

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
    if ((unsigned long int)my_heap + size + sizeof(Metadata) < (unsigned long int)ptr + zone_size)
        return my_heap;
    return NULL;
}

void *customMalloc(size_t requestedSize, void* ptr, int zone_size)
{
    Metadata*    current = (Metadata*)ptr;
    Metadata*    last = (Metadata*)ptr;
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

void customFree(void* ptr, void* zone)
{
    if (ptr == NULL)
        return;
    Metadata *list = (Metadata *)zone;
    while(list->addr != ptr && list)
        list = list->next;
    if(list->addr != ptr)
    {
        printf("invalid free\n");
        exit(1);
    }
    list->previous->next = list->next;
    if (list->next != NULL)
        list->next->previous = list->previous;
    Metadata *pool = (Metadata *)zone;
    pool->size += list->size + sizeof(Metadata);
    bzero(ptr, list->size + sizeof(Metadata));
}

void    show_the_metadata(void *ptr, void* zone)
{
    Metadata *list = (Metadata *)zone;
	while(list)
	{
		if ((unsigned long int)list->addr == (unsigned long int)ptr)
			break;
	    list = list->next;
	}
	if (!list)
	{
		printf("This address '%p' isn't allocated\n", ptr);
		return ;
	}
    printf("size: %ld\n", list->size);
}

int main()
{
    memoryPool = initializeMemoryPool(POOL_SIZE);
    printf("Memorypool -> %p\n\n", memoryPool);
    
    void*   addr = customMalloc(100, memoryPool, POOL_SIZE);
    void*   addr2 = customMalloc(50, memoryPool, POOL_SIZE);
    void*   addr3 = customMalloc(300, memoryPool, POOL_SIZE);


    printf("1\n");
    printf("%lx  -  %lx\n", (unsigned long int)addr, (unsigned long int)addr + 100);
    show_the_metadata(addr, memoryPool);
    printf("2\n");
    printf("%lx  -  %lx\n", (unsigned long int)addr2, (unsigned long int)addr2 + 50);
    show_the_metadata(addr2, memoryPool);
    printf("3\n");
    printf("%lx  -  %lx\n", (unsigned long int)addr3, (unsigned long int)addr3 + 300);
    show_the_metadata(addr3, memoryPool);

    customFree(addr, memoryPool);
    customFree(addr2, memoryPool);
    // customFree(addr3);

    addr = customMalloc(100, memoryPool, POOL_SIZE);
    addr2 = customMalloc(50, memoryPool, POOL_SIZE);
    
    printf("------------\n");

     printf("1\n");
    printf("%lx  -  %lx\n", (unsigned long int)addr, (unsigned long int)addr + 100);
    show_the_metadata(addr, memoryPool);
    printf("2\n");
    printf("%lx  -  %lx\n", (unsigned long int)addr2, (unsigned long int)addr2 + 50);
    show_the_metadata(addr2, memoryPool);
    printf("3\n");
    printf("%lx  -  %lx\n", (unsigned long int)addr3, (unsigned long int)addr3 + 300);
    show_the_metadata(addr3, memoryPool);

    printf("------------\n");

    customFree(addr, memoryPool);
    customFree(addr2, memoryPool);
	customFree(addr3, memoryPool);
    
	Metadata *test = (Metadata *)memoryPool;
    while(test)
    {
        printf("%ld\n", test->size);
        test = test->next;
    }
    
    if (munmap(memoryPool, POOL_SIZE) == -1)
        perror("Failed to unmap memory pool");
    return 0;
}