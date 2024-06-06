#include "project.h"

extern s_malloc    info;

void	print_zone(Metadata* zone)
{
	zone = zone->next;
	while(zone)
	{
		printf("0x%lx - 0x%lx : ", (unsigned long int)zone->addr, (unsigned long int)zone->addr + zone->size);
		printf("%zu bytes\n", zone->size);
		info.total += zone->size;
		zone = zone->next;
	}
}

void	show_alloc_mem()
{
	if (info.init == false)
	{
		printf("No allocation detected\n");
		return;
	}
	info.total = 0;
	printf("TINY  : %p\n", info._tiny);
	print_zone(info._tiny);
	printf("SMALL : %p\n", info._small);
	print_zone(info._small);
	printf("LARGE : %p\n", info._large);
	print_zone(info._large);
	printf("Total : %ld bytes\n", info.total);
}