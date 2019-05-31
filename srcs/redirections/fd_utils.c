#include "42sh.h"

/*
**	Saving std fds : mode 1 is saving, mode 0 is restoring
*/

void	save_reset_stdfd(int mode)
{
	static int	in = -1;
	static int	out = -1;
	static int	err = -1;
	int			lastmode = -1;

	if (mode == 1 && lastmode != 1)
	{
		in = dup(STDIN_FILENO);
		out = dup(STDOUT_FILENO);
		err = dup(STDERR_FILENO);
	}
	if (mode == 0 && lastmode != 0)
	{
		dup2(in, STDIN_FILENO);
		dup2(out, STDOUT_FILENO);
		dup2(err, STDERR_FILENO);
		close(in);
		close(out);
		close(err);
		in = -1;
		out = -1;
		err = -1;
	}
}
