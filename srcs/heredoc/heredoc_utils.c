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

/*
** get_heredoc_finename
** concatenate the default heredoc_filename with the given key
** and returned it
*/

static char	*get_heredoc_filename(unsigned int file_key)
{
	char			*path;
	char			*file_key_str;

	if (!(path = ft_strnew(ft_strlen(HEREDOC_FILENAME) + MAX_INT_LEN)))
		ERROR_MEM;
	ft_strcpy(path, HEREDOC_FILENAME);
	if (!(file_key_str = ft_itoa(file_key)))
		ERROR_MEM;
	ft_strcpy(&path[ft_strlen(HEREDOC_FILENAME)], file_key_str);
	ft_memdel((void*)&file_key_str);
	return (path);
}

/*
** find_unique_filename
** find an unused filename
** and returned it
*/

char	*find_uniq_filename(void)
{
	char			*path;
	unsigned int	file_key;

	file_key = 0;
	path = get_heredoc_filename(file_key);
	while (access(path, F_OK) == 0)//pas sure
	{
		ft_strdel(&path);
		if (file_key == UINT_MAX)
		{
			ft_dprintf(2, "tmp: can't create heredoc temporary file(max UINT)\n");
			return (NULL);
		}
		file_key++;
		path = get_heredoc_filename(file_key);
	}
	return (path);
}
