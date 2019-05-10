#include "lexer.h"
#include "ast.h"

static t_bool	is_valid_tilde(t_token *curr_token, t_token *prev_token)
{
	if (!prev_token && (!ft_strncmp("~", curr_token->content, 2)
				|| !ft_strncmp("~/", curr_token->content, 2)))
		return (1);
	else if (prev_token && prev_token->type == TK_EAT
			&& (!ft_strncmp("~", curr_token->content, 2)
				|| !ft_strncmp("~/", curr_token->content, 2)))
		return (1);
	return (0);
}

t_bool	replace_tilde(char **str, const char **env)
{
	char	*new_str;
	char	*home_str;

	if (!(home_str = get_envline_value("HOME", (char **)env)))
	{
		ft_putendl("NO HOME VAR");//TODO
		return (0);
	}
	if (!(new_str = ft_strnew(ft_strlen(home_str) + ft_strlen(*str) - 1)))
		ERROR_MEM;
	ft_strcpy(new_str, home_str);
	ft_strcat(new_str, *str + 1);
	ft_memdel((void*)*(&str));
	*str = new_str;
	return (1);
}

t_bool	parse_tildes(t_token *token_head, const char **env)
{
	t_token *prev_token;
	t_token *curr_token;
	
	curr_token = token_head;
	prev_token = NULL;
	//ft_putendl("##########in Parse_tildes");
	while (curr_token)
	{
		if (curr_token->type == TK_WORD && is_valid_tilde(curr_token, prev_token))//~ doesn't expand in ""
		{
			if (!replace_tilde(&curr_token->content, env))
				return (0);
		}
		prev_token = curr_token;
		curr_token = curr_token->next;
	}
	//ft_putendl("################");
	return (1);//tmp
}
