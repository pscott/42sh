#include "builtins.h"
#include "env.h"
#include "errors.h"
#include <sys/stat.h>
#include <limits.h>

static int		check_cd_usage(char **argv)
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
	while (argv[i++])
		k++;
	if (k > 1)
	{
		ft_dprintf(2, SHELL_NAME ": cd: too many arguments\n");
		return (1);
	}
	return (0);
}

static int		is_error(char *dest)
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

static char		*get_dest_path(char *arg, char ***env, int *display)
{
	char	*dest;

	if (!(arg))
		dest = get_directory("HOME", (const char**)*env);
	else if (ft_strncmp(arg, "-", 2) == 0)
	{
		if ((dest = get_directory("OLDPWD", (const char**)*env)))
			*display = 2;
	}
	else if (arg[0] == '/')
	{
		if (!(dest = ft_strdup(arg)))
			clean_exit(1, 1);
	}
	else
		dest = relative_directory(arg, (const char**)*env, display);
	return (dest);
}

/*
**	Returns 0 if it succesfully managed to change directory ; else returns
**	the corresponding error value.
*/

int				case_cd(char **argv, char ***env)
{
	char			*dest;
	int				ret;
	char			opt;
	int				pos;
	int				display;

	display = 0;
	if ((opt = get_cd_options(argv, &pos)) == -1)
		return (1);
	if (check_cd_usage(argv))
		return (1);
	dest = get_dest_path(argv[pos], env, &display);
	if (!dest)
		return (1);
	if (opt != 'P')
		format_path_string(&dest);
	if ((ret = is_error(dest)) != 0)
	{
		ft_strdel(&dest);
		return (ret);
	}
	else
		return (change_environ(dest, env, opt, display));
}
