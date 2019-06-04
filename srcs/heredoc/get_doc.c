#include "heredoc.h"

/*
** save_heredoc
** find a unique file name
** write the input into the new file
** return the path to it
*/

static char	*save_heredoc(char **txt)
{
	char	*path;
	int		fd;

	if (!(path = find_uniq_filename()))//protect better
		return (NULL);
	if ((fd = open(path, O_CREAT | O_RDWR | O_APPEND, 0666)) == -1)
	{
		ft_dprintf(2, "%s: an open() error occurs\n", SHELL_NAME);
		return (NULL);
	}
	if (write(fd, *txt, ft_strlen(*txt)) == -1)
		ft_dprintf(2, "%s: heredoc write error\n", SHELL_NAME);
	close(fd);
	ft_strdel(txt);
	return (path);
}

/*
** get_heredoc
** read input from user
** concatenate the input
** TODO expand the input if EOF isn't quoted
** save it into a file and return the path to it
*/

//static t_bool	is_last_line_escaped(char *str)
static void	apply_escape(t_st_cmd *st_cmd)
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

//double use of path and len for the norm...
char		*get_doc(char *eof, unsigned char is_eof_quoted, t_vars *vars)
{
	char		*path;
	char		*txt;
	t_st_cmd	*st_cmd;
	int			len;

	st_cmd = init_st_cmd((const char **)vars->env_vars);
	ft_strdel(&st_cmd->st_txt->txt);
	if (!(st_cmd->st_txt->txt = ft_strdup("\n")))//TODO lookup insert_str
		ERROR_MEM;
	st_cmd = append_st_cmd(st_cmd, "", "heredoc> ");
	txt = NULL;
	while (42)
	{
		if ((len = input_loop(st_cmd, vars, heredoc)) < 1 || !*st_cmd->st_txt->txt)
		{
			ft_strdel(&txt);
			free_all_st_cmds(&st_cmd);
			ft_strdel(&eof);
			return (NULL);
		}
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
	free_all_st_cmds(&st_cmd);
	path = txt;
	if (!(txt = ft_strndup(&txt[1], len - 1)))
		ERROR_MEM;
	ft_strdel(&path);
	ft_strdel(&eof);
	if (!is_eof_quoted && !parse_dollars_str(&txt, vars))
	{
		ft_strdel(&txt);
		return (NULL);
	}
	if (!(path = save_heredoc(&txt)))
		return (NULL);
	return (path);
}
