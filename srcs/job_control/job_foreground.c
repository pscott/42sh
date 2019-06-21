#include "jobs.h"
#include <signals.h>

int		put_job_in_foreground(t_job *j, int cont)
{
	int	ret;

	tcsetpgrp(TERM_FD, j->pgid);
	if (cont)
	{
		tcsetattr(TERM_FD, TCSADRAIN, &j->tmodes);
		if (kill(-j->pgid, SIGCONT) < 0)
			ft_dprintf(2, SHELL_NAME ": error with sending continue signal\n");
	}
	j->fg = 1;
	ret = wait_for_job(j);
	tcsetpgrp(TERM_FD, g_shell_pgid);
	tcgetattr(TERM_FD, &j->tmodes);
	return (ret);
}
