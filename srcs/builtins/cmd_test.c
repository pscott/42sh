#include "builtins.h"
#include <sys/stat.h>

static int		get_unary_option(char *arg)
{
	if (!ft_strcmp(arg, "-b"))
		return (op_b);
	else if (!ft_strcmp(arg, "-c"))
		return (op_c);
	else if (!ft_strcmp(arg, "-d"))
		return (op_d);
	else if (!ft_strcmp(arg, "-e"))
		return (op_e);
	else if (!ft_strcmp(arg, "-f"))
		return (op_f);
	else if (!ft_strcmp(arg, "g"))
		return (op_g);
	else if (!ft_strcmp(arg, "-L"))
		return (op_cap_l);
	else if (!ft_strcmp(arg, "-p"))
		return (op_p);
	else if (!ft_strcmp(arg, "-r"))
		return (op_r);
	else if (!ft_strcmp(arg, "-S"))
		return (op_cap_s);
	else if (!ft_strcmp(arg, "-s"))
		return (op_s);
	else if (!ft_strcmp(arg, "-u"))
		return (op_u);
	else if (!ft_strcmp(arg, "-w"))
		return (op_w);
	else if (!ft_strcmp(arg, "-x"))
		return (op_x);
	else if (!ft_strcmp(arg, "-z"))
		return (op_z);
	return (-1);
}

static int		get_binary_option(char *arg)
{
	if (!ft_strcmp(arg, "="))
		return (op_sym_eq);
	else if (!ft_strcmp(arg, "!="))
		return (op_sym_noteq);
	else if (!ft_strcmp(arg, "-eq"))
		return (op_eq);
	else if (!ft_strcmp(arg, "-ne"))
		return (op_ne);
	else if (!ft_strcmp(arg, "-ge"))
		return (op_ge);
	else if (!ft_strcmp(arg, "-lt"))
		return (op_lt);
	else if (!ft_strcmp(arg, "-le"))
		return (op_le);
//	else if (!ft_strcmp(arg, "!"))
//		return (op_mark);
	return (-1);
}

static int		check_test_errors(char **argv, int ac)
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
//	else if (ac == 4 && (check_number(argv[1]) || check_number(argv[3])))
//		ft_dprintf(2, "42sh: test: %s: integer expression expected\n", str);
	return (ret);
}

static int		check_unary_values(char *path, int uflag, int *result)
{
	if (uflag == op_b)
		return (test_flag_b(path, result));
	else if (uflag == op_c)
		return (test_flag_c(path, result));
	else if (uflag == op_d)
		return (test_flag_d(path, result));
	else if (uflag == op_e)
		return (test_flag_e(path, result));
	else if (uflag == op_f)
		return (test_flag_f(path, result));
	else if (uflag == op_g)
		return (test_flag_g(path, result));
	else if (uflag == op_cap_l)
		return (test_flag_cap_l(path, result));
	else if (uflag == op_p)
		return (test_flag_p(path, result));
	else if (uflag == op_r)
		return (test_flag_r(path, result));
	else if (uflag == op_cap_s)
		return (test_flag_cap_s(path, result));
	else if (uflag == op_s)
		return (test_flag_s(path, result));
	else if (uflag == op_u)
		return (test_flag_u(path, result));
	else if (uflag == op_w)
		return (test_flag_w(path, result));
	else if (uflag == op_x)
		return (test_flag_x(path, result));
	else if (uflag == op_z)
		return (test_flag_z(path, result));
	return (0);
}

static int		check_binary_values(char *right, char *left, int biflag,
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
//	else if (biflag == op_sym_mark)
//		return (test_flag_sym_mark(right, left, result));
	return (2);
}

int				case_test(char **argv)
{
	int		ret;
	int		ac;
	int		uflag;
	int		biflag;

	ac = 0;
	uflag = 0;
	biflag = 0;
	while (argv[ac])
		ac++;
	if ((ret = check_test_errors(argv, ac)))
		return (ret);
	if (ac == 3)
		uflag = get_unary_option(argv[1]);
	else if (ac == 4)
		biflag = get_binary_option(argv[2]);
	if (uflag)
	{
		if (check_unary_values(argv[2], uflag, &ret) == 2)
			return (2);
	}
	else if (biflag)
		check_binary_values(argv[1], argv[3], biflag, &ret);
	return (ret);
}
