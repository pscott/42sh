#include "ftsh.h"
#include "history.h"
#include "input.h"
#include "jobs.h"

static int	check_for_stopped_jobs(void)
{
	t_job *j;

	j = g_first_job;
	while (j)
	{
		if (job_is_stopped(j))
			return (1);
		j = j->next;
	}
	return (0);
}

/*
** Utility function to reset the terminal settings and exit
*/

void		clean_exit(int exitno, t_exit reason)
{
	t_st_cmd	*st_cmd;
	t_vars		*vars;

	if (reason != MALLOC_ERR)
	{
		if (reason != FORCE && !g_can_exit && check_for_stopped_jobs())
		{
			ft_dprintf(2, "There are stopped jobs\n");
			g_can_exit = 1;
			return ;
		}
		st_cmd = get_st_cmd(NULL);
		vars = get_vars(NULL);
		write_to_history(st_cmd, (const char **)vars->env_vars);
		free_all_st_cmds(&st_cmd);
		free_job_list(g_first_job);
		free_vars(vars);
	}
	else
		write(2, "\nexiting: malloc error\n", 23);
	if (reason != NORESET)
		reset_terminal_settings();
	exit(exitno);
}
