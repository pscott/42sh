#include "ftsh.h"
#include "env.h"
#include <limits.h>

static char	*add_brackets(const char *str)
{
	char	*res;

	if (!str)
		return (NULL);
	if (!(res = ft_strjoin("[", str)))
		clean_exit(1, MALLOC_ERR);
	if (!(res = ft_strjoin_free_left(res, "]")))
		clean_exit(1, MALLOC_ERR);
	return (res);
}

char		*exit_to_str(int exit)
{
	char	*res;
	char	*tmp;

	res = NULL;
	if (exit)
	{
		if (!(res = ft_itoa(exit)))
			clean_exit(1, MALLOC_ERR);
		tmp = res;
		res = add_brackets(res);
		ft_strdel(&tmp);
	}
	else if (!(res = ft_strdup("")))
		clean_exit(1, MALLOC_ERR);
	return (res);
}

static char	*get_valid_dir(t_vars *vars)
{
	char	*dir;
	char	*res;

	if (!(dir = get_varline_value("PWD", vars->env_vars))
				|| !(ft_strchr(dir, '/')))
	{
		ft_strdel(&dir);
		if (!(dir = getcwd(NULL, 0)))
		{
			if (!(res = ft_strdup("...")))
				clean_exit(1, MALLOC_ERR);
			return (res);
		}
	}
	res = ft_strdup(ft_strrchr(dir, '/'));
	ft_strdel(&dir);
	return (res);
}

char		*dir_to_str(const char *tmp)
{
	char	*res;
	char	*dir;
	t_vars	*vars;

	if (!tmp)
		return (NULL);
	if (!(vars = get_vars(NULL)))
		return (NULL);
	dir = get_valid_dir(vars);
	res = add_brackets(dir);
	ft_strdel(&dir);
	return (res);
}
