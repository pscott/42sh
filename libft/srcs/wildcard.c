#include "ft_printf.h"

void	wildcard(t_arg *specs, va_list arg, int modif)
{
	int value;

	value = va_arg(arg, int);
	if (modif == 0)
	{
		if (value < 0)
			specs->left = 1;
		specs->width = 1;
		if (value == -2147483647)
			specs->width_len = 0;
		else
			specs->width_len = value >= 0 ? value : -value;
	}
	else
	{
		if (value < 0)
		{
			value = 0;
			specs->precision = 0;
		}
		specs->precision_len = value;
	}
}
