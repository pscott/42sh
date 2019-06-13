#include "libterm.h"

int		err_caps(void)
{
	ft_putstr_fd("error: missing terminal capabilities\n", 2);
	return (1);
}
