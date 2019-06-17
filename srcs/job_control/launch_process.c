#include "jobs.h"
#include "execution.h"
#include "signals.h"

int	launch_process(t_process *p, pid_t pgid, int fds[2], int foreground)
{
	pid_t pid;

	if (g_isatty)
	{
		pid = getpid();
		if (pgid == 0)
			pgid = pid;
		setpgid(pid, pgid);
		if (foreground)
			tcsetpgrp(TERM_FD, pgid);
		reset_signals();
	}
	clean_exit(parse_and_exec(p->token_list, fds[0], fds[1]), 0);
	return (0);
}
