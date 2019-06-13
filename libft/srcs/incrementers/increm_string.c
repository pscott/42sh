#include "ft_printf.h"

void	increm_string(t_arg *specs, int len)
{
	if (specs->string - specs->origin + len >= specs->mall_len - 1)
		realloc_if_necessary(specs, len);
	specs->string += len;
}
