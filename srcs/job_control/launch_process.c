#include "jobs.h"
#include "execution.h"
#include "signals.h"

int	launch_process(t_process *p, pid_t pgid, int fds[2], int foreground)
{
	pid_t pid;

	if (g_shell_is_interactive)
	{
		pid = getpid();
		if (pgid == 0)
			pgid = pid;
		setpgid(pid, pgid);
		if (foreground)
			tcsetpgrp(TERM_FD, pgid);
		ft_dprintf(2, "resetting\n");
		reset_signals();
	}
	parse_and_exec(p->token_list, fds[0], fds[1]);
	return (0);
}
