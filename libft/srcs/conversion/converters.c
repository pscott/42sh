#include "ft_printf.h"

char	*convert(ULL num, int base, char *rep)
{
	static char	buffer[80];
	char		*ptr;

	ptr = &buffer[80];
	*ptr = 0;
	ptr--;
	if (num == 0)
		*--ptr = rep[num & base];
	while (num)
	{
		*--ptr = rep[num % base];
		num /= base;
	}
	return (ptr);
}

char	*convert_p(L num, int base, char *rep)
{
	static char	buffer[80];
	char		*ptr;

	ptr = &buffer[80];
	*ptr = 0;
	ptr--;
	if (num == 0)
		*--ptr = rep[num & base];
	while (num)
	{
		*--ptr = rep[num % base];
		num /= base;
	}
	return (ptr);
}
