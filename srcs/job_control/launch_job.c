#include "execution.h"
#include "signals.h"
#include "jobs.h"

int		launch_job(t_job *j, int foreground)
{
	t_process	*p;
	pid_t		pid;
	int			mypipe[2];
	int			fds[2];

	fds[0] = j->stdin;
	p = j->first_process;
	while (p)
	{
		if (p->next)
		{
			if (pipe (mypipe) < 0)
			{
				ft_dprintf(2, "pipe failed\n");
				exit(1);
			}
			fds[1] = mypipe[1];
		}
		else
			fds[1] = j->stdout;
		pid = fork();
		if (pid == 0)
			launch_process(p, j->pgid, fds, foreground);
		else if (pid < 0)
		{
			ft_dprintf(2, "fork failed\n");
			exit(1);
		}
		else
		{
			p->pid = pid;
			if (g_isatty)
			{
				if (!j->pgid)
					j->pgid = pid;
				setpgid(pid, j->pgid);
			}
		}
		if (fds[0] != j->stdin)
			close(fds[0]);
		if (fds[1] != j->stdout)
			close(fds[1]);
		fds[0] = mypipe[0];
		p = p->next;
	}
	format_job_info(j, "launched");
	if (!g_isatty)
		wait_for_job(j);
	else if (foreground)
		put_job_in_foreground(j, 0);
	else
		put_job_in_background(j, 0);
	return (0);
}
