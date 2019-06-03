#include "libft.h"

void	ft_print_ntab(char **ntab)
{
	unsigned int i;

	i = 0;
	if (!ntab)
	{
		ft_putendl("(null)");
		return ;
	}
	while (ntab[i])
	{
		ft_putendl(ntab[i]);
		i++;
	}
}
