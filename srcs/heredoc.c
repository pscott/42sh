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

//i need to write the content of heredoc in a file, then replace EOF with the path of the file
t_bool	save_heredoc(t_token **prev_token, t_token **current_token, t_vars *vars)
{
	static int	heredoc_count = 0;
	//int			fd;
	char		*txt;
	char		*txt_tmp;
	t_st_cmd	*st_cmd;

	st_cmd = init_st_cmd((const char**)vars->env_vars);
	//read input
	ft_printf("cmp{%d}\n", ft_strncmp((*current_token)->content, txt_tmp, ft_strlen((*current_token)->content) + 1));
	ft_printf("curr: {%s}\n", (*current_token)->content);
	ft_printf("st_cmd: {%s}\n", st_cmd->st_txt->txt);




	txt_tmp = ft_strdup("");
	while (ft_strncmp((*current_token)->content, txt_tmp, ft_strlen((*current_token)->content) + 1))
	{
		ft_printf("IN WHILE\n");
		txt = concatenate_txt(st_cmd);
		input_loop(st_cmd, vars);
		txt_tmp = ft_strndup(st_cmd->st_txt->txt, ft_strlen(st_cmd->st_txt->txt) - 1);
		ft_printf("{%s}\n", txt_tmp);
		st_cmd = append_st_cmd(st_cmd, "", "cont > ");
		//st_cmd = reset_st_cmd(st_cmd);
	}
	ft_printf("IN HEREDOC 3\n");
	ft_printf("{%s}curr type: %d\n", (*current_token)->content, (*current_token)->type);
	//(*current_token)->content = ft_strdup(txt_tmp);
	(*current_token)->content = add_quot(txt);
	//(*current_token)->content = ft_strdup(st_cmd->st_txt->txt);
	//(*current_token)->content = ft_strdup("\"bonsoir\"");
	(*current_token)->type = tk_dq_str;
	ft_printf("{%s}postcurr type: %d\n", (*current_token)->content, (*current_token)->type);
	ft_printf("{%s}prev type: %d\n", (*prev_token)->content, (*prev_token)->type);
	(*prev_token)->content = ft_strdup("<");
	(*prev_token)->type = tk_redirection;
	ft_printf("{%s}postprev type: %d\n", (*prev_token)->content, (*prev_token)->type);
	heredoc_count++;
	return (1);
}
