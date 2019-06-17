#include "jobs.h"

void	do_job_notification(void)
{
	t_job		*j;
	t_job		*jlast;
	t_job		*jnext;
	t_process	*p;

	update_status();
	jlast = NULL;
	j = g_first_job;
	while (j)
	{
		jnext = j->next;
		if (job_is_completed(j))
		{
			format_job_info(j, "completed");
			if (jlast)
				jlast->next = jnext;
			else
				g_first_job = jnext;
			free_job(j);
		}
		else if (job_is_stopped(j) && !j->notified)
		{
			format_job_info(j, "stopped");
			j->notified = 1;
			jlast = j;
		}
		else
			jlast = j;
	}
}
