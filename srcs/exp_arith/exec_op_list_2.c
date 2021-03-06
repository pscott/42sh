#include "ftsh.h"
#include "env.h"
#include "exp_arith.h"

static	long long	calc_bas(long long nb1, long long nb2, int token, int *err)
{
	if (token == tk_add)
		return (nb1 + nb2);
	if (token == tk_sub)
		return (nb1 - nb2);
	if (token == tk_mult)
		return (nb1 * nb2);
	if (token == tk_div || token == tk_mod)
	{
		if (nb2 == 0)
		{
			*err = 4;
			return (0);
		}
		if (token == tk_div)
			return (nb1 / nb2);
		else
			return (nb1 % nb2);
	}
	return (0);
}

long long			calcul(long long nb1, long long nb2, int token, int *err)
{
	if (token >= tk_add && token <= tk_mod)
		return (calc_bas(nb1, nb2, token, err));
	if (token == tk_lesseq)
		return ((nb1 <= nb2) ? 1 : 0);
	if (token == tk_moreeq)
		return ((nb1 >= nb2) ? 1 : 0);
	if (token == tk_less)
		return ((nb1 < nb2) ? 1 : 0);
	if (token == tk_more)
		return ((nb1 > nb2) ? 1 : 0);
	if (token == tk_eq)
		return ((nb1 == nb2) ? 1 : 0);
	if (token == tk_noteq)
		return ((nb1 != nb2) ? 1 : 0);
	if (token == tk_operand)
		return ((nb1 && nb2) ? 1 : 0);
	if (token == tk_operor)
		return ((nb1 || nb2) ? 1 : 0);
	return (0);
}

static	int			change_vars_value(t_vars *vars, t_op *lst, long long var)
{
	char	*ptr;

	if (!(ptr = ft_lltoa(var)))
		clean_exit(1, MALLOC_ERR);
	set_env_var(lst->varname, ptr, &vars->shell_vars);
	if (get_envline_index(lst->varname, vars->env_vars) != -1)
		set_env_var(lst->varname, ptr, &vars->env_vars);
	if (get_envline_index(lst->varname, vars->env_exported) != -1)
		set_env_var(lst->varname, ptr, &vars->env_exported);
	free(ptr);
	return (0);
}

int					get_var_value(t_op *lst, long long *nb, t_vars *vars)
{
	long long	var;
	char		*ptr;

	if (lst->varid == -2)
		*nb = lst->value;
	else
	{
		if (lst->varid != -1)
		{
			if ((ptr = get_value_index(lst->varid, vars->shell_vars)))
				*nb = (ft_atoll(ptr) + lst->beg) * lst->value;
			var = ft_atoll(ptr) + lst->beg + lst->end;
		}
		else
		{
			*nb = lst->beg * lst->value;
			var = *nb + lst->end;
		}
		if ((lst->varid > -1 || (lst->varid == -1 && var != 0))
				&& lst->end != 0)
			if (change_vars_value(vars, lst, var))
				return (1);
	}
	return (0);
}

long long			double_numbers(t_op *lst, int *err, t_vars *vars)
{
	long long nb;

	if (lst)
		get_var_value(lst, &nb, vars);
	*err = 3;
	return (0);
}
