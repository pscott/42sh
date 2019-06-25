#include "auto_completion.h"
#include "errors.h"

static int			get_filename(const char *next, const char *to_find,
					struct dirent *ent, char **filename)
{
	if (ft_strlen(next) == ft_strlen(to_find)
			|| ft_is_white_space(next[ft_strlen(to_find)]))
	{
		if (!(*filename = ft_strjoin(ent->d_name, " ")))
			clean_exit(1, 1);
	}
	else if (!(*filename = ft_strdup(ent->d_name)))
		clean_exit(1, 1);
	return (0);
}

static int			check_command_folder(char *path, t_auto_comp **match,
					const char *to_find, const char *next)
{
	DIR				*dir;
	struct dirent	*ent;
	char			*filename;

	if ((dir = opendir(path)) == NULL)
		return (1);
	filename = NULL;
	while ((ent = readdir(dir)))
	{
		if (!compare_entry2("..", ent->d_name)
			&& !compare_entry2(".", ent->d_name)
			&& !compare_entry(to_find, ent->d_name)
			&& !is_a_builtin(ent->d_name))
		{
			get_filename(next, to_find, ent, &filename);
			create_match_link(match, filename);
			ft_strdel(&filename);
		}
	}
	if (closedir(dir) == -1)
		return (1);
	return (0);
}

char				*get_filename_builtin(const char *to_find,
					const char *next, char *type)
{
	char		*filename;

	if (ft_strlen(next) == ft_strlen(to_find)
			|| ft_is_white_space(next[ft_strlen(to_find)]))
	{
		if (!(filename = ft_strjoin(type, " ")))
			clean_exit(1, 1);
	}
	else if (!(filename = ft_strdup(type)))
		clean_exit(1, 1);
	return (filename);
}

char				*rm_spaces_path(const char *str)
{
	char			*ret;
	int				i;
	int				j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	if (!(ret = ft_strnew(ft_strlen(str))))
		clean_exit(1, 1);
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

int					get_matching_exe(char **path, t_auto_comp **match,
					const char *to_find_real, const char *next)
{
	char			*true_path;
	int				i;

	i = 0;
	true_path = NULL;
	while (path && path[i])
	{
		true_path = rm_spaces_path(path[i++]);
		check_command_folder(true_path, match, to_find_real, next);
		ft_strdel(&true_path);
	}
	if (add_builtins(match, to_find_real, next, 1))
		return (1);
	if (!(*match))
		return (0);
	return (0);
}
