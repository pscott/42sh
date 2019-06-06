#include "input.h"
#include "heredoc.h"
#include "cmd_parsing.h"

static void		apply_escape(t_st_cmd *st_cmd)
{
	int				i;
	unsigned char	is_real_escape;

	i = ft_strlen(st_cmd->st_txt->txt) - 1;
	is_real_escape = 0;
	while (--i >= 0 && st_cmd->st_txt->txt[i] == '\\')
	{
		if (st_cmd->st_txt->txt[i] == '\\')
			is_real_escape = (is_real_escape) ? 0 : 1;
	}
	if (is_real_escape)
	{
		st_cmd->st_txt->txt[st_cmd->st_txt->data_size - 1] = 0;
		st_cmd->st_txt->txt[st_cmd->st_txt->data_size - 2] = 0;
		st_cmd->st_txt->data_size -= 2;
	}
}

static t_st_cmd	*init_get_doc(char **txt, t_vars *vars)
{
	t_st_cmd *st_cmd;

	st_cmd = init_st_cmd((const char **)vars->env_vars);
	ft_strdel(&st_cmd->st_txt->txt);
	if (!(st_cmd->st_txt->txt = ft_strdup("\n")))
		clean_exit(1, 1);
	st_cmd = append_st_cmd(st_cmd, "", "heredoc> ");
	*txt = NULL;
	return (st_cmd);
}

static char		*get_heredoc_txt(t_st_cmd **st_cmd, char *txt, char *eof)
{
	char	*trimed_txt;
	size_t	len;

	free_all_st_cmds(st_cmd);
	len = ft_strlen(txt) - ft_strlen(eof) - 2;
	if (!(trimed_txt = ft_strndup(&txt[1], len)))
		clean_exit(1, 1);
	ft_strdel(&txt);
	ft_strdel(&eof);
	return (trimed_txt);
}

static char		*return_get_doc(char *txt, unsigned char is_eof_quoted,
			t_vars *vars)
{
	char	*path;

	if (!is_eof_quoted && (parse_dollars_str(&txt, vars) > 0))
	{
		ft_strdel(&txt);
		return (NULL);
	}
	if (!(path = write_heredoc_in_file(&txt)))
		return (NULL);
	return (path);
}

/*
** get_doc
** read the input from user until a line contain only 'eof' string
** write the input into a temporary file
** and return the path to it
*/

char			*get_doc(char *eof, unsigned char is_eof_quoted, t_vars *vars)
{
	char		*txt;
	t_st_cmd	*st_cmd;
	int			len;
	int			ret;

	st_cmd = init_get_doc(&txt, vars);
	while (42)
	{
		if ((ret = input_loop(st_cmd, vars, heredoc)) < 1
			|| !*st_cmd->st_txt->txt)
			return (free_get_doc(txt, st_cmd, eof));
		if (!is_eof_quoted)
			apply_escape(st_cmd);
		txt = concatenate_txt(st_cmd);
		len = ft_strlen(txt) - ft_strlen(eof) - 1;
		if (len > 0 && !ft_strncmp(&txt[len], eof, ft_strlen(eof))
			&& txt[len - 1] == '\n' && txt[ft_strlen(txt) - 1] == '\n')
			break ;
		st_cmd = append_st_cmd(st_cmd, "", "heredoc> ");
		ft_strdel(&txt);
	}
	txt = get_heredoc_txt(&st_cmd, txt, eof);
	return (return_get_doc(txt, is_eof_quoted, vars));
}
