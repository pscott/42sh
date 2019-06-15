#include "jobs.h"

/*
**	Find the active job with the indicated pgid.
*/
t_job 	*find_job(pid_t pgid)
{
	t_job *j;

	j = g_first_job;
	while (j)
	{
		if (j->pgid == pgid)
			return (j);
		j = j->next;
	}
	return (NULL);
}

/*
**	Return true if all processes in the job have stopped or completed.
*/

int 	job_is_stopped(t_job *j)
{
	t_process *p;

	p = j->first_process;
	while (p)
	{
		if (!p->completed && !p->stopped)
			return (0);
		p = p->next;
	}
	return (1);
}

/*
**	Return true if all processes in the job have completed.
*/

int		job_is_completed(t_job *j)
{
	t_process *p;

	p = j->first_process;
	while (p)
	{
		if (!p->completed)
			return (0);
		p = p->next;
	}
	return (1);
}
