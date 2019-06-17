#include "builtins.h"
#include <sys/stat.h>

static int		free_newargv(char **newargv, int ret)
{
	ft_free_ntab(newargv);
	return (ret);
}

static int		return_test_inv(int ret, int inv)
{
	if (inv % 2)
		return (!ret);
	return (ret);
}

static int		case_no_arg(char **newargv, int ac, int inv)
{
	if ((ac == 1 && !newargv[ac]) || !newargv[ac - 1][0])
		return (free_newargv(newargv, return_test_inv(1, inv)));
	return (free_newargv(newargv, return_test_inv(0, inv)));
}

static void		init_ints(int *a, int *b, int *c)
{
	*a = 0;
	*b = 0;
	*c = 0;
}

int				case_test(char **argv)
{
	int		ret;
	int		ac;
	int		flag;
	int		inv;
	char	**newargv;

	init_ints(&ac, &flag, &inv);
	newargv = check_inv(argv, &inv);
	while (newargv[ac])
		ac++;
	if ((ret = check_test_errors(newargv, ac)))
		return (free_newargv(newargv, ret));
	if (ac == 1 || ac == 2)
		return (case_no_arg(newargv, ac, inv));
	else if (ac == 3)
		flag = get_unary_option(newargv[1]);
	else if (ac == 4)
		flag = get_binary_option(newargv[2]);
	if (flag <= op_z)
		ret = check_unary_values(newargv[2], flag);
	else if (flag > op_z)
		if (check_binary_values(newargv[1], newargv[3], flag, &ret))
			return (free_newargv(newargv, 2));
	return (free_newargv(newargv, return_test_inv(ret, inv)));
}
