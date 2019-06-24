#include "lexer.h"
#include "signals.h"
#include "execution.h"
#include "cmd_parsing.h"
#include "jobs.h"

static pid_t	get_last_pid(t_job *j)
{
	t_process	*p;
	pid_t		res;
	
	if (!j)
		return (-1);
	p = j->first_process;
	while (p)
	{
		res = p->pid;
		p = p->next;
	}
	return (res);
}

int				parse_cmdline(t_ast *root, t_vars *vars, int fg)
{
	int			num_processes;
	t_token		*token;
	t_job		*j;
	t_process	*p;
	int			ret;

	if (!(token = root->token))
		return (0);
	p = create_process_list(token);
	num_processes = get_processes_len(p);
	if ((num_processes == 1 && fg)
			&& ((ret = check_no_pipe_builtin(token, vars)) >= 0 || ret == -2))
	{
		free_process_list(p);
		return (ret);
	}
	g_can_exit = 0;
	if (fg)
		j = append_job(&g_first_job, create_job(root, fg, get_last_num(g_first_job) + 1));
	else
	{
		j = g_first_job;
		while (j && j->next)
			j = j->next;
	}
	j->first_process = p;
	ret = launch_job(j, fg);
	if (g_isatty && !fg && !j->forked)
	{
		ft_dprintf(STDERR_FILENO, "[%d] %d\n", j->num, get_last_pid(j));
		j->bg = 1;
	}
	if (j->forked)
	{
		free_process_list(p);
		j->first_process = NULL;
	}
	vars->cmd_value = ret;
	return (ret);
}
