#include "libft.h"
#include <unistd.h>

int		ft_putchar(int c)
{
	if (write(1, &c, 1) >= 0)
		return (1);
	else
		return (0);
}
