#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	if (s1 && s2)
	{
		if (n == 0)
			return (1);
		while (*s1 == *s2 && *s1 && n)
		{
			s1++;
			s2++;
			n--;
		}
		if (n == 0 || (*s1 == *s2 && !(*s1)))
			return (1);
	}
	return (0);
}
