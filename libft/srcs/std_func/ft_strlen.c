#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	if (s)
	{
		while (*s)
		{
			i++;
			s++;
		}
	}
	return (i);
}
