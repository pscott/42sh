#include "libft.h"
#include "line_editing.h"
#include <dirent.h>

static int			check_command_folder(char *path, t_auto_comp **match, char *to_find)
{
	DIR				*dir;
	struct dirent	*ent;
	int				k;
	unsigned char	t;

	k = 0;
	if ((dir = opendir(path)) == NULL)
		return (1);
	//	return (ERR_OPENDIR);
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
			if (create_match_link(match, ent->d_name, t))
			{
				closedir(dir);
				return (1);
			//	return (ERR_MALLOC);
			}
		}
		k++;
	}
	if (closedir(dir) == -1)
		return (1);
	//	return (ERR_CLOSEDIR);
	return (0);
}

static int			add_builtins(t_auto_comp **match, char *to_find)
{
	if (!compare_entry(to_find, "exit"))
	{
		if (create_match_link(match, "exit", REGULAR))
			return (1);
			//return (ERR_MALLOC);
	}
	else if (!compare_entry(to_find, "setenv"))
	{
		if (create_match_link(match, "setenv", REGULAR))
			return (1);
	//		return (ERR_MALLOC);
	}
	else if (!compare_entry(to_find, "unsetenv"))
	{
		if (create_match_link(match, "unsetenv", REGULAR))
			return (1);
	//		return (ERR_MALLOC);
	}
	return (0);
}

static int			add_alias(t_auto_comp **match, char *to_find)
{
	//quand les alias seront geres
	return (0);
}

static char			*rm_spaces_path(char *str)
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


int					find_matching_exe(char **path, t_auto_comp **match, char *to_find, int is_exe)
{
	char			*true_path;
	char			*to_find_real;
	int				i;

	i = 0;
	to_find_real = ft_strndup(to_find, ft_strlen(to_find) - 2);
	//Proteciton malloc
	while (path[i])
		{
			true_path = rm_spaces_path(path[i]);
			if (check_command_folder(path[i++], match, to_find) ==  1 /*ERR_MALLOC*/)
				return (1);
		//		return (ERR_MALLOC); // leaks
		}
	if (is_exe == 1 && add_builtins(match, to_find))
		return (1);
//		return (ERR//_MALLOC);
	if (is_exe == 1 && add_alias(match, to_find))
		return (1);	
	//	return (ERR_MALLOC);
	if (!(*match))
		return (0);
	while ((*match)->prev)
	{
		(*match) = (*match)->prev;
	}
/*	while (*match)
	{
		ft_putendl((*match)->name);
		ft_putnbr(i++);
		if ((*match)->next)
			(*match) = (*match)->next;
		else
			sleep(10);
	}*/
//	*match = ft_list_sort_ascii(*match);
//	ft_putendl((*match)->name);
//	sleep(1);
	ft_strdel(&to_find_real);
	return (0);
}
