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
    // else if (size <= small)
    //     addr = small_alloc(size);
    // else
    //     addr = large_alloc(size);
        // addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0); 
        // if (addr == MAP_FAILED)
        //     return NULL;
    return addr;
}

int main()
{
    char *test, *test1, *test2;

    test = ft_malloc(20);
    test1 = ft_malloc(40);
    test2 = ft_malloc(60);

    printf("%lu\n", sizeof(max_align_t));
    printf("%d\n", tiny);
    printf("-> %p\n", info.tiny_addr);
    printf("-> %p\n", test);
    printf("-> %p\n", test1);
    printf("-> %p\n", test2);

    return 0;
}
