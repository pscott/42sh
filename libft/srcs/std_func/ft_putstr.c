#include "libft.h"

void	ft_putstr(char const *str)
{
	if (str)
	{
		while (*str)
		{
			ft_putchar(*str);
			str++;
		}
	}
}
