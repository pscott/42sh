#include "jobs.h"

static void	go_to_background(t_job *j)
{
	if (job_is_completed(j))
		ft_dprintf(2, SHELL_NAME ": bg: job has terminated\n");
	else if (j && j->fg == 0)
		ft_dprintf(2, SHELL_NAME ": bg: job %d already in background\n", j->num);
	else
	{
		put_job_in_background(j, 1);
		ft_dprintf(STDERR_FILENO, "[%d]%c %s&\n",
				j->num, j->current, j->command);
	}
}

int			case_bg(char **argv)
{
	t_job	*j;
	int		i;

	if (!g_isatty)
		return (0);
	update_status();
	if (!argv[1])
	{
		j = get_job("%+", "bg");
		go_to_background(j);
	}
	else
	{
		i = 1;
		while (argv[i])
		{
			j = get_job(argv[i], "bg");
			go_to_background(j);
			i++;
		}
	}
	return (0);
}
