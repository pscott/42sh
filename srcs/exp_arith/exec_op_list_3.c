/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_op_list_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:21:16 by penzo             #+#    #+#             */
/*   Updated: 2019/06/24 11:21:20 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftsh.h"
#include "exp_arith.h"

long long		check_err_numbers(t_op *lst)
{
	if (lst->token == tk_nb && ((lst->left
					&& lst->left->token == tk_nb)
				|| (lst->right && lst->right->token == tk_nb)))
		return (1);
	return (0);
}

long long		not_tok_nb(t_op *lst, int *err, long long *nb, char ***vars)
{
	*nb = exec(lst, err, vars);
	if (*err != 0)
		return (*err);
	return (0);
}

long long		lonely_number(t_op *lst, int *err, char ***vars)
{
	long long nb;

	nb = 0;
	if (lst->token != tk_nb)
	{
		*err = 5;
		return (0);
	}
	get_var_value(lst, &nb, vars);
	return (nb);
}

long long		return_set_err(int *err, int error)
{
	*err = error;
	return (0);
}

void			initialize_long_long(long long *n1, long long *n2)
{
	*n1 = 0;
	*n2 = 0;
}
