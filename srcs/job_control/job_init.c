#include "jobs.h"
#include "signals.h"
#include <sys/types.h>

void	init_shell(void)
{
	g_first_job = NULL;
	g_isatty = isatty(STDIN_FILENO);
	g_can_exit = 0;
	if (g_isatty)
	{
		while (tcgetpgrp(STDIN_FILENO) != (g_shell_pgid = getpgrp()))
			kill(-g_shell_pgid, SIGTTIN);
		signals_setup();
		g_shell_pgid = getpid();
		if (setpgid(g_shell_pgid, g_shell_pgid) < 0)
		{
			ft_dprintf(2, "Couldn't put the shell in its own process group\n");
			exit(1);
		}
		tcsetpgrp(STDIN_FILENO, g_shell_pgid);
	}
	g_isatty = 0;
}
