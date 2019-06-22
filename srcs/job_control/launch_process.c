#include "jobs.h"
#include "execution.h"
#include "signals.h"

void	set_group_id(pid_t pgid, int foreground)
{
	pid_t pid;

	if (g_isatty)
	{
		pid = getpid();
		if (pgid == 0)
			pgid = pid;
		if (setpgid(pid, pgid) == -1)
			exit(1);
		if (foreground)
			tcsetpgrp(TERM_FD, pgid);
	}
}

int	launch_process(t_process *p, pid_t pgid, int fds[2], int foreground)
{
	set_group_id(pgid, foreground);
	reset_signals();
	exit(parse_and_exec(p->token_list, fds[0], fds[1]));
	return (1);
}
