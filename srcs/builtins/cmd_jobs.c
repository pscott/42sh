#include "jobs.h"

static void reset_notif(void)
{
	t_job *j;

	j = g_first_job;
	while (j)
	{
		j->notified = 0;
		j = j->next;
	}
}

int		case_jobs(char **argv)
{
	(void)argv;
	reset_notif();
	do_job_notification(1);
	return (0);
}
