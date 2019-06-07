#include "ftsh.h"
#include "exp_arith.h"

static	long long	case_nb1(t_op *lst, long long *nb1, int *err, char ***vars)
{
	if (lst->left)
		get_var_value(lst->left, nb1, vars);
	if (lst->left && lst->left->token == TK_NB
			&& (lst->left->left || lst->left->right))
	{
		*err = 3;
		return (1);
	}
	return (0);
}

static	long long	case_nb2(t_op *lst, long long *nb2, int *err, char ***vars)
{
	if (lst->right)
		get_var_value(lst->right, nb2, vars);
	if (lst->right && lst->right->token == TK_NB
			&& (lst->right->left || lst->right->right))
	{
		*err = 3;
		return (1);
	}
	return (0);
}

long long			exec(t_op *lst, int *err, char ***vars)
{
	long long nb1;
	long long nb2;

	initialize_long_long(&nb1, &nb2);
	if (!lst->left && !lst->right)
		return (lonely_number(lst, vars));
	else if (check_err_numbers(lst))
		return (double_numbers(lst, err, vars));
	if (lst->token == TK_OPERAND || lst->token == TK_OPEROR)
		return (oper_and_or(lst, err, vars));
	if (lst->left && lst->left->token != TK_NB
			&& not_tok_nb(lst->left, err, &nb1, vars))
		return (0);
	else if (lst->left && lst->left->token == TK_NB)
		if (case_nb1(lst, &nb1, err, vars))
			return (0);
	if (lst->token > TK_MINVAR && (!lst->right || !lst->left))
		return (return_set_err(err, 5));
	if (lst->right && lst->right->token != TK_NB
			&& not_tok_nb(lst->right, err, &nb2, vars))
		return (0);
	else if (lst->right && lst->right->token == TK_NB)
		if (case_nb2(lst, &nb2, err, vars))
			return (0);
	return (calcul(nb1, nb2, lst->token, err));
}

long long			oper_and_or(t_op *lst, int *err, char ***vars)
{
	if (!lst->left || !lst->right)
		return (return_set_err(err, 5));
	if (lst->token == TK_OPERAND)
	{
		if (exec(lst->left, err, vars))
		{
			if (exec(lst->right, err, vars))
				return (1);
		}
	}
	else
	{
		if (exec(lst->left, err, vars))
			return (1);
		else if (exec(lst->right, err, vars))
			return (1);
	}
	return (0);
}

/*
**	Ast execution : recursively handles vars and ops, increments the vars
*/

int					exec_op_list(t_op *lst, char ***vars, long long *result)
{
	int			error;

	error = 0;
	while (lst->prev)
		lst = lst->prev;
	*result = exec(lst, &error, vars);
	return (error);
}
