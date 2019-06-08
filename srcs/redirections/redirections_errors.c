#include "cmd_parsing.h"

int	bad_fd_error(int fd, int mode)
{
	if (mode != -1)
		ft_dprintf(STDERR_FILENO, "42sh: %d: bad file descriptor\n", fd);
	return (1);
}

int	ambi_redir_error(char *str, int mode)
{
	if (mode != -1)
		ft_dprintf(STDERR_FILENO, "42sh: %s: ambiguous redirect\n", str);
	return (1);
}

int	no_file_error(char *filename, int mode)
{
	if (mode != -1)
		ft_dprintf(2, "42sh: %s: No such file or directory\n", filename);
	return (1);
}

int	open_error(char *filename, int mode)
{
	if (mode != -1)
		ft_dprintf(2, "error opening file : %s\n", filename);
	return (1);
}
