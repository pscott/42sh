#include "ft_printf.h"

void	ft_special_memset(t_arg *specs, char c, int len)
{
	len = max(0, len);
	realloc_if_necessary(specs, len);
	ft_memset(specs->string, (unsigned char)c, len);
	increm_string(specs, len);
}
