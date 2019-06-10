#include "ft_printf.h"

void	ft_strncat_move(char *src, int n, t_arg *specs)
{
	realloc_if_necessary(specs, n);
	ft_memcpy(specs->string, src, n);
	increm_string(specs, n);
}
