#include "project.h"

extern t_malloc    info;

void large_free(void *ptr)
{
    munmap(ptr, 10/*size matter*/);
    info.large_alloc--;
}

void free(void *ptr)
{
    if (size <= tiny)
        info.tiny_alloc--;
    else if (size <= small)
        info.small_alloc--;
    else
        large_free(ptr);
    if (info.tiny_alloc == 0 && info.small_alloc == 0 && info.large_alloc == 0)
    {
        info.init = false;
        if (munmap(info.tiny_addr, info.tiny_size) == -1)
            printf("error munmap\n");
        if (munmap(info.small_addr, info.small_size) == -1)
            printf("error munmap\n");
    }
    return addr;
}