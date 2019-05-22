#include "heredoc.h"

/*
** get_eof
** parse tokens to concatenate the real EOF
** and check if it is quoted
*/

static unsigned char	get_eof(char **eof, t_token *probe)
{
	unsigned char	is_eof_quoted;

	is_eof_quoted = 0;
	while (probe->next && probe->next->type == tk_eat)
		probe = probe->next;
	probe = probe->next;
	while (probe && probe->type > tk_eat && probe->type < tk_redirection)
	{
		if (probe->type >= tk_monoc && probe->type <= tk_dq_str)
			is_eof_quoted = 1;
		*eof = eof_join(*eof, probe);
		//ft_printf("REFRESH EOF {%s}\n", *eof);
		//EAT
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

static char	*get_heredoc(char *eof, unsigned char is_eof_quoted, t_vars *vars)
{
	char		*path;
	char		*txt;
	char		*txt_tmp;
	t_st_cmd	*st_cmd;

	st_cmd = init_st_cmd((const char**)vars->env_vars);
	txt_tmp = ft_strdup("");
	while (ft_strncmp(eof, txt_tmp, ft_strlen(eof) + 1))
	{
		txt = concatenate_txt(st_cmd);
		input_loop(st_cmd, vars);
		ft_memdel((void*)&txt_tmp);
		txt_tmp = ft_strndup(st_cmd->st_txt->txt, ft_strlen(st_cmd->st_txt->txt) - 1);
		st_cmd = append_st_cmd(st_cmd, "", "heredoc> ");
	}
	//expand txt (depending on is_eof_quoted)// OR should i expand as i write()
	if (!is_eof_quoted)
	{/*
		-parameter expansion
		-command substitution
		-arithmetic expansion
		-the character sequence \newline is ignored
		-‘\’ must be used to quote the characters ‘\’, ‘$’, and ‘`’.
		*/
		//i can maybe tricks, by making a tk_dq_str, then passing the single token in parse expand ?
		//ft_printf("EOF is NOT quoted\n");
	}
	if (!(path = save_heredoc(txt)))
		return (NULL);
	ft_memdel((void*)&txt_tmp);
	ft_memdel((void*)&txt);
	free_st_cmd(st_cmd);
	return (path);
}

/*
** replace_heredoc_tokens
*/

static t_token	*replace_heredoc_tokens(t_token *probe, const char *path)
{
	//change '<<' to '<', still tk_redirection
	ft_strdel(&probe->content);
	if (!(probe->content = ft_strdup("<")))
		ERROR_MEM;
	probe->type = tk_redirection;
	//
	probe = probe->next;
	while (probe->type == tk_eat)
		probe = probe->next;
	probe->type = tk_word;//was tk_dq_str, should it be tk_heredoc_path or tk_q_str
	ft_strdel(&probe->content);
	if (!(probe->content = ft_strdup(path)))
		ERROR_MEM;
	probe = probe->next;
	while (probe && probe->type >= tk_word && probe->type <= tk_redirection)
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
			is_eof_quoted = get_eof(&eof, token_probe);
			//read and save
			path = get_heredoc(eof, is_eof_quoted, vars);//protect
			//replace tokens
			token_probe = replace_heredoc_tokens(token_probe, path);
			ft_strdel(&path);//test
			//continue
		}
		token_probe = token_probe->next;
	}
	return (1);//tmp
}
