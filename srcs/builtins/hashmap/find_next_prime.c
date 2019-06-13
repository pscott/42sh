#include "hashmap.h"
#include <limits.h>

static int		is_prime(int nb)
{
	int	i;

	if (nb < 2)
		return (FALSE);
	if (nb <= 3)
		return (TRUE);
	if ((nb % 2 == 0) || (nb % 3 == 0))
		return (FALSE);
	i = 5;
	while (i * i < (int)nb)
	{
		if ((nb % i == 0) || (nb % (i + 2) == 0))
			return (FALSE);
		i += 6;
	}
	return (TRUE);
}

/*
**	nb < u32 max
*/

int				find_next_prime(int nb)
{
	while (++nb && nb <= INT_MAX)
	{
		if (is_prime(nb))
			return (nb);
	}
	return (0);
}
