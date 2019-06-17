#include "jobs.h"

void	format_job_info(job *j, const char *status)
{
	ft_dprintf(STDERR_FILENO, "%ld (%s): %s\n", (long)j->pgid, status, j->command);
}
