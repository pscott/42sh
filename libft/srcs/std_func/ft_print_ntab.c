#include "libft.h"

void	ft_print_ntab(char **ntab)
{
	unsigned int i;

	i = 0;
	if (!ntab)
		return ;
	while (ntab[i])
	{
		ft_putendl(ntab[i]);
		i++;
	}
}
