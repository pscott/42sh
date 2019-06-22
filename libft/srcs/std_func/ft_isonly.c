#include "libft.h"

int		ft_isonly(const char *only, const char *s)
{
	int		i;

	if (!s || !only)
		return (1);
	i = 1;
	if (s[0] && s[1])
	{
		while (s[i])
		{
			if (!ft_strchr(only, s[i]))
				return (0);
			i++;
		}
	}
	return (1);
}
