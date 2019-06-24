/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:21:16 by penzo             #+#    #+#             */
/*   Updated: 2019/06/24 11:21:20 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftsh.h"
#include "exp_arith.h"

int				free_lst_link(t_op *lst, int err)
{
	if (lst)
		free(lst);
	return (err);
}

static	void	recurs_free_lst(t_op *lst)
{
	t_op *right;
	t_op *left;

	if (!lst)
		return ;
	right = lst->right;
	left = lst->left;
	if (lst->varname)
		free(lst->varname);
	free(lst);
	recurs_free_lst(left);
	recurs_free_lst(right);
}

int				free_lst(t_op *lst, int err)
{
	while (lst && lst->prev)
		lst = lst->prev;
	recurs_free_lst(lst);
	return (err);
}
