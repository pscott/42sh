#include "42sh.h"
#include "lexer.h"
#include "input.h"

static char	*add_quot(char *str)
{
	char	*new;
	unsigned int old_len;

	old_len = ft_strlen(str) + 2;
	if (!(new = ft_strnew(old_len)))
		ERROR_MEM;
	new[0] = '"';
	ft_strcpy(&new[1], str);
	new[old_len + 1] = '"';
	return (new);
}

///////////////////////////////////////////////////////////////////////////////
//-read and save input in a file
//	check if default filename exist ('/tmp/tmp_heredoc0000'):
//		if not: create it
//		else: increment number at the end of filename
//-replace '<<' by '<'
//-replace 'EOF' by 'path to file'

//later, at exec:
//rm all used file

#define	HEREDOC_FILENAME "/tmp/.tmp_heredoc"
#define	MAX_INT_LEN 10

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

static char	*get_uniq_filename(void)
{
	char			*path;
	unsigned int	file_key;

	file_key = 0;//protect max value
	path = get_heredoc_filename(file_key);
	while (access(path, F_OK) == 0)//pas sure
	{
		ft_memdel((void*)&path);
		file_key++;
		path = get_heredoc_filename(file_key);
	}
	return (path);
}

char	*heredoc(const char *txt)
{
	char	*path;
	int		fd;

	path = get_uniq_filename();
	ft_printf("UNIQ: {%s}\n", path);
	if ((fd = open(path, O_CREAT | O_RDWR | O_APPEND, 0666)) == -1)
	{
		ft_dprintf(2, "tmp: open error\n");
		return (NULL);//error
	}
	ft_printf("NEW FD: %d\n", fd);
	if (write(fd, txt, ft_strlen(txt)) == -1)
		ft_dprintf(2, "tmp: write error\n");
	return (path);//free
}
///////////////////////////////////////////////////////////////////////////////

//i need to write the content of heredoc in a file, then replace EOF with the path of the file
t_bool	save_heredoc(t_token **prev_token, t_token **current_token, t_vars *vars)
{
	static int	heredoc_count = 0;
	//int			fd;
	char		*txt;
	char		*txt_tmp;
	t_st_cmd	*st_cmd;
	char		*path;

	st_cmd = init_st_cmd((const char**)vars->env_vars);
	//read input

	txt_tmp = ft_strdup("");
	while (ft_strncmp((*current_token)->content, txt_tmp, ft_strlen((*current_token)->content) + 1))
	{
		txt = concatenate_txt(st_cmd);
		input_loop(st_cmd, vars);
		txt_tmp = ft_strndup(st_cmd->st_txt->txt, ft_strlen(st_cmd->st_txt->txt) - 1);
		st_cmd = append_st_cmd(st_cmd, "", "cont > ");
	}
	(*current_token)->content = add_quot(txt);
	(*current_token)->type = tk_dq_str;
	(*prev_token)->content = ft_strdup("<");
	(*prev_token)->type = tk_redirection;
	heredoc_count++;
	ft_printf("END TXT: {%s}\n", txt);
	path = heredoc(txt);
	ft_printf("END HEREDOC; path:{%s}\n", path);
	return (1);
}
