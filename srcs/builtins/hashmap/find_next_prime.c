#include "hashmap.h"

static t_bool	is_prime(unsigned int nb)
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

unsigned int	find_next_prime(unsigned int nb)
{
	while (++nb)//< u32 max
	{
		if (is_prime(nb))
			return (nb);
	}
	return (0);
}

unsigned int	find_prev_prime(unsigned int nb)
{
	if (nb < 5)
		return (3);
	while (--nb >= 3)
	{
		if (is_prime(nb))
			return (nb);
	}
	return (nb);
}
