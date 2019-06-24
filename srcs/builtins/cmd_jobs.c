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

static int	get_options(char **argv, int *i)
{
	int	j;
	int	opt;

	opt = DEFAULT;
	while (argv[*i])
	{
		j = 0;
		if (argv[*i][j] == '-')
		{
			j++;
			if (argv[*i][j] == '-')
				return (opt);
			else if (!argv[*i][j])
				return (opt);
			while (argv[*i][j])
			{
				if (argv[*i][j] == 'p')
					opt = PID;
				else if (argv[*i][j] == 'l')
					opt = LONG;
				else if (argv[*i][j] == 0)
					break;
				else
					return (ERROR);
				j++;
			}
		}
		else
			return (opt);
		(*i)++;
	}
	return (opt);
}

int		case_jobs(char **argv)
{
	t_job		*to_print;
	t_job_opt	opt;
	int			i;

	if (!g_isatty)
		return (0);
	reset_notif();
	i = 1;
	opt = get_options(argv, &i);
	if (opt == ERROR)
	{
		ft_dprintf(2, "jobs: usage: jobs [-l | -p] [job_id...]\n");
		return (1);
	}
	if (!argv[i])
	{
		do_job_notification(1, opt);
		return (0);
	}
	else
	{
		while (argv[i])
		{
			to_print = get_job(argv[i], "jobs");
			if (print_job_status(to_print, 1, DEFAULT))
				free_job_from_list(to_print);
			i++;
		}
	}
	return (to_print ? 0 : 1);
}
