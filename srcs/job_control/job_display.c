#include "jobs.h"

char	*tokens_to_str(t_token *tokens)
{
	char	*res;
	char	*tmp;

	res = NULL;
	while (tokens)
	{
		res = ft_strjoin_free_left(res, tokens->content); // protect ?
		tokens = tokens->next;
	}
	tmp = res;
	res = ft_strndup(res, ft_strlen(res) - 1); // protect
	ft_strdel(&tmp);
	return (res);
}

void		format_job_info(t_job *j, const char *status)
{
	if (!j->fg)
		ft_dprintf(STDERR_FILENO, "[%d]%c %s %s\n", j->num, j->current, status, tokens_to_str(j->token_list));
}
