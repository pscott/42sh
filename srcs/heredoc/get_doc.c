#include "input.h"
#include "heredoc.h"
#include "history.h"
#include "cmd_parsing.h"

static void		apply_escape(t_st_cmd *st_cmd, int is_eof_quoted)
{
	int				i;
	unsigned char	is_real_escape;

	if (!is_eof_quoted)
	{
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
}

static char		*get_heredoc_txt(char *txt, char *eof, int ctrl_d)
{
	char	*trimed_txt;
	size_t	len;

	if (!ctrl_d)
		len = ft_strlen(txt) - ft_strlen(eof) - 2;
	else
		len = ft_strlen(txt);
	if (!(trimed_txt = ft_strndup(&txt[1], len)))
		clean_exit(1, MALLOC_ERR);
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

static void		init_get_doc(t_st_cmd **cmd, char **txt, t_st_cmd **heredoc)
{
	*cmd = get_last_st_cmd(get_st_cmd(NULL));
	*txt = NULL;
	*cmd = append_st_cmd(*cmd, "", init_st_prompt(HEREDOC_PROMPT, NULL, 0));
	*heredoc = *cmd;
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
	t_st_cmd	*cmd;
	int			ctrl_d;
	t_st_cmd	*start_heredoc;
	int			len;

	ctrl_d = 0;
	init_get_doc(&cmd, &txt, &start_heredoc);
	while (42)
	{
		if ((len = input_loop(cmd, vars, heredoc)) < 1)
		{
			if (*cmd->st_txt->txt != '\x03')
			{
				ctrl_d = 1;
				ft_dprintf(STDERR_FILENO, SHELL_NAME ": warning: here-document delimited by end-of-file (wanted `EOF')\n");
				txt = concatenate_heredoc_txt(cmd, start_heredoc);
				break ;
			}
			clean_heredoc(cmd, start_heredoc);
			return (free_get_doc(txt, eof));
		}
		apply_escape(cmd, is_eof_quoted);
		txt = concatenate_heredoc_txt(cmd, start_heredoc);
		len = ft_strlen(txt) - ft_strlen(eof) - 1;
		if (len > 0 && !ft_strncmp(&txt[len], eof, ft_strlen(eof))
				&& txt[len - 1] == '\n' && txt[ft_strlen(txt) - 1] == '\n')
			break ;
		ft_strdel(&txt);
		cmd = append_st_cmd(cmd, "", init_st_prompt(HEREDOC_PROMPT, NULL, 0));
	}
	txt = get_heredoc_txt(txt, eof, ctrl_d);
	clean_heredoc(cmd, start_heredoc);
	return (return_get_doc(txt, is_eof_quoted, vars));
}
