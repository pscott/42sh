#include "libft.h"

size_t	ft_strnlen(const char *str, size_t n)
{
	size_t	i;

	if (!str || n == 0)
		return (0);
	i = 0;
	while (str[i] && i < n)
		i++;
	return (i);
}
