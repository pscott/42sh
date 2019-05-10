#include "builtins.h"
#include "errors.h"
#include "tosh.h"
#include "ast.h"
#include <sys/stat.h>
#include <limits.h>

static int	apply_cd(char **t)
{
	char	*ptr;

	if (!t[1])
	{
		if (!(ptr = get_envline("HOME", g_env)))
			return (-2);
	}
	else if (ft_strncmp(t[1], "-", 2) == 0)
	{
		if (!(ptr = get_envline("OLDPWD", g_env)))
			return (-3);
	}
	else
		ptr = t[1];
	return (chdir(ptr));
}

static int	change_environ(char *buf)
{
	char	buf2[PATH_MAX + 1];

	if (getcwd(buf2, PATH_MAX) == NULL)
		return (print_errors(ERR_GETCWD, ERR_GETCWD_STR, NULL));
	set_env_var("PWD", buf2, &g_env);
	set_env_var("OLDPWD", buf, &g_env);
	return (0);
}

int			case_cd(char **t)
{
	char			buf[PATH_MAX + 1];
	int				ret;
	struct	stat	infos;
	int				i;

	if (t[1])
	{
		i = ft_strlen(t[1]) - 1;
		if (t[1][i] == '/')
			t[1][i] = '\0';
		if (lstat(t[1], &infos) == -1)
			return (print_errors(ERR_NOEXIST, ERR_NOEXIST_STR, t[1]));
		if (!S_ISDIR(infos.st_mode))
			return (print_errors(ERR_NOTDIR, ERR_NOTDIR_STR, t[1]));
		if (access(t[1], F_OK) == 0 && access(t[1], X_OK) == -1)
			return (print_errors(ERR_ACCESS, ERR_ACCESS_STR, t[1]));
	}
	if (getcwd(buf, PATH_MAX) == NULL)
		return (print_errors(ERR_GETCWD, ERR_GETCWD_STR, NULL));
	ret = apply_cd(t);
	if (ret == 0 && change_environ(buf))
		return (ERR_MALLOC);
	else if (ret == -1)
		return (print_errors(ERR_CHDIR, ERR_CHDIR_STR, NULL));
	else if (ret == -2)
		return (print_errors(ERR_NOEXIST, ERR_NOEXIST_STR, "HOME"));// ?
	else if (ret == -3)
		return (print_errors(ERR_NO_OLDPWD, ERR_NO_OLDPWD_STR, t[1]));
	return (0);
}
