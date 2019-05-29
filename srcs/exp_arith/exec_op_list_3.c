#include "42sh.h"
#include "exp_arith.h"

long long		check_err_numbers(t_op *lst)
{
	if (lst->token == TK_NB && ((lst->left
					&& lst->left->token == TK_NB)
				|| (lst->right && lst->right->token == TK_NB)))
		return (1);
	return (0);
}

long long		not_tok_nb(t_op *lst, int *err, long long *nb, char ***vars)
{
	*nb = exec(lst, err, vars, 0, 0);
	if (*err != 0)
		return (*err);
	return (0);
}

long long		lonely_number(t_op *lst, char ***vars)
{
	long long nb;

	nb = 0;
	get_var_value(lst, &nb, vars);
	return (nb);
}

long long		return_set_err(int *err, int error)
{
	*err = error;
	return (0);
}
