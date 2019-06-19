#include "cmd_parsing.h"

int	bad_fd_error(int fd, int mode)
{
	if (mode != -1)
	{
		ft_dprintf(STDERR_FILENO, SHELL_NAME ": %d: bad file descriptor", fd);
		ft_dprintf(STDERR_FILENO, " (must be less than 9)", fd);
	}
	return (1);
}

int	ambi_redir_error(char *str, int mode)
{
	if (mode != -1)
		ft_dprintf(STDERR_FILENO, SHELL_NAME ": %s: ambiguous redirect\n", str);
	return (1);
}

int	no_file_error(char *filename, int mode)
{
	if (mode != -1)
		ft_dprintf(2, SHELL_NAME ": %s: No such file or directory\n", filename);
	return (1);
}

int	open_error(char *filename, int mode)
{
	if (mode != -1)
		ft_dprintf(2, "error accessing or opening file : %s\n", filename);
	return (1);
}
