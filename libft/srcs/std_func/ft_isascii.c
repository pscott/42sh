#include "libft.h"

int		ft_isascii(int c)
{
	if (c > -1 && c < 128)
		return (1);
	return (0);
}
