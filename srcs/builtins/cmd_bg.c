#include "jobs.h"

int		case_bg(char **argv)
{
	t_job *j;

	(void)argv;//
	update_status();
	if (!(j = find_job_by_current('+')))
	{
		ft_dprintf(2, SHELL_NAME": bg: current: no such job\n");
		return (1);
	}
	if (job_is_completed(j))
	{
		ft_dprintf(2, SHELL_NAME ": bg: job has terminated\n");
		return (1);
	}
	if (put_job_in_background(j, 1))
		return (1);
	ft_dprintf(STDERR_FILENO, "[%d]%c %s&\n", j->num, j->current, j->command);
	return (0);
}
