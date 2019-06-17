#include "jobs.h"
#include <signals.h>

void	put_job_in_foreground(t_job *j, int cont)
{
	tcsetpgrp(TERM_FD, j->pgid);
	if (cont)
	{
		tcsetattr(TERM_FD, TCSADRAIN, &j->tmodes);
		if (kill(-j->pgid, SIGCONT) < 0)
			ft_dprintf(2, SHELL_NAME ": error with sending continue signal\n");
	}
	wait_for_job(j);
	signals_setup();
	tcsetpgrp(TERM_FD, g_shell_pgid);
	tcgetattr(TERM_FD, &j->tmodes);
//	tcsetattr(TERM_FD, TCSADRAIN, &g_saved_attr);
}
