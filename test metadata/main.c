#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

typedef struct  BlockHeader
{
    size_t              size;
    void*               addr;
    struct BlockHeader* next;
    struct BlockHeader* previous;
}               BlockHeader;

#define POOL_SIZE 1000000

void* memoryPool;

void initializeMemoryPool()
{
    memoryPool = mmap(NULL, POOL_SIZE + sizeof(BlockHeader), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (memoryPool == MAP_FAILED)
    {
        perror("Failed to allocate memory pool");
        exit(1);
    }
    BlockHeader* header = (BlockHeader*)memoryPool;
    header->size		= POOL_SIZE;
    header->addr        = memoryPool;
    header->next        = NULL;
    header->previous    = NULL;
}

void    jump(void** addr, int nbOfJump)
{
    for (int i = 0; i < nbOfJump; i++ )
            (*addr)++;
}

void*   findSpace(int size)
{
    BlockHeader *list = (BlockHeader*)memoryPool;
    void        *my_heap = list->addr;

    if (list->size < size)
        return NULL;
    list = list->next;
    if (list == NULL)
        return my_heap;
    while(list)
    {
        if ((unsigned long int)list->addr - (unsigned long int)my_heap > size + sizeof(BlockHeader))
            break;
        my_heap = list->addr;
        jump(&my_heap, list->size);
        list = list->next;
    }
    if ((unsigned long int)my_heap + size + sizeof(BlockHeader) < (unsigned long int)memoryPool + POOL_SIZE)
        return my_heap;
    return NULL;
}

void* customMalloc(size_t requestedSize)
{
    BlockHeader*    current = (BlockHeader*)memoryPool;
    BlockHeader*    last = (BlockHeader*)memoryPool;
    size_t          totalSize = sizeof(BlockHeader) + requestedSize;
    void*           addr = findSpace(totalSize);

    if (addr == NULL)
        return NULL;
    while((unsigned long int)last->addr < (unsigned long int)addr && last->next)
        last = last->next;
    BlockHeader* newBlock = (BlockHeader*)((char*)addr + totalSize);
    newBlock->size = requestedSize;
    newBlock->previous = last;
    newBlock->addr = addr + sizeof(BlockHeader);
    if (last->next != NULL)
        newBlock->next = last->next;
    else
        newBlock->next = NULL;
    last->next = newBlock;
    current->size -= totalSize;
    return addr + sizeof(BlockHeader);
}

void customFree(void* ptr)
{
    if (ptr == NULL)
        return;
    BlockHeader *list = (BlockHeader *)memoryPool;
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
    BlockHeader *pool = (BlockHeader *)memoryPool;
    pool->size += list->size + sizeof(BlockHeader);
    bzero(ptr, list->size + sizeof(BlockHeader));
}

void    show_the_metadata(void *ptr) // cest nul
{
    BlockHeader *test = (BlockHeader *)((char*)ptr - sizeof(BlockHeader));
    test = test->next;
    printf("size: %ld\n", test->size);
}

int main()
{
    initializeMemoryPool();
    printf("Memorypool -> %p\n\n", memoryPool);
    
    void*   addr = customMalloc(100);
    void*   addr2 = customMalloc(50);
    void*   addr3 = customMalloc(300);


    printf("1\n");
    printf("%lx  -  %lx\n", (unsigned long int)addr, (unsigned long int)addr + 100);
    show_the_metadata(addr);
    printf("2\n");
    printf("%lx  -  %lx\n", (unsigned long int)addr2, (unsigned long int)addr2 + 50);
    show_the_metadata(addr2);
    printf("3\n");
    printf("%lx  -  %lx\n", (unsigned long int)addr3, (unsigned long int)addr3 + 300);
    show_the_metadata(addr3);

    customFree(addr);
    customFree(addr2);
    // customFree(addr3);

    addr = customMalloc(100);
    addr2 = customMalloc(50);
    
    printf("------------\n");

     printf("1\n");
    printf("%lx  -  %lx\n", (unsigned long int)addr, (unsigned long int)addr + 100);
    show_the_metadata(addr);
    printf("2\n");
    printf("%lx  -  %lx\n", (unsigned long int)addr2, (unsigned long int)addr2 + 50);
    show_the_metadata(addr2);
    printf("3\n");
    printf("%lx  -  %lx\n", (unsigned long int)addr3, (unsigned long int)addr3 + 300);
    show_the_metadata(addr3);

    printf("------------\n");

    BlockHeader *test = (BlockHeader *)memoryPool;
    while(test)
    {
        printf("%ld\n", test->size);
        test = test->next;
    }

    
    if (munmap(memoryPool, POOL_SIZE) == -1)
    {
        perror("Failed to unmap memory pool");
        exit(EXIT_FAILURE);
    }
    return 0;
}