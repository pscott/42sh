#include "libft.h"

void	ft_strclr(char *s)
{
	if (s)
	{
		while (*s)
		{
			*s = 0;
			s++;
		}
	}
}
