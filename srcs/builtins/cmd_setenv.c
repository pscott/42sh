#include "builtins.h"
#include "env.h"

/*
**	Few errors that csh uses
*/

static int	print_errors_setenv(int err)
{
	if (err == 2)
	{
		ft_dprintf(STDERR_FILENO, "setenv: Variable name must begin");
		ft_dprintf(STDERR_FILENO, " with a letter\n");
	}
	if (err == 3)
	{
		ft_dprintf(STDERR_FILENO, "setenv: Variable name must contain");
		ft_dprintf(STDERR_FILENO, " alphanumeric characters\n");
	}
	return (1);
}

/*
**	Errors : var_name begins with a number, var_name does not only contain
**	alphanumeric characters
*/

static int	check_errors_setenv(char **argv)
{
	int		i;

	i = 0;
	if (ft_isdigit(argv[1][0]))
		return (2);
	while (argv[1][i])
	{
		if (!ft_isalnum(argv[1][i]) && argv[1][i] != '_')
			return (3);
		i++;
	}
	return (0);
}

/*
**	Setenv accepts only 1 or 2 argument(s), csh also prints the env
**	in case setenv has no argument
*/

static int	check_usage_setenv(char **argv)
{
	int		i;

	i = 0;
	while (argv[i])
		i++;
	if (i > 3 || i < 2)
	{
		ft_dprintf(STDERR_FILENO, "usage: setenv VAR [VALUE]\n");
		return (1);
	}
	return (0);
}

/*
**	Setenv buitin : add or modify a variable in the env array
*/

int			case_setenv(char **argv, char ***env)
{
	int ret;

	if (check_usage_setenv(argv))
		return (1);
	if ((ret = check_errors_setenv(argv)))
		return (print_errors_setenv(ret));
	set_env_var(argv[1], argv[2], env);
	return (0);
}
