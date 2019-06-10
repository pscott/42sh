#include "ft_printf.h"

void	increm_format(char **s1, int len)
{
	if (s1 && *s1 && **s1)
		*s1 += len;
}
