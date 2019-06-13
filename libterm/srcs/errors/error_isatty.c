#include "libft.h"

int		err_not_terminal(void)
{
	ft_putstr_fd("error: not a terminal.\n", 2);
	return (0);
}
