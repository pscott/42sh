#include "builtins.h"

static void		builtin_exit_error(int errno, char *s)
{
	if (errno == args_nb)
		ft_dprintf(STDERR_FILENO, "exit: too many arguments\n");
	else if (errno == arg_not_digit)
		ft_dprintf(STDERR_FILENO, "exit: numeric argument required: %s\n", s);
}

int				get_exit_value(char **argv)
{
	int	exitno;

	if (!argv || !argv[1])
		return (0);
	if (!word_is_num(argv[1]))
		return (2);
	if (is_zero(argv[1]))
		return (0);
	else
	{
		if ((exitno = ft_atol(argv[1])) == 0)
			return (2);
		return (exitno);
	}
}

void			print_exit(void)
{
	ft_dprintf(TERM_FD, "exit\n");
}

static int		check_validity_args(char **argv, int *exitno)
{
	int			ret;
	t_vars		*vars;

	ret = 0;
	vars = get_vars(NULL);
	if (!argv || !argv[1])
	{
		ret = 1;
		*exitno = vars->cmd_value;
	}
	else if (!word_is_num(argv[1]))
	{
		ret = 1;
		builtin_exit_error(arg_not_digit, argv[1]);
		*exitno = 2;
	}
	else if (is_zero(argv[1]))
	{
		ret = 1;
		*exitno = 0;
	}
	else
		*exitno = get_exit_value(argv);
	return (ret);
}

/*
**	Exit builtin. Does NOT call exit(3). Returns 0 if exit(3) should be called
**	else returns 1. Sets the *exitno parameter to the corresponding value.
*/

int				case_exit(char **argv, int *exitno)
{
	int			ret;

	if ((ret = check_validity_args(argv, exitno)) == 1)
		return (1);
	else if (argv[2])
	{
		builtin_exit_error(args_nb, NULL);
		*exitno = 1;
		return (0);
	}
	else
	{
		*exitno = ft_atol(argv[1]);
		if (*exitno == 0)
		{
			builtin_exit_error(arg_not_digit, argv[1]);
			*exitno = 2;
		}
		return (1);
	}
}
