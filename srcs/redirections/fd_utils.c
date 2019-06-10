#include "ftsh.h"

/*
**	Saving std fds : mode 1 is saving, mode 0 is restoring
*/

static	int		dup2_print_err(int old, int new)
{
	int ret;

	if ((ret = dup2(old, new)) == -1)
		ft_dprintf(2, SHELL_NAME ": error: dup2 failed\n");
	return (ret);
}

static	void	close_saves(int one, int two, int three)
{
	close(one);
	close(two);
	close(three);
}

void			save_reset_stdfd(int mode)
{
	static int	in = -1;
	static int	out = -1;
	static int	err = -1;
	static int	lastmode = -1;

	if (mode == 1 && lastmode != 1)
	{
		lastmode = 1;
		in = dup2_print_err(STDIN_FILENO, 10);
		out = dup2_print_err(STDOUT_FILENO, 11);
		err = dup2_print_err(STDERR_FILENO, 12);
		lastmode = 1;
	}
	else if (mode == 0 && lastmode == 1)
	{
		dup2_print_err(in, STDIN_FILENO);
		dup2_print_err(out, STDOUT_FILENO);
		dup2_print_err(err, STDERR_FILENO);
		close_saves(in, out, err);
		in = -1;
		out = -1;
		err = -1;
		lastmode = 0;
	}
}
