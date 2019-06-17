#include "jobs.h"

void	launch_process(process *p, int fds[2], pid_t pgid, int foreground)
{
	pid_t pid;

	if (g_shell_is_interactive)
	{
		pid = getpid();
		if (pgid == 0)
			pgid = pid;
		setpgid(pid, pgid);
		if (foreground)
			tcsetpgrp(g_shell_terminal, pgid);
		reset_signals();
	}
	parse_and_exec(p->token_list, fds[0], fd[1]);
}
