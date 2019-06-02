#include "ftsh.h"
#include "exp_arith.h"

/*
**	Ascii to long long
*/

long long	ft_atoll(char *str)
{
	char					*s;
	unsigned long long int	i;
	int						neg;
	unsigned long long int	rep;

	s = (char *)str;
	i = 0;
	while (s[i] == '\n' || s[i] == '\t' || s[i] == '\r' || s[i] == '\v'
			|| s[i] == '\f' || s[i] == ' ')
		i++;
	neg = 1;
	if (s[i] == '-' || s[i] == '+')
		if (s[i++] == '-')
			neg = -1;
	rep = 0;
	while (s[i] >= '0' && s[i] <= '9' && s[i])
		rep = 10 * rep + (s[i++] - '0');
	return ((long long)rep * (long long)neg);
}
