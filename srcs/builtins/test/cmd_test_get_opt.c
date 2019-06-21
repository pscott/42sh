#include "builtins.h"

static int		get_additional_unary_option(char *arg)
{
	if (!ft_strcmp(arg, "-r"))
		return (op_r);
	if (!ft_strcmp(arg, "-S"))
		return (op_cap_s);
	if (!ft_strcmp(arg, "-s"))
		return (op_s);
	if (!ft_strcmp(arg, "-u"))
		return (op_u);
	if (!ft_strcmp(arg, "-w"))
		return (op_w);
	if (!ft_strcmp(arg, "-x"))
		return (op_x);
	if (!ft_strcmp(arg, "-z"))
		return (op_z);
	return (-1);
}

int				get_unary_option(char *arg)
{
	if (!ft_strcmp(arg, "-b"))
		return (op_b);
	if (!ft_strcmp(arg, "-c"))
		return (op_c);
	if (!ft_strcmp(arg, "-d"))
		return (op_d);
	if (!ft_strcmp(arg, "-e"))
		return (op_e);
	if (!ft_strcmp(arg, "-f"))
		return (op_f);
	if (!ft_strcmp(arg, "-g"))
		return (op_g);
	if (!ft_strcmp(arg, "-L"))
		return (op_cap_l);
	if (!ft_strcmp(arg, "-p"))
		return (op_p);
	return (get_additional_unary_option(arg));
}

int				get_binary_option(char *arg)
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
	return (-1);
}
