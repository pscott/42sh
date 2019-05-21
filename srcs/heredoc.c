#include "42sh.h"
#include "lexer.h"
#include "input.h"

#define	HEREDOC_FILENAME "/tmp/.tmp_heredoc"
#define	MAX_INT_LEN 10
#define UINT_MAX 4294967295


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

static char	*eof_join(char *eof, t_token *token)
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
** find_unia_filename
** find an unused filename
** and returned it
*/

static char	*find_uniq_filename(void)
{
	char			*path;
	unsigned int	file_key;

	file_key = 0;
	path = get_heredoc_filename(file_key);
	while (access(path, F_OK) == 0)//pas sure
	{
		ft_memdel((void*)&path);
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
		ft_dprintf(2, "tmp: write error\n");
	close(fd);
	return (path);//free
}

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
	//expand txt (depending on is_eof_quoted)
	if (!is_eof_quoted)
	{/*
		-parameter expansion
		-command substitution
		-arithmetic expansion
		-the character sequence \newline is ignored
		-‘\’ must be used to quote the characters ‘\’, ‘$’, and ‘`’.
		*/
		//i can maybe tricks, by making a tk_dq_str, then passing the single token in parse expand ?
		//ft_printf("EOF is NOT quoted");
		//print_line();
	}
	if (!(path = save_heredoc(txt)))
		return (NULL);
	ft_memdel((void*)&txt_tmp);
	ft_memdel((void*)&txt);
	free_st_cmd(st_cmd);
	return (path);
}

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
			//continue
		}
		token_probe = token_probe->next;
	}
	return (1);//tmp
}
