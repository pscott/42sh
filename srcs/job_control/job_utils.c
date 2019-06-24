#include "jobs.h"

/*
**	Return true if all processes in the job have stopped.
*/

int		job_is_stopped(t_job *j)
{
	t_process *p;

	if (!j)
		return (0);
	p = j->first_process;
	if (!p)
		return (0);
	while (p)
	{
		if (!p->stopped)
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

	if (!j)
		return (1);
	p = j->first_process;
	while (p)
	{
		if (!p->completed)
			return (0);
		p = p->next;
	}
	return (1);
}
