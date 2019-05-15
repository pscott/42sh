#include "42sh.h"
#include "builtins.h"

int				builtin_exit_error(int errno, char *s)
{
	if (errno == ARGS_NB)
	{
		ft_dprintf(STDERR_FILENO,"exit: too many arguments");
		print_line();
		return (0);
	}
	else if (errno == ARG_NOT_DIGIT)
	{
		ft_dprintf(STDERR_FILENO, "exit: numeric argument required: %s", s);
		print_line();
		return (1);
	}
	return (EXIT_SUCCESS);
}

static void		builtin_exit(int exitno)
{
	clean_exit(exitno);
}

int				case_exit(char **arr)
{
	int			i;
	int			ret;
	int			count;

	i = 0;
	ret = 0;
	count = 0;
	if (!arr || !arr[1])
		builtin_exit(0);
	if (arr[2])
		return (builtin_exit_error(ARGS_NB, NULL));
	if (arr[1][i] == '-')
		i++;
	while (arr[1][i])
	{
		if (!ft_isdigit(arr[1][i]))
			return (builtin_exit_error(ARG_NOT_DIGIT, arr[1]));
		if (arr[1][i] != 0)
			++count;
		i++;
	}
	if (count > 19)
		return (builtin_exit_error(ARG_NOT_DIGIT, NULL));
	ret = ft_atoi(arr[1]);
	builtin_exit(ret);
	return (1);
}
