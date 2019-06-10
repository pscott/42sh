#include "ft_printf.h"

int		set_i(t_arg *specs)
{
	int i;

	if (specs->precision)
		if (specs->precision_len)
		{
			i = specs->precision_len;
			ft_special_memset(specs, '.', 1);
		}
		else
			i = 0;
	else
	{
		i = 6;
		ft_special_memset(specs, '.', 1);
	}
	return (i);
}
