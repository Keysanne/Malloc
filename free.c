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
    if(list->addr != ptr)
    {
        printf("invalid free\n");
        return;
    }
    list->previous->next = list->next;
    if (list->next != NULL)
        list->next->previous = list->previous;
    pool->size += list->size + sizeof(Metadata);
    bzero(ptr, list->size + sizeof(Metadata));
}

void ft_free(void *ptr)
{
	//find the zone (small, tiny)
	return ;
}