#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

typedef struct  BlockHeader
{
    size_t size;
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
    header->previous    = NULL;
    header->next        = NULL;
}

void    jump(void** addr, int nbOfJump)
{
    for (int i = 0; i < nbOfJump; i++ )
            (*addr)++;
}

void*   findSpace(int size)
{
    BlockHeader *list = (BlockHeader*)memoryPool;
    void        *my_heap = memoryPool;

    list = list->next;
    if (list == NULL)
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
    while(last->next)
        last = last->next;
    BlockHeader* newBlock = (BlockHeader*)((char*)addr + totalSize);
    last->next = newBlock;
    newBlock->previous = last;
    newBlock->size = requestedSize;
    newBlock->next = NULL;
    current->size -= totalSize;
    return addr + sizeof(BlockHeader);
}

void customFree(void* ptr) // a refaire
{
    if (ptr == NULL)
        return;
    BlockHeader* block = (BlockHeader*)((char*)ptr - sizeof(BlockHeader));
    block->next = (BlockHeader*)memoryPool;
}

void    show_the_metadata(void *ptr)
{
    BlockHeader *test = (BlockHeader *)((char*)ptr - sizeof(BlockHeader));
    while(test)
    {
        if (ptr + test->size == test)
            break;
        test = test->next;
    }
    printf("size: %ld\n", test->size);
}

int main()
{
    initializeMemoryPool();
    printf("Memorypool -> %p\n", memoryPool);
    printf("%ld\n\n", (unsigned long int)memoryPool);
    
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

    printf("--------------\n");

    customFree(addr);
    customFree(addr2);
    customFree(addr3);
    
    if (munmap(memoryPool, POOL_SIZE) == -1)
    {
        perror("Failed to unmap memory pool");
        exit(EXIT_FAILURE);
    }
    return 0;
}