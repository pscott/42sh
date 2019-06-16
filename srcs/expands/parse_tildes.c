#include "lexer.h"
#include "env.h"
#include "ast.h"
#include "line_editing.h"
#include "cmd_parsing.h"

/*
**	Replaces the str with the '~' expanded.
*/

int				replace_tilde(char **str, const char **env)
{
	t_vars			*vars;
	char			*new_str;
	char			*home_str;

	if (!(home_str = get_envline_value("HOME", (char **)env)))
	{
		vars = get_vars(NULL);
		if (vars->verbose)
			ft_dprintf(2, "error: HOME not set\n");
		return (0);
	}
	if (!(new_str = ft_strnew(ft_strlen(home_str) + ft_strlen(*str) - 1)))
		clean_exit(1, 1);
	ft_strcpy(new_str, home_str);
	ft_strcat(new_str, *str + 1);
	ft_memdel((void*)str);
	*str = new_str;
	return (1);
}

static void		insert_expansion(char *user, char **str)
{
	char			*expansion;
	struct passwd	*infos;

	expansion = NULL;
	if (!(infos = getpwnam(user)))
		return ;
	else if (infos && infos->pw_dir)
	{
		if (is_slashed(*str))
		{
			if (!(expansion = ft_strdup(infos->pw_dir)))
				clean_exit(1, 1);
			ft_strdel(str);
			if (!(*str = ft_strjoin_free_left(expansion,
						*str + ft_strlen_char(*str, '/'))))
				clean_exit(1, 1);
		}
		else
		{
			ft_strdel(str);
			if (!(*str = ft_strdup(infos->pw_dir)))
				clean_exit(1, 1);
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
			clean_exit(1, 1);
	}
	else
	{
		if (!(ret = ft_strndup((*str) + 1, ft_strlen_char(*str, '/') - 1)))
			clean_exit(1, 1);
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
	return (1);
}
