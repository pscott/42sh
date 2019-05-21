#include "42sh.h"
#include "builtins.h"

/*
**	Unsetenv accepts 1 argument or more, but not 0
*/

int		check_usage_unsetenv(char **argv)
{
	int		i;

	i = 0;
	while (argv[i])
		i++;
	if (i < 2)
	{
		ft_putstr_fd("usage: unsetenv [env name]", 2);
		ft_putchar_fd('\n', 2);
		return (1);
	}
	return (0);
}

/*
**	Unsetenv builtin : remove a variable from the env array
*/

int			case_unsetenv(char **argv, t_vars *vars)
{
	int		i;

	i = 1;
	if (check_usage_unsetenv(argv))
		return (1);
	while (argv[i])
	{
		unset_env_var(argv[i], &vars->env_vars);
		i++;
	}
	return (0);
}
