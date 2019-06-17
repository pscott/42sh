#include "jobs.h"

void	format_job_info(t_job *j, const char *status)
{
	ft_dprintf(STDERR_FILENO, "%ld (%s): %s\n", (long)j->pgid, status, "hi"); // should be appended tokens in j;
}
