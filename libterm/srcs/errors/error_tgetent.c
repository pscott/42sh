#include "libft.h"

int		err_noentry(void)
{
	ft_putstr_fd("error: no entry found for termtype\n", 2);
	return (1);
}

int		err_no_database(void)
{
	ft_putstr_fd("error: no database found\n", 2);
	return (1);
}
