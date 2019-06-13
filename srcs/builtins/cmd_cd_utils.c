#include "builtins.h"
#include "env.h"
#include "errors.h"

/*
**	Returns a freshly allocated string containing the value of value associated
**	with the env_key paramter. If env_key is not found in env, returns NULL.
*/

char			*get_directory(const char *env_key, const char **env)
{
	char			*dest;

	dest = NULL;
	if (!(dest = get_envline_value((char*)env_key, (char**)env)))
	{
		if (ft_strncmp(env_key, "PWD", 4))
			print_errors(ERR_NOT_SET, ERR_NOT_SET_STR, (char*)env_key);
		return (NULL);
	}
	if (!(dest = ft_strdup(dest)))
		clean_exit(1, 1);
	return (dest);
}

char			*get_cwd_value(const char **env)
{
	char			*cwd;

	cwd = NULL;
	if ((cwd = get_envline_value("PWD", (char**)env)))
	{
		if (!(cwd = ft_strdup(cwd)))
			clean_exit(1, 1);
	}
	else if (!(cwd = getcwd(NULL, 0)))
	{
		print_errors(ERR_GETCWD, ERR_GETCWD_STR, NULL);
		return (NULL);
	}
	return (cwd);
}

/*
**	Get the right path with getcwd call, for easier chdir execution
*/

char			*relative_directory(const char *path, const char **env, int opt,
		int *cdpath)
{
	char			*cwd;
	char			*tmp;
	char			*dest;

	ft_initialize_str(&cwd, &tmp, &dest, NULL);
	cwd = get_cwd_value(env);
	if (cwd[0] && cwd[0] == '/' && !cwd[1])
		tmp = cwd;
	else if (!ft_strncmp(path, "..", 2) && opt != 'P')
		return (cut_path_string(cwd, 1));
	else
	{
		if (check_cdpath_var(path, env, &tmp, cdpath))
		{
			if (!(tmp = ft_strjoin(cwd, "/")))
				clean_exit(1, 1);
			ft_strdel(&cwd);
		}
	}
	if (!(dest = ft_strjoin(tmp, path)))
		clean_exit(1, 1);
	ft_strdel(&tmp);
	ft_strdel(&cwd);
	return (dest);
}
