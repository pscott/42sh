#include "builtins.h"

int				check_test_errors(char **argv, int ac)
{
	int		ret;

	ret = 0;
	if (ac > 4)
	{
		ft_dprintf(2, "42sh: test: too many arguments\n");
		ret = 2;
	}
	else if (ac == 3 && get_unary_option(argv[1]) == -1)
	{
		ft_dprintf(2, "42sh: test: %s: unary operator expected\n", argv[1]);
		ret = 2;
	}
	else if (ac == 4 && get_binary_option(argv[2]) == -1)
	{
		ft_dprintf(2, "42sh: test: %s: binary operator expected\n", argv[2]);
		ret = 2;
	}
	return (ret);
}

static int		check_additional_unary_values(char *path, int uflag)
{
	if (uflag == op_p)
		return (test_flag_p(path));
	if (uflag == op_r)
		return (test_flag_r(path));
	if (uflag == op_cap_s)
		return (test_flag_cap_s(path));
	if (uflag == op_s)
		return (test_flag_s(path));
	if (uflag == op_u)
		return (test_flag_u(path));
	if (uflag == op_w)
		return (test_flag_w(path));
	if (uflag == op_x)
		return (test_flag_x(path));
	if (uflag == op_z)
		return (test_flag_z(path));
	return (0);
}

int				check_unary_values(char *path, int uflag)
{
	if (uflag == op_b)
		return (test_flag_b(path));
	if (uflag == op_c)
		return (test_flag_c(path));
	if (uflag == op_d)
		return (test_flag_d(path));
	if (uflag == op_e)
		return (test_flag_e(path));
	if (uflag == op_f)
		return (test_flag_f(path));
	if (uflag == op_g)
		return (test_flag_g(path));
	if (uflag == op_cap_l)
		return (test_flag_cap_l(path));
	return (check_additional_unary_values(path, uflag));
}

int				check_binary_values(char *right, char *left, int biflag,
		int *result)
{
	if (biflag == op_eq)
		return (test_flag_eq(right, left, result));
	else if (biflag == op_ne)
		return (test_flag_ne(right, left, result));
	else if (biflag == op_ge)
		return (test_flag_ge(right, left, result));
	else if (biflag == op_lt)
		return (test_flag_lt(right, left, result));
	else if (biflag == op_le)
		return (test_flag_le(right, left, result));
	else if (biflag == op_sym_eq)
		return (test_flag_sym_eq(right, left, result));
	else if (biflag == op_sym_noteq)
		return (test_flag_sym_noteq(right, left, result));
	return (2);
}
