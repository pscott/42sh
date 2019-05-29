#include "42sh.h"
#include "exp_arith.h"

static	long long	calc_bas(long long nb1, long long nb2, int token, int *err)
{
	if (token == TK_ADD)
		return (nb1 + nb2);
	if (token == TK_SUB)
		return (nb1 - nb2);
	if (token == TK_MULT)
		return (nb1 * nb2);
	if (token == TK_DIV)
	{
		if (nb2 == 0)
		{
			*err = 4;
			return (0);
		}
		return (nb1 / nb2);
	}
	if (token == TK_MOD)
		return (nb1 % nb2);
	return (0);
}

long long			calcul(long long nb1, long long nb2, int token, int *err)
{
	if (token >= TK_ADD && token <= TK_MOD)
		return (calc_bas(nb1, nb2, token, err));
	if (token == TK_LESSEQ)
		return ((nb1 <= nb2) ? 1 : 0);
	if (token == TK_MOREEQ)
		return ((nb1 >= nb2) ? 1 : 0);
	if (token == TK_LESS)
		return ((nb1 < nb2) ? 1 : 0);
	if (token == TK_MORE)
		return ((nb1 > nb2) ? 1 : 0);
	if (token == TK_EQ)
		return ((nb1 == nb2) ? 1 : 0);
	if (token == TK_NOTEQ)
		return ((nb1 != nb2) ? 1 : 0);
	if (token == TK_OPERAND)
		return ((nb1 && nb2) ? 1 : 0);
	if (token == TK_OPEROR)
		return ((nb1 || nb2) ? 1 : 0);
	return (0);
}

static	int			change_vars_value(char ***vars, t_op *lst, long long var)
{
	char	*ptr;

	if (!(ptr = ft_lltoa(var)))
		ERROR_MEM;
	set_env_var(lst->varname, ptr, vars);
	free(ptr);
	return (0);
}

int					get_var_value(t_op *lst, long long *nb, char ***vars)
{
	long long	var;
	char		*ptr;

	var = 0;
	if (lst->varid == -2)
		*nb = lst->value;
	else
	{
		if (lst->varid != -1)
		{
			if ((ptr = get_value_index(lst->varid, *vars)))
				*nb = (ft_atoll(ptr) + lst->beg) * lst->value;
			var = ft_atoll(ptr) + lst->beg + lst->end;
		}
		else
		{
			*nb = lst->beg * lst->value;
			var = *nb + lst->end;
		}
		if (lst->varid > -1 || (lst->varid == -1 && var != 0))
			if (change_vars_value(vars, lst, var))
				return (1);
	}
	return (0);
}

long long			double_numbers(t_op *lst, int *err, char ***vars)
{
	long long nb;

	if (lst)
		get_var_value(lst, &nb, vars);
	*err = 3;
	return (0);
}
