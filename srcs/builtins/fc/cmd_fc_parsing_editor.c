#include "ftsh.h"
#include "history.h"
#include "auto_completion.h"

static int		search_in_precise_path(char *path, char *to_find)
{
	DIR				*dir;
	struct dirent	*ent;

	if ((dir = opendir(path)) == NULL)
		return (0);
	while ((ent = readdir(dir)))
	{
		if (!ft_strcmp(to_find, ent->d_name))
		{
			return (1);
		}
	}
	if (closedir(dir) == -1)
		return (0);
	return (0);

}

static int		find_editor_in_path(char **path, char *arg)
{
	char			*to_find;
	char			*true_path;
	int				j;
	int				ret;

	j = 0;
	ret = 0;
	if (!(to_find = ft_strtrim(arg)))
		clean_exit(1, 1);
	while (path[j])
	{
		true_path = rm_spaces_path(path[j]);
		ret = search_in_precise_path(true_path, to_find);
		if (ret != 0)
			break ;
		j++;
	}
	ft_strdel(&to_find);
	return (ret);

}

static int		get_editor_fc(char **argv, int i)
{
	char		**path;
	t_vars		*vars;
	int			ret;

	vars = get_vars(NULL);
	path = NULL;
	get_path(&path, vars);
	if (path == NULL || *path == NULL)
		return (-1);
	ret = find_editor_in_path(path, argv[i + 1]);

	return (ret);
}

int				parse_editor_fc(char **argv, int i)
{
	int			j;
	int			ret;

	j = 0;
	while (argv[j] && j < i)
	{
		if (argv[j][0] == '-' && ft_strchr(argv[j], 'e'))
		{
			if (!argv[j + 1])
				return (error_fc(NULL, 0, editor_unspecified, NULL));
			if ((ret = get_editor_fc(argv, j)) == -1)
				return (error_fc(argv[j + 1], 0, path_unspecified, NULL));
			else if (ret == 0)
				return (error_fc(argv[j + 1], 0, cmd_not_found, NULL));
			else
				return (j + 1);
		}
		j++;
	}
	return (0);

}
