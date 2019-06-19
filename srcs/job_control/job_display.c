#include "jobs.h"

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
	if (!j->fg)
		ft_dprintf(STDOUT_FILENO, "[%d]%c %-20s %s%s\n", j->num, j->current, status, j->command, bg);
}
