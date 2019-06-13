#include "libft.h"

void	ft_free_ntab(char **tab)
{
	int		i;

	if (!tab)
		return ;
	i = -1;
	while (tab[++i])
		ft_memdel((void*)&(tab[i]));
	ft_memdel((void*)&tab);
}
