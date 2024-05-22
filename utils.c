#include "project.h"

extern t_malloc    info;

int    init_malloc()
{
    void    *addr = mmap(NULL, (small + sizeof(max_align_t)) * 100, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (addr == MAP_FAILED)
        return 1;
    info.small_addr = addr;
    addr = mmap(NULL, (tiny + sizeof(max_align_t)) * 100, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (addr == MAP_FAILED)
        return 1;
    info.tiny_addr = addr;
    info.init = true;

    return 0;
}
//return 1 if error