#include "builtins.h"
#include "errors.h"
#include "42sh.h"
#include <sys/stat.h>
#include <limits.h>

static int	apply_cd(char **t, char ***env)
{
	char	*ptr;

	if (!t[1])
	{
		if (!(ptr = get_envline("HOME", *env)))
			return (ERR_NOEXIST);
	}
	else if (ft_strncmp(t[1], "-", 2) == 0)
	{
		if (!(ptr = get_envline("OLDPWD", *env)))
			return (ERR_NO_OLDPWD);
	}
	else
		ptr = t[1];
	return (chdir(ptr));
}

static int	change_environ(char *buf, char ***env)
{
	char	buf2[PATH_MAX + 1];

	if (getcwd(buf2, PATH_MAX) == NULL)
		return (print_errors(ERR_GETCWD, ERR_GETCWD_STR, NULL));
	set_env_var("PWD", buf2, env);
	set_env_var("OLDPWD", buf, env);
	return (0);
}

static int	print_cd_errors(int ret, char *str)
{
	if (ret == -1)
		return (print_errors(ERR_CHDIR, ERR_CHDIR_STR, NULL));
	else if (ret == ERR_NOEXIST)
		return (print_errors(ERR_NOEXIST, ERR_NOEXIST_STR, "HOME"));// ?
	else if (ret == ERR_NO_OLDPWD)
		return (print_errors(ERR_NO_OLDPWD, ERR_NO_OLDPWD_STR, str));
	return (0);
}

/*
 **	
 */

int			case_cd(char **t, char ***env)
{
	char			buf[PATH_MAX + 1];
	int				ret;
	struct	stat	infos;

	if (t && t[1])
	{
		ret = ft_strlen(t[1]) ? ft_strlen(t[1]) - 1 : 0;
		if (t[1][ret] == '/')
			t[1][ret] = '\0';
		if (lstat(t[1], &infos) == -1)
		{
			print_errors(ERR_NOEXIST, ERR_NOEXIST_STR, t[1]);
			ret = 1;
		}
		else if (!S_ISDIR(infos.st_mode))
		{
			print_errors(ERR_NOTDIR, ERR_NOTDIR_STR, t[1]);
			ret = 1;
		}
		else if (access(t[1], F_OK) == 0 && access(t[1], X_OK) == -1)
		{
			print_errors(ERR_ACCESS, ERR_ACCESS_STR, t[1]);
			ret = 1;
		}
		else
			ret = 0;
	}
	else
	{
		if (getcwd(buf, PATH_MAX) == NULL)
		{
			print_errors(ERR_GETCWD, ERR_GETCWD_STR, NULL);
			return (2);
		}
		ret = apply_cd(t, env);
		if (ret == 0 && change_environ(buf, env))
			ERR_MALLOC;
		print_cd_errors(ret, t[1]);
	}
	return (ret);
}
