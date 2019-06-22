#include "ftsh.h"
#include <sys/stat.h>

int		case_echo(char **argv)
{
	int			i;
	struct stat	buf;

	i = 1;
	if (fstat(STDOUT_FILENO, &buf) == -1)
	{
		ft_dprintf(2, SHELL_NAME ": echo: write error: Bad file descriptor\n");
		return (1);
	}
	while (argv[i])
	{
		ft_dprintf(STDOUT_FILENO, "%s", argv[i]);
		i++;
		if (argv[i])
			ft_putchar(' ');
	}
	ft_putchar('\n');
	return (0);
}
