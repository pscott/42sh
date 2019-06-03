#include "heredoc.h"

static char	*remove_quot(char *str)
{
	char			*new;
	unsigned int	str_len;

	str_len = ft_strlen(str);
	if (!(new = ft_strnew(str_len - 2)))
		ERROR_MEM;
	ft_strncpy(new, &str[1], str_len - 2);
	return (new);
}

static char	*strjoin_free(char *str_join, char *str_add)
{
	char	*tmp_str;

	//if 1NULL or 2NULL
	if (!(tmp_str = ft_strjoin(str_join, str_add)))
		ERROR_MEM;
	ft_strdel(&str_join);
	//ft_strdel(&str_add);//don't want to free token->content now
	return (tmp_str);
}

//check expand order ?
char	*eof_join(char *eof, t_token *token)
{
	char	*tmp_str;

	if (!eof)
	{
		if (token->type == tk_word || token->type == tk_monoc)
		{
			if (!(eof = ft_strdup(token->content)))
				ERROR_MEM;
		}
		else if (token->type == tk_sq_str || token->type == tk_dq_str)
		{
			if (!(tmp_str = remove_quot(token->content)))
				ERROR_MEM;
			if (!(eof = ft_strdup(tmp_str)))
				ERROR_MEM;
			ft_strdel(&tmp_str);
		}
	}
	else
	{
		if (token->type == tk_word || token->type == tk_monoc)
			eof = strjoin_free(eof, token->content);
		else if (token->type == tk_sq_str || token->type == tk_dq_str)
		{
			if (!(tmp_str = remove_quot(token->content)))
				ERROR_MEM;
			eof = strjoin_free(eof, tmp_str);
			ft_strdel(&tmp_str);
		}
	}
	return (eof);
}
