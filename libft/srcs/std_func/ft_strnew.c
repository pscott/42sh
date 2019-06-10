#include "libft.h"
#include <stdlib.h>

char		*ft_strnew(size_t size)
{
	char	*res;
	size_t	i;

	if (!(res = (char *)malloc(sizeof(*res) * (size + 1))))
		return (NULL);
	i = 0;
	while (size + 1)
	{
		res[i] = 0;
		i++;
		size--;
	}
	return (res);
}
