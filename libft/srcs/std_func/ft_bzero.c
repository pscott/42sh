#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t i;

	if (n == 0 || !s)
		return ;
	i = 0;
	while (i < n)
	{
		((char *)s)[i] = 0;
		i++;
	}
}
