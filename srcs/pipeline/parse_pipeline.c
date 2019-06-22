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
/*
**	Returns the next simple_command (the one after the next pipe), if there
**	is one.
**	Should not return NULL because it is called n - 1 times
*/

t_token	*get_next_simple_command(t_token *begin)
{
	while (is_simple_cmd_token(begin))
		begin = begin->next;
	if (begin && begin->type == tk_pipe)
		return (begin->next);
	else
		return (begin);
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
		while (j && j->next) // job has been created by `&` previous fork
			j = j->next;
	}
	j->first_process = p;
	ret = launch_job(j, fg);
	if (!fg && !j->forked)
		ft_dprintf(STDERR_FILENO, "[%d] %d\n", j->num, get_last_pid(j));
	vars->cmd_value = ret;
	return (ret);
}
