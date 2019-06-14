#include "builtins.h"
#include "env.h"
#include "errors.h"
#include <sys/stat.h>
#include <limits.h>

/*
**	Updates the pwd and oldpwd env variables, then calles chdir.
**	Returns 0 on success, else returns 1.
*/

static int	change_environ(char *new_wd, char ***env, int opt, int cdpath)
{
	char			*old_pwd;
	char			*pwd;
	int				ret;
	char buf[1000];

	ft_bzero(&buf, 1000);

	ft_initialize_str(&pwd, &old_pwd, NULL, NULL);
	if ((old_pwd = get_directory("PWD", (const char**)*env)))
	{
		set_env_var("OLDPWD", old_pwd, env);
		ft_strdel(&old_pwd);
	}
	if ((ret = chdir(new_wd)) == -1)
		print_errors(ERR_CHDIR, ERR_CHDIR_STR, new_wd);
	if (opt == 'L' || opt == 0)
	{
		if (!(pwd = strdup(new_wd)))
			clean_exit(1, 1);
	}
	else
	{
		if (!(pwd = getcwd(NULL, 0)))
			return (print_errors(ERR_GETCWD, ERR_GETCWD_STR, NULL));
	}
	set_env_var("PWD", pwd, env);
	if (cdpath)
		ft_printf("%s\n", pwd);
	ft_strdel(&new_wd);
	ft_strdel(&pwd);
	return (ret);
}

static int	check_cd_usage(char **argv)
{
	int		i;
	int		k;

	i = 1;
	k = 0;
	while (argv[i] && argv[i][0] == '-'
			&& !(argv[i][0] == '-' && argv[i][1] == '\0'))
	{
		if (!ft_strcmp(argv[i], "--"))
		{
			i++;
			break ;
		}
		i++;
	}
	while (argv[i])
	{
		i++;
		k++;
	}
	if (k > 1)
	{
		ft_dprintf(2, SHELL_NAME ": cd: too many arguments\n");
		return (1);
	}
	return (0);
}

static int	is_error(char *dest)
{
	struct stat		infos;

	if (!dest)
		return (1);
	if (stat(dest, &infos) == -1)
		return (print_errors(ERR_NOEXIST, ERR_NOEXIST_STR, dest));
	else if (!S_ISDIR(infos.st_mode))
		return (print_errors(ERR_NOTDIR, ERR_NOTDIR_STR, dest));
	else if (access(dest, F_OK) == 0 && access(dest, X_OK) == -1)
		return (print_errors(ERR_PERM, ERR_PERM_STR, dest));
	else
		return (0);
}

static int	del_and_return_cd(char **dest, int ret)
{
	ft_strdel(dest);
	return (ret);
}

/*
**	Returns 0 if it succesfully managed to change directory ; else returns
**	the corresponding error value.
*/

int			case_cd(char **argv, char ***env)
{
	char			*dest;
	int				ret;
	char			opt;
	int				pos;
	int				cdpath;

	ft_print_ntab(argv);
	cdpath = 0;
	if ((opt = get_cd_options(argv, &pos)) == -1)
		return (1);
	if (check_cd_usage(argv))
		return (1);
	if (!(argv[pos]))
		dest = get_directory("HOME", (const char**)*env);
	else if (ft_strncmp(argv[pos], "-", 2) == 0)
	{
		if ((dest = get_directory("OLDPWD", (const char**)*env)))
			ft_dprintf(1, "%s\n", dest);
	}
	else if (argv[pos][0] == '/')
	{
		if (!(dest = ft_strdup(argv[pos])))
			clean_exit(1, 1);
	}
	else
		dest = relative_directory(argv[pos], (const char**)*env, opt, &cdpath);
	printf("|%s|\n", argv[pos]);
	ft_printf("Before format : %s\n", dest);
	dest = format_path_string(dest);
	ft_printf("After format : %s\n", dest);

	if ((ret = is_error(dest)) != 0)
		return (del_and_return_cd(&dest, ret));
	else
		return (change_environ(dest, env, opt, cdpath));
}
