#include "jobs.h"
#include "input.h"

char	*tokens_to_str(t_token *token)
{
	char	*res;

	res = NULL;
	while (token)
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

void		format_job_info(t_job *j, const char *status, const char *bg)
{
	t_st_cmd	*st_cmd;

	st_cmd = get_st_cmd(NULL);
	zsh_newline(st_cmd);
	ft_dprintf(STDOUT_FILENO, "[%d]%c status: %d %-20s %s%s\n", j->num, j->current, exit_status(j->status), status, j->command, bg);
}
