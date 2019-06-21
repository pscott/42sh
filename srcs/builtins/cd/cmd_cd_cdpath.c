#include "builtins.h"
#include "execution.h"
#include "env.h"

/*
**	Utils for CDPATH env value
*/

static char		*join_path_slash(char *path)
{
	int		i;
	char	*newpath;

	i = 0;
	while (path[i])
		i++;
	if (i != 0)
		i--;
	if (path[i] != '/')
	{
		if (!(newpath = ft_strjoin(path, "/")))
			clean_exit(1, 1);
	}
	else
	{
		if (!(newpath = ft_strdup(path)))
			clean_exit(1, 1);
	}
	return (newpath);
}

static char		*find_cdpath(const char *file, char **paths)
{
	unsigned int	i;
	char			*path_w_slash;
	char			*possible_path;

	if (!*file || !ft_strncmp(".", file, 2) || !ft_strncmp("..", file, 3)
			|| !paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		path_w_slash = join_path_slash(paths[i]);
		if (!(possible_path = ft_strjoin(path_w_slash, file)))
			clean_exit(1, 1);
		if (check_access(possible_path) == 0)
		{
			ft_strdel(&possible_path);
			return (path_w_slash);
		}
		ft_strdel(&path_w_slash);
		ft_strdel(&possible_path);
		i++;
	}
	return (NULL);
}

static int		get_cdpath(char ***path, char **env)
{
	char		*tmpath;

	if (!env)
		return (1);
	if (!(tmpath = get_envline_value("CDPATH", env)))
	{
		*path = NULL;
		return (1);
	}
	if (!(*path = ft_strsplit(tmpath, ":")))
		clean_exit(1, 1);
	return (0);
}

int				check_cdpath_var(const char *path, const char **env,
		char **tmp, int *check)
{
	char	**cdpath;

	if (get_cdpath(&cdpath, (char **)env))
		return (1);
	if (!(*tmp = find_cdpath(path, cdpath)))
	{
		ft_free_ntab(cdpath);
		return (1);
	}
	ft_free_ntab(cdpath);
	*check = 1;
	return (0);
}
