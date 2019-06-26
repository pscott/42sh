#include "jobs.h"
#include "input.h"
#include "execution.h"

char				*tokens_to_str(t_token *token, t_token_type delimiter)
{
	char	*res;

	res = NULL;
	while (token && token->type < delimiter)
	{
		if (token->type == tk_eat)
		{
			while (token && token->type == tk_eat)
				token = token->next;
			res = ft_strjoin_free_left(res, " ");
		}
		else
		{
			res = ft_strjoin_free_left(res, token->content);
			token = token->next;
		}
	}
	res = ft_strjoin_free_left(res, " ");
	return (res);
}

static void			display_long(t_job *j, const char *bg)
{
	t_process	*p;

	p = j->first_process;
	if (p->next)
		ft_dprintf(STDOUT_FILENO, "[%d]%c %d %-28s %s\n", j->num, j->current,
				j->pgid, get_exit_str(p->status), p->process_str);
	else
		ft_dprintf(STDOUT_FILENO, "[%d]%c %d %-28s %s%s\n", j->num, j->current,
				j->pgid, get_exit_str(p->status), p->process_str, bg);
	while ((p = p->next))
	{
		if (p->next)
			ft_dprintf(STDOUT_FILENO, "%9d %-28s %s%s\n", p->pid,
					get_exit_str(p->status), "| ", p->process_str);
		else
			ft_dprintf(STDOUT_FILENO, "%9d %-28s %s%s%s\n", p->pid,
					get_exit_str(p->status), "| ", p->process_str, bg);
	}
}

void				format_job_info(t_job *j, const char *state, const char *bg,
		t_job_opt opt)
{
	t_st_cmd	*st_cmd;
	t_process	*p;

	st_cmd = get_st_cmd(NULL);
	zsh_newline(st_cmd);
	if (opt == DEFAULT)
		ft_dprintf(STDOUT_FILENO, "[%d] %c %-28s %s%s\n", j->num, j->current,
				state, j->command, bg);
	else if (opt == PID)
	{
		p = j->first_process;
		while (p)
		{
			ft_dprintf(STDOUT_FILENO, "%d\n", p->pid);
			p = p->next;
		}
	}
	else if (opt == LONG)
		display_long(j, bg);
}
