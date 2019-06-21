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
	t_process *p;

	if (cont)
	{
		if (kill(-j->pgid, SIGCONT) < 0)
			ft_dprintf(2, SHELL_NAME ": error with sending continue signal\n");
	}
	p = j->first_process;
	while (p)
	{
		p->stopped = 0;
		p = p->next;
	}
	j->fg = 0;
	j->bg = 1;
}
