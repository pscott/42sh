#include "jobs.h"
#include <signal.h>

int		put_job_in_background(t_job *j, int cont)
{
	t_process *p;

	if (!j)
		return (1);
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
	return (0);
}
