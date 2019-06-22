#include "libft.h"
#include <unistd.h>

int		ft_putchar(int c)
{
	return (write(1, &c, 1));
}
