#include "libft.h"

void	ft_putendl(char const *str)
{
	if (str)
	{
		while (*str)
		{
			ft_putchar(*str);
			str++;
		}
	}
	ft_putchar('\n');
}
