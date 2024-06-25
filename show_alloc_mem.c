#include "project.h"

extern s_malloc    info;

void	ft_putnbradress(unsigned long nb)
{
	char	base[] = "0123456789abcdef";

	if (nb < 16)
	{
		write(1, &base[nb], 1);
	}
	if (nb >= 16)
	{
		ft_putnbradress(nb / 16);
		ft_putnbradress(nb % 16);
	}
}

void printadress(unsigned long int ptr)
{
	write(1, "0x", 2);
	ft_putnbradress(ptr);
}

void printint(int nb)
{
	char	base[] = "0123456789";

	if (nb < 10)
	{
		write(1, &base[nb], 1);
	}
	if (nb >= 10)
	{
		printint(nb / 10);
		printint(nb % 10);
	}
}

void	print_zone(Metadata* zone)
{
	zone = zone->next;
	while(zone)
	{
		printadress((unsigned long int)zone->addr);
		write(1, " - ", 3);
		printadress((unsigned long int)zone->addr + zone->size);
		write(1, " : ", 3);
		printint(zone->size);
		write(1, " bytes\n", 7);
		info.total += zone->size;
		zone = zone->next;
	}
}

void	show_alloc_mem()
{
	if (info.init == false)
	{
		write(1, "No allocation detected\n", 23);
		return;
	}
	info.total = 0;
	write(1, "TINY : ", 7);
	printadress((unsigned long int)info._tiny);
	write(1, "\n", 1);
	print_zone(info._tiny);

	write(1, "SMALL : ", 7);
	printadress((unsigned long int)info._small);
	write(1, "\n", 1);
	print_zone(info._small);

	write(1, "LARGE : ", 7);
	printadress((unsigned long int)info._large);
	write(1, "\n", 1);
	print_zone(info._large);

	write(1, "Total : ", 8);
	printint(info.total);
	write(1, " bytes\n", 7);
}