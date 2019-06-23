#include "jobs.h"

static void reset_notif(void)
{
	t_job		*j;
	t_process	*p;

	j = g_first_job;
	while (j)
	{
		p = j->first_process;
		j->notified = 0;
		j = j->next;
	}
}

int		case_jobs(char **argv)
{
	t_job	*to_print;
	int		i;

	reset_notif();
	if (!argv[1])
	{
		do_job_notification(1);
		return (0);
	}
	else
	{
		i = 1;
		while (argv[i])
		{
			to_print = get_job(argv[i], "jobs");
			if (print_job_status(to_print, 1))
				free_job_from_list(to_print);
			i++;
		}
	}
	return (to_print ? 0 : 1);
}
