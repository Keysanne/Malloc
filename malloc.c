#include "project.h"

void *ft_malloc(size_t size)
{
    void    *addr;

    addr = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (addr == MAP_FAILED)
        return NULL;
    printf("-  %p\n", addr);
    return addr;
}

int main()
{
    int *test;

    test = ft_malloc(2);
    printf("-  %p\n", test);
    test = malloc(2);
    printf("%p\n", test);

    return 0;
}