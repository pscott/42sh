#include "jobs.h"

void	do_job_notification(int verbose)
{
	t_job		*j;
	t_job		*jlast;
	t_job		*jnext;

	update_status();
	set_current();
	jlast = NULL;
	j = g_first_job;
	while (j)
	{
		jnext = j->next;
		if (job_is_completed(j))
		{
			if (j->notified == 0)
				format_job_info(j, "Done", "");
			if (jlast)
				jlast->next = jnext;
			else
				g_first_job = jnext;
			free_job(j);
		}
		else if (job_is_stopped(j) && !j->notified)
		{
			format_job_info(j, "Stopped", "");
			j->notified = 1;
			jlast = j;
		}
		else
		{
			if (verbose)
				format_job_info(j, "Running", "&");
			jlast = j;
		}
		j = jnext;
	}
}
