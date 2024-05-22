#include "project.h"

void    *ft_malloc(size_t size)
{
    // if (info.init == false)
    //     if (init_malloc() == 1)
    //         return NULL;
    




    void    *addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0); 
    if (addr == MAP_FAILED)
        return NULL;
    return addr;
}

int main()
{
    char *test, *test1, *test2;

    printf("%zu\n", sizeof(max_align_t));

    test = ft_malloc(2000000);
    printf("-  %p\n", test);
    test1 = ft_malloc(2000000);
    printf("-  %p\n", test1);
    test2 = ft_malloc(2000000);
    printf("-  %p\n", test2);

    return 0;
}
