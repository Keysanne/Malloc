#include "project.h"

t_malloc    info;

void    *ft_malloc(size_t size)
{
    void    *addr;

    if (info.init == false)
        if (init_malloc() == 1)
            return NULL;
    if (size <= tiny)
        addr = tiny_alloc(size);
    else if (size <= small)
        addr = small_alloc(size);
    else
        addr = large_alloc(size);
    return addr;
}

int main()
{
    char *test, *test1, *test2;

    test = ft_malloc(100);
    test1 = ft_malloc(5000);
    test2 = ft_malloc(100000);

    printf("tiny_zone: %p  | small_zone: %p\n\n", info.tiny_addr, info.small_addr);
    printf("tiny:  %p\nsmall: %p\nlarge: %p\n",test, test1, test2);

    return 0;
}
