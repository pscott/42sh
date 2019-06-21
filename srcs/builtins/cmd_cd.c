#include "builtins.h"
#include "env.h"
#include "errors.h"
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

static char		*get_dest_path(char *arg, char ***env, int *display, char opt)
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
		dest = relative_directory(arg, (const char**)*env, display, opt);
	return (dest);
}

static int		check_path_too_long(char *str)
{
	size_t	i;

	i = 0;
	if (str)
		i = ft_strlen(str);
	if (i > PATH_MAX)
	{
		ft_dprintf(2, "%s: cd: %s: File name too long\n", SHELL_NAME, str);
		return (1);
	}
	return (0);
}

static int		del_and_return(char **todel, int ret)
{
	ft_strdel(todel);
	return (ret);
}

/*
**	Returns 0 if it succesfully managed to change directory ; else returns
**	the corresponding error value.
*/

int				case_cd(char **argv, char ***env)
{
	char			*dest;
	char			opt;
	int				pos;
	int				display;

	display = 0;
	if (check_cd_usage(argv))
		return (1);
	if ((opt = get_cd_options(argv, &pos)) == -1)
		return (1);
	dest = get_dest_path(argv[pos], env, &display, opt);
	if (!dest)
		return (1);
	if (opt != 'P')
		format_path_string(&dest);
	if (check_path_too_long(dest) || (opt != 'P'
				&& check_full_access(&dest, argv[pos])))
		return (del_and_return(&dest, 1));
	else
		return (change_environ(dest, env, opt, display));
}
