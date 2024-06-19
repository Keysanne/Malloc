#include "project.h"

extern s_malloc    info;

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
    bzero(ptr, list->size + sizeof(Metadata));
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

void free(void *ptr)
{
	type_zone type;

	type = find_zone(ptr);
	if (type == -1)
	{
		printf("invalid free\n");
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
}