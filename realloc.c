#include "project.h"

extern s_malloc    info;

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i = -1;
	unsigned char	*dest2 = (unsigned char *)dest;
	unsigned char	*src2 = (unsigned char *)src;

	while (++i < n)
		dest2[i] = src2[i];
	return (dest);
}

void	*right_zone(int type)
{
	if (type == -1)
	{
		printf("invalid pointer\n");
		return NULL;
	}
	switch (type)
	{
		case TINY:
			return info._tiny;
		case SMALL:
			return info._small;
		case LARGE:
			return info._large;
	}	
	return NULL;
}

void *realloc(void *ptr, size_t size)
{
	void		*final;
	int 		type = find_zone(ptr);
	Metadata	*list;

	list = right_zone(type);
	if (list == NULL)
		return NULL;
	for (; list; list = list->next)
		if (list->addr == ptr)
			break;
	final = malloc(size);
	if (!final)
		return NULL;
	if (size > list->size)
		size = list->size;
	ft_memcpy(final, ptr, size);
	free(ptr);
	return final;
}