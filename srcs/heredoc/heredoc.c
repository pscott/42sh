#include "heredoc.h"

/*
** get_eof
** parse tokens to concatenate the real EOF
** and check if it is quoted
** return 2 if no eof is found
*/

//TODO check this function
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
		return (2);
	}
	while (probe && probe->type > tk_eat && probe->type < tk_redirection)
	{
		if (probe->type >= tk_monoc && probe->type <= tk_dq_str)
			is_eof_quoted = 1;
		*eof = eof_join(*eof, probe);
		probe = probe->next;
	}
	return(is_eof_quoted);
}

/*
** save_heredoc
** find a unique file name
** write the input into the new file
** return the path to it
*/

static char	*save_heredoc(const char *txt)
{
	char	*path;
	int		fd;

	if (!(path = find_uniq_filename()))//protect better
	{
		ft_dprintf(2, "tmp(heredoc): can't create unique temporary filename\n");
		return (NULL);//check this return
	}
	if ((fd = open(path, O_CREAT | O_RDWR | O_APPEND, 0666)) == -1)
	{
		ft_dprintf(2, "tmp: open error\n");
		return (NULL);//error
	}
	if (write(fd, txt, ft_strlen(txt)) == -1)
	{
		ft_dprintf(2, "tmp: write error\n");
	}
	close(fd);
	return (path);//free
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

static char	*get_doc(char *eof, unsigned char is_eof_quoted, t_vars *vars)
{
	char		*path;
	char		*txt;
	t_st_cmd	*st_cmd;
	int			len;

	st_cmd = init_st_cmd((const char **)vars->env_vars);
	if (!(st_cmd->st_txt->txt = ft_strdup("\n")))//TODO lookup insert_str
		ERROR_MEM;
	st_cmd = append_st_cmd(st_cmd, "", "heredoc> ");
	txt = NULL;
	while (42)
	{
		input_loop(st_cmd, vars);
		if (!is_eof_quoted)
			apply_escape(st_cmd);
		txt = concatenate_txt(st_cmd);//need free ?
		len = ft_strlen(txt) - ft_strlen(eof) - 1;
		if (len > 0 && !ft_strncmp(&txt[len], eof, ft_strlen(eof))
			&& txt[len - 1] == '\n' && txt[ft_strlen(txt) - 1] == '\n')
			break ;
		st_cmd = append_st_cmd(st_cmd, "", "heredoc> ");
	}
	path = txt;
	if (!(txt = ft_strndup(&txt[1], len - 1)))
		ERROR_MEM;
	ft_strdel(&path);
	if (!is_eof_quoted)
	{
		if (!parse_dollars_str(&txt, vars))
			ft_printf("TMP: parse_dollars_str in heredoc FAILED\n");
	}
	if (!(path = save_heredoc(txt)))
		return (NULL);
	ft_memdel((void*)&txt);
	free_st_cmd(st_cmd);//does it free only one ?
	return (path);
}

/*
** replace_heredoc_tokens
*/

static t_token	*replace_heredoc_tokens(t_token *probe, const char *path)
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
		//ft_strdel(&probe->content);//pas sure
		//probe->content = ft_strdup("");//pas sure non plus, depend des prochain free
		probe = probe->next;
	}
	return (probe);
}

/*
** parse_heredoc
** parse the entire token list, if it find an 'heredoc'
** - it get 'EOF' word and check if it was quoted
** - write the content of heredoc into a unique file
** - replace << by <, first 'EOF' token by new file name (and tk_eat if multi)
**		and type the rest of 'EOF' tokens to tk_eat
*/

t_bool	parse_heredoc(t_token *token_head, t_vars *vars)
{
	t_token			*token_probe;
	char			*eof;
	unsigned char	is_eof_quoted;
	char			*path;

	token_probe = token_head;
	while (token_probe)
	{
		if (token_probe->type == tk_heredoc)
		{
			eof = NULL;
			if ((is_eof_quoted = get_eof(&eof, token_probe)) == 2)
				return (0);//check me
			//read and save
			if (!(path = get_doc(eof, is_eof_quoted, vars)))
				return (0);//check me
			//replace tokens
			token_probe = replace_heredoc_tokens(token_probe, path);
			//print_line(1);
			ft_strdel(&path);
			continue ;
		}
		token_probe = token_probe->next;
	}
	return (1);//tmp
}
