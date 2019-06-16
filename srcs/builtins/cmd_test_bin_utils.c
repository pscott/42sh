#include "builtins.h"

static int			error_too_long(char *str)
{
	ft_dprintf(2, "42sh: test: %s: integer expression expected\n", str);
	return (2);
}

static long long	ft_atoll_test(char *str, long long *value)
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
	{
		if ((neg == 1 && 10 * rep + (s[i] - '0') > 9223372036854775807)
				|| (neg == -1
					&& (10 * rep + (s[i] - '0') - 1) > 9223372036854775807))
			return (2);
		rep = 10 * rep + (s[i++] - '0');
	}
	*value = (long long)rep * (long long)neg;
	return (0);
}

int					check_longlong(char *str, long long *value)
{
	*value = 0;
	if (ft_atoll_test(str, value))
		return (error_too_long(str));
	return (0);
}
