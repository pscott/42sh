#include "libft.h"

int		err_no_env(void)
{
	ft_putstr_fd("error: no TERM variable found in environment.\n", 2);
	return (1);
}
