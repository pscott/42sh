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

static void		init_get_doc(t_st_cmd *cmds[2], char **txt, int *ctrl_d)
{
	cmds[0] = get_last_st_cmd(get_st_cmd(NULL));
	*txt = NULL;
	cmds[0] = append_st_cmd(cmds[0], "", init_st_prompt(HRDC_PS, NULL, 0));
	cmds[1] = cmds[0];
	*ctrl_d = 0;
}

/*
** get_doc
** read the input from user until a line contain only 'eof' string
** write the input into a temporary file
** and return the path to it
** cmds[cmd, start_heredoc] 'because norm'
*/

char			*get_doc(char *eof, int is_eof_quoted, t_vars *vars)
{
	char		*txt;
	int			ctrl_d;
	int			len;
	t_st_cmd	*cmds[2];

	init_get_doc(cmds, &txt, &ctrl_d);
	while (42)
	{
		if ((len = input_loop(cmds[0], vars, heredoc)) < 1)
		{
			if (*cmds[0]->st_txt->txt != '\x03'
				&& get_doc_ctrl_d(&ctrl_d, eof, &txt, cmds))
				break ;
			return (free_get_doc(cmds, txt, eof));
		}
		apply_escape(cmds[0], is_eof_quoted);
		txt = concatenate_heredoc_txt(cmds[0], cmds[1]);
		if ((len = ft_strlen(txt) - ft_strlen(eof) - 1) && is_e(len, txt, eof))
			break ;
		ft_strdel(&txt);
		cmds[0] = append_st_cmd(cmds[0], "", init_st_prompt(HRDC_PS, NULL, 0));
	}
	txt = get_heredoc_txt(txt, eof, ctrl_d);
	clean_heredoc(cmds[0], cmds[1]);
	return (return_get_doc(txt, is_eof_quoted, vars));
}
