#include "42sh.h"

void	save_reset_stdfd(int mode)
{
	static int	in = -1;
	static int	out = -1;
	static int	err = -1;
	int			lastmode = -1;

	if (mode == 1 && lastmode != 1)
	{
		in = dup(0);
		out = dup(1);
		err = dup(2);
	}
	if (mode == 0 && lastmode != 0)
	{
		dup2(in, 0);
		dup2(out, 1);
		dup2(err, 2);
		close(in);
		close(out);
		close(err);
		in = -1;
		out = -1;
		err = -1;
	}
}
