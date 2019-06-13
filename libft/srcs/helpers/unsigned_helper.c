#include "ft_printf.h"

void	ft_uitoa_spec(t_arg *specs, ULL value)
{
	if (specs->l == 2)
		ft_uitoa(specs, (ULL)value);
	else if (specs->l == 1)
		ft_uitoa(specs, (UL)value);
	else if (specs->h == 2)
		ft_uitoa(specs, (unsigned char)value);
	else if (specs->h == 1)
		ft_uitoa(specs, (unsigned short int)value);
	else
		ft_uitoa(specs, (unsigned int)value);
}
