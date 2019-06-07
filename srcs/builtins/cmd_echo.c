#include "ftsh.h"

int		case_echo(char **argv)
{
	int i;

	i = 1;
	while (argv[i])
	{
		ft_dprintf(OUTPUT_FD, "%s", argv[i]);
		i++;
		if (argv[i])
			ft_putchar(' ');
	}
	ft_putchar('\n');
	return (0);
}
