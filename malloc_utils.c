#include "project.h"

extern t_malloc    info;

int    init_malloc()
{
    void    *addr = mmap(NULL, (small + sizeof(max_align_t)) * 100, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (addr == MAP_FAILED)
        return 1;
    info.small_addr = addr;
    info.small_size = (small + sizeof(max_align_t)) * 100;
    info.small_alloc = 0;
    addr = mmap(NULL, (tiny + sizeof(max_align_t)) * 100, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (addr == MAP_FAILED)
        return 1;
    info.tiny_addr = addr;
    info.tiny_size = (tiny + sizeof(max_align_t)) * 100;
    info.tiny_alloc = 0;
    info.init = true;
    return 0;
}

void    *tiny_alloc(size_t size)
{
    void    *addr;
    addr = info.tiny_addr;
    if(info.tiny_alloc == 100)
        return NULL;
    for (int i = 0; i < (tiny + sizeof(max_align_t)) * info.tiny_alloc; i++)
        addr++;
    while ((unsigned long int)addr % sizeof(max_align_t) != 0)
        addr++;
    info.tiny_alloc++;
    return addr;
}

void    *small_alloc(size_t size)
{
    void    *addr;
    addr = info.small_addr;
    if(info.small_alloc == 100)
        return NULL;
    for (int i = 0; i < (tiny + sizeof(max_align_t)) * info.small_alloc; i++)
        addr++;
    while ((unsigned long int)addr % sizeof(max_align_t) != 0)
        addr++;
    info.small_alloc++;
    return addr;
}

void    *large_alloc(size_t size)
{
    void    *addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (addr == MAP_FAILED)
        return NULL;
    info.large_alloc++;
    return addr;
}