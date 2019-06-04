#include "lexer.h"
#include "env.h"
#include <pwd.h>
#include "ast.h"
#include "line_editing.h"
#include "get_next_line.h"
#include "cmd_parsing.h"

/*
**	Replaces the str with the '~' expanded.
*/

int				replace_tilde(char **str, const char **env)
{
	char			*new_str;
	char			*home_str;

	if (!(home_str = get_envline_value("HOME", (char **)env)))
	{
		ft_putendl("TMP: NO HOME VAR");//TODO
		return (0);
	}
	if (!(new_str = ft_strnew(ft_strlen(home_str) + ft_strlen(*str) - 1)))
		ERROR_MEM;
	ft_strcpy(new_str, home_str);
	ft_strcat(new_str, *str + 1);
	ft_memdel((void*)str);
	*str = new_str;
	return (1);
}

static void		insert_expansion(char *user, char **str)
{
	char			*tmp_end;
	char			*expansion;
	struct passwd	*infos;

	ft_initialize_str(&tmp_end, &expansion, NULL, NULL);
	if (!(infos = getpwnam(user)))
		return ;
	else if (infos && infos->pw_dir)
	{
		if (is_slashed(*str))
		{
			tmp_end = ft_strsub(*str, ft_strlen_char(*str, '/'),
					ft_strlen(*str));
			if (!(expansion = ft_strdup(infos->pw_dir)))
				ERROR_MEM;
			ft_strdel(str);
			if (!(*str = ft_strjoin(expansion, tmp_end)))
				ERROR_MEM;
			ft_strdel(&tmp_end);
		}
		else
		{
			ft_strdel(str);
			if (!(*str = ft_strdup(infos->pw_dir)))
				ERROR_MEM;
		}
	}
}

static char		*get_to_find_exp_tilde_user(char **str)
{
	char			*ret;

	ret = NULL;
	if (!ft_strchr(*str, '/'))
	{
		if (!(ret = ft_strdup((*str) + 1)))
			ERROR_MEM;
	}
	else
	{
		if (!(ret = ft_strndup((*str) + 1, ft_strlen_char(*str, '/') - 1)))
			ERROR_MEM;
	}
	return (ret);
}

static int		replace_tilde_users(char **str)
{
	char			*to_find;

	to_find = get_to_find_exp_tilde_user(str);
	insert_expansion(to_find, str);
	ft_strdel(&to_find);
	return (0);
}

/*
**	Depending of the input, we expand tilde as our user's home (~/directory),
**	or the home directory of the specified user (~root/)
*/

int				parse_tildes(t_token *token_head, const char **env)
{
	t_token			*prev_token;
	t_token			*curr_token;
	int				ret;

	curr_token = token_head;
	prev_token = NULL;
	ret = 0;
	while (curr_token)
	{
		if (curr_token->type == tk_word
				&& (ret = is_valid_tilde(curr_token->content, prev_token)))
		{
			if (ret == 1 && !replace_tilde(&curr_token->content, env))
				return (0);
			else if (ret == 2 && ft_strlen(curr_token->content) > 1
					&& !replace_tilde_users(&curr_token->content))
				return (0);
		}
		prev_token = curr_token;
		curr_token = curr_token->next;
	}
	return (1);//tmp
}
