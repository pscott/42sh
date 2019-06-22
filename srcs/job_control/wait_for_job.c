#include "jobs.h"
#include "execution.h"


int		wait_for_job(t_job *j, int opt)
{
	int		status;
	pid_t	pid;

	if (!j)
		return (0);
	pid = waitpid(WAIT_ANY, &status, opt);
	while (!mark_process_status(pid, status)
			&& !job_is_stopped(j)
			&& !job_is_completed(j))
		pid = waitpid(WAIT_ANY, &status, opt);
	j->status = last_process_status(j->first_process);
	status = j->status;
	if (WIFSIGNALED(status)) // need function for proper error messages
	{
		if (j->fg && WTERMSIG(status) != SIGINT && WTERMSIG(status) != SIGPIPE)
			ft_dprintf(2, "process terminated, received signal : %d\n",
					WTERMSIG(status));
	}
	return (status);
}
