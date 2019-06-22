#include "jobs.h"
#include "execution.h"
#include <signal.h>

int		special_wait(t_job *j, int opt)
{
	int		status;
	pid_t	pid;

	if (!j)
		return (0);
	pid = waitpid(WAIT_MYPGRP, &status, opt);
	ft_dprintf(2, "rep: %d\n", pid);
	if (WIFCONTINUED(status))
	{
		ft_dprintf(2, "Killing cont\n");
		kill(getpid(), SIGCONT);
	}
	if (WIFSTOPPED(status))
	{
		ft_dprintf(2, "killing STOP\n");
		kill(getpid(), WSTOPSIG(status));
	}
	ft_dprintf(2, "killed\n");
	while (!mark_process_status(pid, status)
			&& !job_is_stopped(j)
			&& !job_is_completed(j))
	{
		if (WIFCONTINUED(status))
			kill(getpid(), SIGCONT);
		if (WIFSTOPPED(status))
			kill(getpid(), WSTOPSIG(status));
		pid = waitpid(WAIT_ANY, &status, opt);
	}
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
