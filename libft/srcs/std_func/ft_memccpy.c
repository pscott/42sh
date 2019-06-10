#include "libft.h"

void	*ft_memccpy(void *restrict d, const void *restrict s, int c, size_t n)
{
	size_t			i;
	unsigned char	*source;
	unsigned char	*desti;

	i = 0;
	if (!d | !s)
		return (NULL);
	source = (unsigned char *)s;
	desti = (unsigned char *)d;
	while (i < n)
	{
		desti[i] = source[i];
		if (source[i] == (unsigned char)c)
			return (desti + i + 1);
		i++;
	}
	return (NULL);
}
