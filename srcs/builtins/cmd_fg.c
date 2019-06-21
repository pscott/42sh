#include "jobs.h"

int		case_fg(char **argv)
{
	t_job *j;

	(void)argv;//
	if (!(j = find_job_by_current('+')))
	{
		ft_dprintf(2, SHELL_NAME": fg: current: no such job\n");
		return (1); // error
	}
	ft_dprintf(2, "%s\n", j->command);
	put_job_in_foreground(j, 1);
	return (0);
}
