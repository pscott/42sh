#include "builtins.h"
#include "errors.h"
#include "42sh.h"
#include <sys/stat.h>
#include <limits.h>

/*
**	Returns a freshly allocated string containing the value of value associated
**	with the env_key paramter. If env_key is not found in env, returns NULL.
*/

char	*get_directory(const char *env_key, const char **env)
{
	char			*dest;

	dest = NULL;
	if (!(dest = get_envline_value((char*)env_key, (char**)env)))
	{
		print_errors(ERR_NOT_SET, ERR_NOT_SET_STR, (char*)env_key);
		return (NULL);
	}
	if (!(dest = ft_strdup(dest)))
		ERROR_MEM;
	return (dest);
}

char	*get_cwd_value(const char **env)
{
	char			*cwd;

	cwd = NULL;
	if ((cwd = get_envline_value("PWD", (char**)env)))
	{
		if (!(cwd = ft_strdup(cwd)))
			ERROR_MEM;
	}
	else if (!(cwd = getcwd(NULL, 0)))//test it pls
	{
		print_errors(ERR_GETCWD, ERR_GETCWD_STR, NULL);
		return (NULL);
	}
	return (cwd);
}

char	*relative_directory(const char *path, const char **env)
{
	char			*cwd;
	char			*tmp;
	char			*dest;

	ft_initialize_str(&cwd, &tmp, &dest, NULL);
	cwd = get_cwd_value(env);
	if (cwd[0] && cwd[0] == '/' && !cwd[1])
		tmp = cwd;
	else
	{
		if (!(tmp = ft_strjoin(cwd, "/")))
			ERROR_MEM;
		ft_strdel(&cwd);
	}
	if (!(dest = ft_strjoin(tmp, path)))
		ERROR_MEM;
	ft_strdel(&tmp);
	return (dest);
}
