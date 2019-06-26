#include "execution.h"
#include "jobs.h"

static void	clean_fds_after_launch(int fds[2], int mypipe[2])
{
	if (fds[0] != STDIN_FILENO)
		close(fds[0]);
	if (fds[1] != STDOUT_FILENO)
		close(fds[1]);
	fds[0] = mypipe[0];
}

static void	set_stdout(t_process *p, int fds[2], int mypipe[2])
{
	if (p->next)
	{
		if (pipe(mypipe) < 0)
		{
			ft_dprintf(2, "pipe failed\n");
			clean_exit(1, NORESET);
		}
		fds[1] = mypipe[1];
	}
	else
		fds[1] = STDOUT_FILENO;
}

static void	parent_process(t_job *j, t_process *p, pid_t pid)
{
	p->pid = pid;
	if (g_isatty)
	{
		if (!j->pgid)
			j->pgid = pid;
		setpgid(pid, j->pgid);
	}
}

void		fork_and_launch_process(t_job *j, int fds[2], int mypipe[2], int fg)
{
	pid_t		pid;
	t_process	*p;

	p = j->first_process;
	while (p)
	{
		set_stdout(p, fds, mypipe);
		pid = fork();
		if (pid == 0)
		{
			if (fds[0] != mypipe[0])
				close(mypipe[0]);
			launch_process(p, j->pgid, fds, fg);
		}
		else if (pid < 0)
		{
			ft_dprintf(2, "fork failed\n");
			clean_exit(1, NORESET);
		}
		else
			parent_process(j, p, pid);
		clean_fds_after_launch(fds, mypipe);
		p = p->next;
	}
}
