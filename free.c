#include "project.h"

extern s_malloc    info;

void ft_bzero(void *ptr, size_t size)
{
	unsigned char* tmp = ptr;
	for (size_t i = 0; i < size; i++)
		tmp[i++] = '\0';
}

void customFree(void* ptr, void* zone)
{
    if (ptr == NULL)
        return;

    Metadata*	list	= zone;
    Metadata*	pool	= zone;
    
	while(list->addr != ptr && list)
        list = list->next;
    list->previous->next = list->next;
    if (list->next != NULL)
        list->next->previous = list->previous;
    pool->size += list->size + sizeof(Metadata);
    ft_bzero(ptr, list->size + sizeof(Metadata));
}

type_zone	find_zone(void* ptr)
{
	Metadata	*list;
	void	*tab[] = {info._tiny, info._small, info._large};

	for(int i = 0; i < 3; i++)
	{
		list = tab[i];
		for(list = list->next; list; list = list->next)
			if (list->addr == ptr)
				return i;
	}
	return -1;
}

int is_last_alloc()
{
	int x = 0;
	Metadata	*list;
	void	*tab[] = {info._tiny, info._small, info._large};

	for(int i = 0; i < 3; i++)
	{
		list = tab[i];
		for(list = list->next; list; list = list->next)
			x++;
	}
	return x;
}

void free(void *ptr)
{
	type_zone type;

	type = find_zone(ptr);
	if (type == -1)
	{
		write(1, "invalid free\n", 13);
		return;
	}
	switch (type)
	{
        case TINY:
			customFree(ptr, info._tiny);
			break;
        case SMALL:
			customFree(ptr, info._small);
			break;
        case LARGE:
			customFree(ptr, info._large);
			break;
    }
	if(is_last_alloc() == 0)
	{
		munmap(info._tiny, pool_tiny + sizeof(Metadata));
		munmap(info._small, pool_small + sizeof(Metadata));
		munmap(info._large,sizeof(Metadata));
		info.init = false;
	}
}