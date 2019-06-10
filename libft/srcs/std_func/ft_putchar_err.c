#include "libft.h"

int		ft_putchar_err(int c)
{
	if (write(STDERR_FILENO, &c, 1) == -1)
		return (0);
	return (1);
}
