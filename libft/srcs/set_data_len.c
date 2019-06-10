#include "ft_printf.h"

void	set_data_len(t_arg *specs, LL value)
{
	if (specs->type == 'x')
		value_x(specs, value);
	else if (specs->type == 'X')
		value_xx(specs, value);
	else if (specs->type == 'o')
		value_o(specs, value);
}
