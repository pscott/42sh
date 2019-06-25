#include "ftsh.h"
#include "history.h"
#include "auto_completion.h"

static int		search_in_precise_path(char *path, char *to_find)
{
	DIR				*dir;
	struct dirent	*ent;

	if (!path)
		return (0);
	if ((dir = opendir(path)) == NULL)
		return (0);
	while ((ent = readdir(dir)))
	{
		if (!ft_strcmp(to_find, ent->d_name))
		{
			if (closedir(dir) == -1)
				return (0);
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
		clean_exit(1, MALLOC_ERR);
	while (path[j])
	{
		if (!(true_path = rm_spaces_path(path[j])))
			return (0);
		ret = search_in_precise_path(true_path, to_find);
		ft_strdel(&true_path);
		if (ret != 0)
			break ;
		j++;
	}
	ft_strdel(&to_find);
	return (ret);
}

static int		get_editor_fc(char *to_find)
{
	char		**path;
	t_vars		*vars;
	int			ret;

	vars = get_vars(NULL);
	path = NULL;
	get_path(&path, vars);
	if (path == NULL || *path == NULL)
		return (-1);
	ret = find_editor_in_path(path, to_find);
	ft_free_ntab(path);
	return (ret);
}

int				parse_editor_fc(char **argv, int i)
{
	int			ret;
	int			final;
	char		*to_find;

	if (argv[i] && ft_strnequ(argv[i], "-e", 2) && argv[i][2])
	{
		final = i;
		to_find = argv[i] + 2;
	}
	else if (!argv[i + 1])
		return (error_fc_histo(NULL, 0, editor_unspecified, NULL));
	else
	{
		final = i + 1;
		to_find = argv[i + 1];
	}
	if ((ret = get_editor_fc(to_find)) == -1)
		return (error_fc(to_find, 0, path_unspecified, NULL));
	else if (ret == 0)
		return (error_fc(to_find, 0, cmd_not_found, NULL));
	else
		return (final);
}
