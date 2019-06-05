#include "heredoc.h"

/*
** get_eof
** parse tokens to concatenate the real EOF
** and check if it is quoted
** return ERR_PARSE_EOF if no eof is found
*/

static unsigned char	get_eof(char **eof, t_token *probe)
{
	unsigned char	is_eof_quoted;

	is_eof_quoted = 0;
	while (probe->next && probe->next->type == tk_eat)
		probe = probe->next;
	if (probe->next)
		probe = probe->next;
	if (!probe || probe->type >= tk_redirection || probe->type == tk_eat)
	{
		syntax_error_near(probe);
		return (ERR_PARSE_EOF);
	}
	while (probe && probe->type > tk_eat && probe->type < tk_redirection)
	{
		if (probe->type >= tk_monoc && probe->type <= tk_dq_str)
			is_eof_quoted = 1;
		*eof = eof_join(*eof, probe);
		probe = probe->next;
	}
	return (is_eof_quoted);
}

static t_token			*replace_heredoc_tokens(t_token *probe,
						const char *path)
{
	ft_strdel(&probe->content);
	if (!(probe->content = ft_strdup("<")))
		ERROR_MEM;
	probe->type = tk_redirection;
	probe = probe->next;
	while (probe->type == tk_eat)
		probe = probe->next;
	probe->type = tk_word;
	ft_strdel(&probe->content);
	if (!(probe->content = ft_strdup(path)))
		ERROR_MEM;
	probe = probe->next;
	while (probe && probe->type >= tk_word && probe->type < tk_redirection)
	{
		probe->type = tk_eat;
		probe = probe->next;
	}
	return (probe);
}

/*
** parse_heredoc
** parse the entire token list, if it find an 'heredoc' token
** - it get 'EOF' word and check if it was quoted
** - write the content of heredoc into a unique file
** - replace << by <, and the EOF tokens by the name of the temporary file
*/

int						parse_heredoc(t_token *token_head, t_vars *vars)
{
	t_token			*token_probe;
	char			*eof;
	int			is_eof_quoted;
	char			*path;

	token_probe = token_head;
	while (token_probe)
	{
		if (token_probe->type == tk_heredoc)
		{
			eof = NULL;
			if ((is_eof_quoted = get_eof(&eof, token_probe)) == ERR_PARSE_EOF)
				return (0);
			if (!(path = get_doc(eof, is_eof_quoted, vars)))
				return (0);
			token_probe = replace_heredoc_tokens(token_probe, path);
			ft_strdel(&path);
			continue ;
		}
		token_probe = token_probe->next;
	}
	return (1);
}
