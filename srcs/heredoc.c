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

//-read and save input in a file
//	check if default filename exist ('/tmp/tmp_heredoc0000'):
//		if not: create it
//		else: increment number at the end of filename
//-replace '<<' by '<'
//-replace 'EOF' by 'path to file'

//later, at exec:
//rm all used file (can we)

#define	HEREDOC_FILENAME "/tmp/.tmp_heredoc"
#define	MAX_INT_LEN 10
#define UINT_MAX 4294967295

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

/*
** heredoc
** create and open an unique filename
** write the desired content in it, close it
** and return the path to the file
*/

char	*heredoc(const char *txt)
{
	char	*path;
	int		fd;

	if (!(path = find_uniq_filename()))
		ft_dprintf(2, "tmp(heredoc): can't create unique temporary filename\n");
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

/* OUTDATED ?
** save_heredoc
** enter in read_mode until the matching 'EOF' is found
** it will write the new content in a file
** replace '<<' by '<'
** and 'EOF' by the path of the new file
*/

//need to check if EOF is quoted
/*
t_bool	save_heredoc(t_token **prev_token, t_token **current_token, t_vars *vars)
{
	char		*txt;
	char		*txt_tmp;
	t_st_cmd	*st_cmd;
	char		*path;

	st_cmd = init_st_cmd((const char**)vars->env_vars);
	txt_tmp = ft_strdup("");
	while (ft_strncmp((*current_token)->content, txt_tmp, ft_strlen((*current_token)->content) + 1))
	{
		txt = concatenate_txt(st_cmd);
		input_loop(st_cmd, vars);
		ft_memdel((void*)&txt_tmp);
		txt_tmp = ft_strndup(st_cmd->st_txt->txt, ft_strlen(st_cmd->st_txt->txt) - 1);
		st_cmd = append_st_cmd(st_cmd, "", "cont > ");
	}
	if (!(path = heredoc(txt)))//protect
		return (0);
	ft_memdel((void*)&txt_tmp);
	ft_memdel((void*)&txt);
	//(*current_token)->content = add_quot(txt);
	ft_memdel((void*)&(*current_token)->content);
	(*current_token)->content = path;//strdup ? nop, already alloc, will be free later
	(*current_token)->type = tk_word;//was tk_dq_str, should it be tk_heredoc_path or tk_q_str
	ft_memdel((void*)&(*prev_token)->content);
	(*prev_token)->content = ft_strdup("<");//useless ?
	(*prev_token)->type = tk_redirection;
	free_st_cmd(st_cmd);
	return (1);
}
*/

//i can find eof len before, and then just cpy each token in it
static char	*eof_join(char *str, t_token *probe)
{
	if (probe->type == tk_word || probe->type == tk_monoc)
		return(ft_strjoin(str, probe->content));
	if (probe->type == tk_sq_str)
		return (ft_strjoin(str, remove_quot(probe->content)));
	if (probe->type == tk_dq_str)
		return (ft_strjoin(str, remove_quot(probe->content)));
	return (NULL);//this should never happen
}

//static char	*get_eof(t_token *probe)
static unsigned char	get_eof(char **eof, t_token *probe)
{
	unsigned char	is_eof_quoted;
	//char	*eof;
	//char	*tmp_str;

	//eof = NULL;
	is_eof_quoted = 0;
	while (probe->next && probe->next->type == tk_eat)
		probe = probe->next;
	probe = probe->next;
	ft_printf("current type=%d\n", probe->type);
	while (probe && probe->type > tk_eat && probe->type < tk_redirection)
	{
		ft_printf("joining\n");
		if (probe->type >= tk_monoc && probe->type <= tk_dq_str)
			is_eof_quoted = 1;
		*eof = eof_join(*eof, probe);
		probe = probe->next;
	}
	return(is_eof_quoted);
}

//MAIN parse the entire cmdline(tk_lst)
/*
** if it find a heredoc
** -get real EOF (remove \ ' " and set is_eof_quoted)
** -read until EOF
** -expand if (is_eof_quoted)
** -write in /tmp (uniq check)
** replace << by <
** replace first EOF token by 'path to /tmp file' and EAT the rest
*/
t_bool	parse_heredoc(t_token *token_head, t_vars *vars)
{
	t_token			*token_probe;
	t_token			*prev_token;
	char			*eof;
	unsigned char	is_eof_quoted;

	token_probe = token_head;
	prev_token = NULL;
	while (token_probe->next)
	{
		token_probe = token_probe->next;
		if (token_probe->type == tk_heredoc)
		{
			prev_token = token_probe;
			ft_printf("HERE IS A HEREDOC\n");
			//eof = get_eof(token_probe);
			eof = NULL;
			is_eof_quoted = get_eof(&eof, token_probe);
			ft_printf("EOF: {%s}, quot:%d\n", eof, (int)is_eof_quoted);
		}
		save_heredoc(eof, prev_token, token_probe, is_eof_quoted, vars);
	}
	return (1);
}

//t_bool	save_heredoc(t_token **prev_token, t_token **current_token, t_vars *vars)
//do i need prev_token ?
t_bool	save_heredoc(char *eof, t_token *prev_token, t_token *current_token, unsigned char is_eof_quoted, t_vars *vars)
{
	char		*txt;
	char		*txt_tmp;
	t_st_cmd	*st_cmd;
	char		*path;

	st_cmd = init_st_cmd((const char**)vars->env_vars);
	txt_tmp = ft_strdup("");
	while (ft_strncmp(current_token->content, txt_tmp, ft_strlen(current_token->content) + 1))
	{
		txt = concatenate_txt(st_cmd);
		input_loop(st_cmd, vars);
		ft_memdel((void*)&txt_tmp);
		txt_tmp = ft_strndup(st_cmd->st_txt->txt, ft_strlen(st_cmd->st_txt->txt) - 1);
		st_cmd = append_st_cmd(st_cmd, "", "heredoc> ");
	}
	//expand txt if !is_eof_quoted
	if (!(path = heredoc(txt)))//protect
		return (0);
	ft_memdel((void*)&txt_tmp);
	ft_memdel((void*)&txt);
	ft_memdel((void*)&(*current_token)->content);
	current_token->content = path;//strdup ? nop, already alloc, will be free later
	current_token->type = tk_word;//was tk_dq_str, should it be tk_heredoc_path or tk_q_str
	ft_memdel((void*)&(*prev_token)->content);
	(*prev_token)->content = ft_strdup("<");//useless ?
	(*prev_token)->type = tk_redirection;
	free_st_cmd(st_cmd);
	return (1);
}
