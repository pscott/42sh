#include "libft.h"
#include "line_editing.h"
#include "errors.h"
#include <dirent.h>

static int			check_command_folder(char *path, t_auto_comp **match, char *to_find, char *next)
{
	DIR				*dir;
	struct dirent	*ent;
	unsigned char	t;
	char			*tmp;

	if ((dir = opendir(path)) == NULL)
		return (0);
	while ((ent = readdir(dir)))
	{
		if (!compare_entry2("..", ent->d_name)
				&& !compare_entry2(".", ent->d_name)
				&& !compare_entry(to_find, ent->d_name))

		if (!compare_entry(to_find, ent->d_name))
		{
			t = 0;
			if (ent->d_type)
				t = ent->d_type;
			tmp = NULL;
			if (ft_strlen(next) == ft_strlen(to_find) || is_white_spaces(next[ft_strlen(to_find)]))
			{
				if (!(tmp = ft_strjoin(ent->d_name, " ")))
					ERROR_MEM
			}
			else
				if (!(tmp = ft_strdup(ent->d_name)))
					ERROR_MEM
			if (create_match_link(match, tmp, t))
			{
				closedir(dir);
				ERROR_MEM
			}
			ft_strdel(&tmp);
		}
	}
	if (closedir(dir) == -1)
		return (print_errors(ERR_CLOSEDIR, ERR_CLOSEDIR_STR, NULL));
	return (0);
}

static int			add_builtins(t_auto_comp **match, char *to_find)
{
	if (!compare_entry(to_find, "exit"))
	{
		if (create_match_link(match, "exit", REGULAR))
			ERROR_MEM
	}
	else if (!compare_entry(to_find, "setenv"))
	{
		if (create_match_link(match, "setenv", REGULAR))
			ERROR_MEM
	}
	else if (!compare_entry(to_find, "unsetenv"))
	{
		if (create_match_link(match, "unsetenv", REGULAR))
			ERROR_MEM
	}
	return (0);
}

static int			add_alias(t_auto_comp **match, char *to_find)
{
	//quand les alias seront geres
	return (0);
}

char				*rm_spaces_path(char *str)
{
	char			*ret;
	int				i;
	int				j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	ret = ft_strnew(ft_strlen(str));
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1] != '\\')
			i++;
		ret[j] = str[i];
		i++;
		j++;
	}
	return (ret);
}


int					find_matching_exe(char **path, t_auto_comp **match, char *to_find_real, char *next)
{
	char			*true_path;
	int				i;

	i = 0;
	true_path = NULL;
	while (path[i])
		{
			true_path = rm_spaces_path(path[i++]);
			check_command_folder(true_path, match, to_find_real, next);
			ft_strdel(&true_path);
		}
	if (add_builtins(match, to_find_real))
		return (1);
	if (add_alias(match, to_find_real))
		return (1);
	if (!(*match))
		return (0);
/*	if (match)
		while ((*match)->prev)
		{
			(*match) = (*match)->prev;
		}*/// pas oublier de le remettre pour reset
/*	while (*match)
	{
		ft_putendl((*match)->name);
		ft_putnbr(i++);
		if ((*match)->next)
			(*match) = (*match)->next;
		else
			sleep(10);
	}*/
	return (0);
}
