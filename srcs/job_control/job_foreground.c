#include "jobs.h"
#include <signals.h>
#include <stdio.h>
#include <errno.h>

static void	put_error(char *str)
{
	ft_dprintf(2, SHELL_NAME " : %s\n", str);
}

int		put_job_in_foreground(t_job *j, int cont)
{
	int			ret;
	t_process	*p;

	if (tcsetpgrp(STDIN_FILENO, j->pgid))
		put_error("error giving terminal control to job");
	if (cont)
	{
		if (tcsetattr(STDIN_FILENO, TCSADRAIN, &j->tmodes))
			put_error("error setting job's terminal attributes");
		if (kill(-j->pgid, SIGCONT) < 0)
			put_error("error with sending continue signal");
	}
	p = j->first_process;
	while (p)
	{
		p->stopped = 0;
		p = p->next;
	}
	j->notified = 0;
	j->fg = 1;
	j->bg = 0;
	ret = wait_for_job(j, WUNTRACED);
	if (tcsetpgrp(STDIN_FILENO, g_shell_pgid))
		put_error("error giving terminal control to 42sh");
	if (tcgetattr(STDIN_FILENO, &j->tmodes))
		put_error("error retrieving terminal job's terminal attributes");
	if (tcsetattr(STDIN_FILENO, TCSADRAIN, &g_42sh_attr))
		put_error("error setting 42sh's terminal attributes");
	return (ret);
}
