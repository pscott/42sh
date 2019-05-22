#include "42sh.h"
#include "builtins.h"

static void		builtin_exit_error(int errno, char *s)
{
	if (errno == args_nb)
		ft_dprintf(STDERR_FILENO,"exit: too many arguments\n");
	else if (errno == arg_not_digit)
		ft_dprintf(STDERR_FILENO, "exit: numeric argument required: %s\n", s);
}


static int	ft_atol(const char *str)
{
	char					*s;
	unsigned long long int	i;
	int						neg;
	unsigned long long int	rep;

	s = (char *)str;
	i = 0;
	while (s[i] == '\n' || s[i] == '\t' || s[i] == '\r' || s[i] == '\v'
		|| s[i] == '\f' || s[i] == ' ')
		i++;
	neg = 1;
	if (s[i] == '-' || s[i] == '+')
		if (s[i++] == '-')
			neg = -1;
	rep = 0;
	while (s[i] >= '0' && s[i] <= '9' && s[i])
	{
		rep = 10 * rep + (s[i++] - '0');
		if (rep > 9223372036854775807)
		{
			return (0);
		}
	}
	return ((int)rep * (int)neg);
}

static int		word_is_num(char *str)
{
	unsigned int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int		is_zero(char *str)
{
	unsigned int i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] != '0')
			return (0);
		i++;
	}
	return (1);
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
	if (isatty(STDIN_FILENO))
		ft_dprintf(0, "exit\n");
}
/*
**	Exit builtin. Does NOT call exit(3). Returns 0 if exit(3) should be called
**	else returns 1. Sets the *exitno parameter to the corresponding value.
*/

int				case_exit(char **argv, int *exitno)
{
	if (!argv || !argv[1])
	{
		*exitno = 0;
		return (1);
	}
	if (!word_is_num(argv[1]))
	{
		builtin_exit_error(arg_not_digit, argv[1]);
		*exitno = 2;
		return (1);
	}
	else if (argv[2])
	{
		builtin_exit_error(args_nb, NULL);
		*exitno = 1;
		return (0);
	}
	else if (is_zero(argv[1]))
	{
		*exitno = 0;
		return (1);
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
