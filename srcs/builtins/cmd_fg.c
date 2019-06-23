#include "jobs.h"
#include "signals.h"

int		case_fg(char **argv)
{
	t_job *j;

	(void)argv;//
	update_status();
	if (!(j = find_job_by_current('+')))
	{
		ft_dprintf(2, SHELL_NAME": fg: current: no such job\n");
		return (1); // error
	}
	if (job_is_completed(j))
	{
		ft_dprintf(2, SHELL_NAME ": fg: job has terminated\n");
		return (1);
	}
	ft_dprintf(2, "%s\n", j->command);
	put_job_in_foreground(j, 1);
	return (0);
}
