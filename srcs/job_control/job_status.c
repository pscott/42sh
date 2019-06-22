#include "jobs.h"
#include "execution.h"

int	mark_process_status(pid_t pid, int status)
{
	t_job		*j;
	t_process	*p;

	if (!(j = g_first_job))
		return (1);
	if (pid > 0)
	{
		while (j)
		{
			p = j->first_process;
			while (p)
			{
				if (p->pid == pid)
				{
					p->status = status;
					if (WIFCONTINUED(status))
						p->stopped = 0;
					else if (WIFSTOPPED(status))
					{
						p->stopped = 1;
						j->fg = 0;
					}
					else
						p->completed = 1;
					return (0);
				}
				p = p->next;
			}
			j = j->next;
		}
	}
	return (-1);
}

int		last_process_status(t_process *p)
{
	if (!p)
		return (0);
	while (p->next)
		p = p->next;
	return (p->status);
}

void	update_status(void)
{
	int		status;
	t_job	*j;
	int		opt;
	pid_t	pid;

	opt = WUNTRACED | WNOHANG | WCONTINUED;
	pid = waitpid(WAIT_ANY, &status, opt);
	while (!mark_process_status(pid, status))
		pid = waitpid(WAIT_ANY, &status, opt);
	if (!(j = g_first_job))
		return ;
	status = last_process_status(j->first_process);
	j->status = last_process_status(j->first_process);
}
