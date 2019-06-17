#include "jobs.h"

void	put_job_in_background(t_job *j, int cont)
{
	if (cont)
	{
		if (kill(-j->jpgid, SIGCONT) < 0)
			ft_dprintf(2, SHELL_NAME :" error with sending continue signal\n");
	}
}
