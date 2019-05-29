#include "42sh.h"
#include "builtins.h"

int		case_echo(char **argv)
{
	int i;

	i = 1;
	while (argv[i])
	{
		ft_printf("%s", argv[i]);
		i++;
		if (argv[i])
			ft_putchar(' ');
	}
	ft_putchar('\n');
	return (0);
}
