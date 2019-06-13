#include "ft_printf.h"

void		ft_uitoa(t_arg *specs, unsigned long long n)
{
	int		len;
	int		tmp;

	len = ulen(specs, n);
	tmp = len;
	realloc_if_necessary(specs, len);
	while (n > 9)
	{
		specs->string[len - 1] = n % 10 + '0';
		n = n / 10;
		len--;
	}
	specs->string[0] = n + '0';
	specs->string += tmp;
}
