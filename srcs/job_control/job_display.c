#include "jobs.h"
#include "input.h"
#include "execution.h"

char	*tokens_to_str(t_token *token, t_token_type delimiter)
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

void		format_job_info(t_job *j, const char *state, const char *bg, t_job_opt opt)
{
	t_st_cmd	*st_cmd;
	char		*pstatus;
	t_process	*p;

	st_cmd = get_st_cmd(NULL);
	zsh_newline(st_cmd);
	if (opt == DEFAULT)
		ft_dprintf(STDOUT_FILENO, "[%d] %c %-20s %s%s\n", j->num, j->current, state, j->command, bg);
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
	{
		p = j->first_process;
		if (p->stopped)
			pstatus = ft_strdup("Stopped");
		else if (p->completed)
			pstatus = ft_strdup("Done");
		else
			pstatus = ft_strdup("Running");
		if (!pstatus)
			clean_exit(1, 1);
		if (p->next)
			ft_dprintf(STDOUT_FILENO, "[%d]%c %d %-20s %s\n", j->num, j->current, j->pgid, pstatus, p->process_str);
		else
			ft_dprintf(STDOUT_FILENO, "[%d]%c %d %-20s %s%s\n", j->num, j->current, j->pgid, pstatus, p->process_str, bg);
		ft_strdel(&pstatus);
		while ((p = p->next))
		{
			if (p->stopped)
				pstatus = ft_strdup("Stopped");
			else if (p->completed)
				pstatus = ft_strdup("Done");
			else
				pstatus = ft_strdup("Running");
			if (p->next)
				ft_dprintf(STDOUT_FILENO, "%10d %-20s %s%s\n",  p->pid, pstatus, "| ", p->process_str);
			else
				ft_dprintf(STDOUT_FILENO, "%10d %-20s %s%s%s\n",  p->pid, pstatus, "| ", p->process_str, bg);
			ft_strdel(&pstatus);
		}
	}
}
