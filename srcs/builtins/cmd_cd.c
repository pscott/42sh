#include "builtins.h"
#include "errors.h"
#include "42sh.h"
#include <sys/stat.h>
#include <limits.h>

/*
**	Returns a freshly allocated string containing the value of value associated
**	with the env_key paramter. If env_key is not found in env, returns NULL.
*/

static char	*get_directory(const char *env_key, const char **env)
{
	char	*dest;

	if (!(dest = get_envline_value((char*)env_key, (char**)env)))
	{
		print_errors(ERR_NOT_SET, ERR_NOT_SET_STR, (char*)env_key);
		return (NULL);
	}
	if (!(dest = ft_strdup(dest)))
		ERROR_MEM;
	return (dest);
}

/*
**	Updates the pwd and oldpwd env variables, then calles chdir.
**	Returns 0 on success, else returns 1.
*/

static int	change_environ(char *new_pwd, char ***env)
{
	char	 *old_pwd;
	char	*pwd;
	int		ret;

	if (!(old_pwd = getcwd(NULL, 0)))
		return (print_errors(ERR_GETCWD, ERR_GETCWD_STR, NULL));
	set_env_var("OLDPWD", old_pwd, env);
	ft_strdel(&old_pwd);
	if ((ret = chdir(new_pwd)) == -1)
		print_errors(ERR_CHDIR, ERR_CHDIR_STR, new_pwd);
	if (!(pwd = getcwd(NULL, 0)))
		return (print_errors(ERR_GETCWD, ERR_GETCWD_STR, NULL));
	set_env_var("PWD", pwd, env);
	ft_strdel(&new_pwd);
	ft_strdel(&pwd);
	return (ret);
}

static char	*relative_directory(const char *path, const char **env)
{
	char	*cwd;
	char	*tmp;
	char	*dest;

	if ((cwd = get_envline_value("PWD", (char**)env)))
	{
		if (!(cwd = ft_strdup(cwd)))
			ERROR_MEM;
	}
	else
	{
		if (!(cwd = getcwd(NULL, 0))) //test it pls
		{
			print_errors(ERR_GETCWD, ERR_GETCWD_STR, NULL);
			return (NULL);
		}
	}
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

/*
**	Returns 0 if it succesfully managed to change directory ; else returns
**	the corresponding error value.
*/

int			case_cd(char **t, char ***env)
{
	char			*dest;
	struct	stat	infos;

	if (!(t[1]))
		dest = get_directory("HOME", (const char**) *env);
	else if (ft_strncmp(t[1], "-", 2) == 0)
		dest = get_directory("OLDPWD", (const char**) *env);
	else if (t[1][0] == '/')
	{
		if (!(dest = ft_strdup(t[1]))) // test with '/' at the END pls
			ERROR_MEM;
	}
	else
		dest = relative_directory(t[1], (const char**) *env);
	if (!dest)
		return (1);
	if (stat(dest, &infos) == -1)
		return (print_errors(ERR_NOEXIST, ERR_NOEXIST_STR, dest));
	else if (!S_ISDIR(infos.st_mode))
		return (print_errors(ERR_NOTDIR, ERR_NOTDIR_STR, dest));
	else if (access(dest, F_OK) == 0 && access(dest, X_OK) == -1)
		return (print_errors(ERR_PERM, ERR_PERM_STR, dest));
	return (change_environ(dest, env));
}
