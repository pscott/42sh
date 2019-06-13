#include "ft_printf.h"

int		null_data(t_arg *specs, ULL value)
{
	if (specs->precision && specs->precision_len == 0 && value == 0)
		return (1);
	return (0);
}
