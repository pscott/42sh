#include "lexer.h"
#include "ast.h"
#include "line_editing.h"

static t_bool	is_valid_tilde(t_token *curr_token, t_token *prev_token)
{
	if (!prev_token && (!ft_strncmp("~", curr_token->content, 1)))
		return (2);
	if (!prev_token && !ft_strncmp("~/", curr_token->content, 2))
		return (1);
	if (prev_token && prev_token->type == tk_eat
		&& (!ft_strncmp("~", curr_token->content, 1)))
		return (2);
	if (prev_token && prev_token->type == tk_eat
		&& ft_strncmp("~/", curr_token->content, 2))
		return (1);
	return (0);
}

/*
**	Replaces the str with the '~' expanded.
*/

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
	ft_memdel((void*)str);
	*str = new_str;
	return (1);
}

static t_bool	replace_tilde_users(char **str, const char **env)
{
	int				fd;
	char			*line;
	char			*user;
	struct passwd	*infos;
	int				ret;

	line = NULL;
	user = NULL;
	ret = 0;
	(*str)++;
	fd = open("/etc/passwd", 0);
	while (((ret = get_next_line(fd, &line)) != -1))
	{
		if (line && line[0] && line[0] != '#' && (!ft_strncmp(*(str), line, ft_strlen(str) + 1)))
		{
			if (!(user = ft_strndup(line, ft_strlen_char(line, ':'))))		
				ERROR_MEM
			infos = getpwnam(user);
			if (infos && infos->pw_dir)
			{
			//	ft_strdel(str); str token pas alloue ?
				if (!(*str = ft_strdup(infos->pw_dir)))
					ERROR_MEM
			}
			ft_strdel(&user);
			return (1);
		}
		if (ret == 0)
			break ;
	}
	return (0);
}	

t_bool	parse_tildes(t_token *token_head, const char **env)
{
	t_token *prev_token;
	t_token *curr_token;
	int		ret;

	curr_token = token_head;
	prev_token = NULL;
	ret = 0;
	//ft_putendl("##########in Parse_tildes");
	while (curr_token)
	{
		if (curr_token->type == tk_word && (ret = is_valid_tilde(curr_token, prev_token)))//~ doesn't expand in ""
		{
			if (ret == 1)//case ~/xxxx -> chercher dans le home, get_envline
			{
				if (!replace_tilde(&curr_token->content, env))
					return (0);
			}
			else if (ret == 2)
			{
				if (!replace_tilde_users(&curr_token->content, env))
					return (0);
			}
		}
		prev_token = curr_token;
		curr_token = curr_token->next;
	}
	//ft_putendl("################");
	return (1);//tmp
}
