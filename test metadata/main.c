#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

typedef struct  BlockHeader
{
    size_t size;
    struct BlockHeader* next;
}               BlockHeader;

#define POOL_SIZE 100000

void* memoryPool;

void initializeMemoryPool()
{
    memoryPool = mmap(NULL, POOL_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (memoryPool == MAP_FAILED)
    {
        perror("Failed to allocate memory pool");
        exit(1);
    }

    BlockHeader* header = (BlockHeader*)memoryPool;
    header->size = POOL_SIZE - sizeof(BlockHeader);
    header->next = NULL;
}

void* customMalloc(size_t requestedSize)
{
    BlockHeader* current = (BlockHeader*)memoryPool;

    size_t totalSize = sizeof(BlockHeader) + requestedSize;

    while (current != NULL)
    {
        if (current->size >= totalSize)
        {
            if (current->size > totalSize)
            {
                BlockHeader* newBlock = (BlockHeader*)((char*)current + totalSize);
                newBlock->size = current->size - totalSize;
                newBlock->next = current->next;
                current->size = requestedSize;
                current->next = newBlock;
            }
            // printf("%p\n", (char*)current); // address without the "+10" of the metadata /!\ need alignment
            return (char*)current + sizeof(BlockHeader);
        }
        current = current->next;
    }
    return NULL;
}

void customFree(void* ptr)
{
    if (ptr == NULL)
        return;
    BlockHeader* block = (BlockHeader*)((char*)ptr - sizeof(BlockHeader));
    block->next = (BlockHeader*)memoryPool;
}

void    show_the_metadata(void *ptr)
{
    BlockHeader *test = (BlockHeader *)((char*)ptr - sizeof(BlockHeader));
    printf("%p\n", ptr);
    printf("size: %ld\n", test->size);
}

int main()
{
    initializeMemoryPool();
    void*   addr = customMalloc(100);
    void*   addr2 = customMalloc(200);
    void*   addr3 = customMalloc(300);

    printf("Memorypool -> %p\n", memoryPool);
    printf("1\n");
    printf("%lx  -  %lx\n", (unsigned long int)addr, (unsigned long int)addr + 100);
    show_the_metadata(addr);
    printf("2\n");
    printf("%lx  -  %lx\n", (unsigned long int)addr2, (unsigned long int)addr2 + 200);
    show_the_metadata(addr2);
    printf("3\n");
    printf("%lx  -  %lx\n", (unsigned long int)addr3, (unsigned long int)addr3 + 300);
    show_the_metadata(addr3);

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