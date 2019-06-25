#include "lexer.h"

/*
**	Does not change token_head->type to TK_WORD because we need to know the
**	orginal type for redirections.
*/

static int		expand_squotes(t_token *token_head)
{
	char		*old_content;

	if (*token_head->content == '\'' || *token_head->content == '"')
	{
		old_content = token_head->content;
		if (!(token_head->content =
				ft_strndup((const char*)&(*(token_head->content + 1)),
					ft_strlen(token_head->content) - 2)))
			clean_exit(1, 1);
		ft_strdel(&old_content);
		return (1);
	}
	return (0);
}

static int		is_valid_dquotes_escape(char c)
{
	if (c == '$' || c == '`' || c == '"' || c == '\\' || c == '\n')
		return (1);
	return (0);
}

static size_t	get_new_len(char *str, size_t old_len)
{
	size_t		i;
	size_t		res;

	i = 1;
	res = 0;
	while (i < old_len - 1)
	{
		if (str[i] == '\\' && is_valid_dquotes_escape(str[i + 1]))
			i++;
		i++;
		res++;
	}
	return (res);
}

static int		expand_dquotes(t_token *token_head)
{
	char		*new_str;
	size_t		old_len;
	size_t		new_len;
	size_t		i;
	size_t		j;

	old_len = ft_strlen(token_head->content);
	new_len = get_new_len(token_head->content, old_len);
	if (!(new_str = ft_strnew(new_len)))
		clean_exit(1, 1);
	i = 1;
	j = 0;
	while (i < new_len + 1)
	{
		if (token_head->content[i + j] == '\\'
			&& is_valid_dquotes_escape(token_head->content[i + j + 1]))
			j++;
		new_str[i - 1] = token_head->content[i + j];
		i++;
	}
	free(token_head->content);
	token_head->content = new_str;
	return (1);
}

int				parse_quotes(t_token *token_head)
{
	int		res;

	res = 0;
	while (token_head && token_head->type < tk_pipe)
	{
		if (token_head->type == tk_sq_str)
		{
			res = 1;
			expand_squotes(token_head);
		}
		else if (token_head->type == tk_dq_str)
		{
			res = 1;
			expand_dquotes(token_head);
		}
		token_head = token_head->next;
	}
	return (res);
}
