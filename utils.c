int    init_malloc()
{
    void    *addr = mmap(NULL, /*small_size*/, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (addr == MAP_FAILED)
        return NULL;

    addr = mmap(NULL, /*tiny_size*/, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (addr == MAP_FAILED)
        return NULL;
}
//return 1 if error