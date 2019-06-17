#include "jobs.h"

void	wait_for_job(t_job *j)
{
	int		status;
	pid_t	pid;

	pid = waitpid(WAIT_ANY, &status, WUNTRACED);
	while (!mark_process_status(pid, status)
		&& !job_is_stopped(j)
		&& !job_is_completed(j))
		pid = waitpid(WAIT_ANY, &status, WUNTRACED);
}
