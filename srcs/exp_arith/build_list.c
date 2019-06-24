/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:21:16 by penzo             #+#    #+#             */
/*   Updated: 2019/06/24 11:21:20 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftsh.h"
#include "exp_arith.h"

static	void			put_lst_new(t_op **lst, t_op **new)
{
	if ((*lst)->right)
		put_lst_left((*lst), (*new));
	else
		put_lst_right((*lst), (*new));
	(*lst) = (*new);
}

static	int				check_prio(int tok)
{
	if (tok == tk_nb)
		return (1);
	if (tok == tk_varplus || tok == tk_plusvar
			|| tok == tk_varmin || tok == tk_minvar)
		return (2);
	if (tok == tk_add || tok == tk_sub)
		return (4);
	if (tok == tk_mult || tok == tk_div || tok == tk_mod)
		return (3);
	if (tok == tk_lesseq || tok == tk_moreeq
			|| tok == tk_less || tok == tk_more)
		return (5);
	if (tok == tk_eq || tok == tk_noteq)
		return (6);
	if (tok == tk_operand)
		return (7);
	if (tok == tk_operor)
		return (8);
	return (0);
}

static	void			put_lst_higher(t_op **lst, t_op **new)
{
	t_op	*tmp;

	tmp = (*lst);
	while ((*lst) && (*lst)->prev
			&& check_prio((*lst)->prev->token) <= check_prio((*new)->token))
	{
		tmp = (*lst);
		(*lst) = (*lst)->prev;
	}
	if (check_prio((*lst)->token) > check_prio((*new)->token))
		(*lst) = tmp;
	put_lst_back((*lst), (*new));
	(*lst) = (*lst)->prev;
}

t_op					*build_op_list(t_tok *tks)
{
	t_op				*new;
	t_op				*lst;
	unsigned	int		i;

	i = 0;
	lst = NULL;
	while (tks[i].token != 0)
	{
		if (!(new = create_op_link(tks[i].token, tks[i].value, tks[i])))
			clean_exit(1, 1);
		if (!(lst))
			lst = new;
		else if ((lst->token == tk_nb && new->token == tk_nb)
				|| (check_prio(lst->token) > check_prio(new->token)))
			put_lst_new(&lst, &new);
		else
			put_lst_higher(&lst, &new);
		i++;
	}
	return (lst);
}
