#include "jobs.h"
#include <signal.h>

void	put_last_job_in_background(void)
{
	t_job *j;

	j = g_first_job;
	while (j)
	{
		if (j->current == '+')
			put_job_in_background(j, 0);
		j = j->next;
	}
}

void	put_job_in_background(t_job *j, int cont)
{
	if (cont)
	{
		if (kill(-j->pgid, SIGCONT) < 0)
			ft_dprintf(2, SHELL_NAME ": error with sending continue signal\n");
	}
	j->fg = 0;
	wait_for_job(j); // ctrl + z ?
}
