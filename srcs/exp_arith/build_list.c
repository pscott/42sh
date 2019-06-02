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
	if (tok == TK_NB)
		return (1);
	if (tok == TK_VARPLUS || tok == TK_PLUSVAR
			|| tok == TK_VARMIN || tok == TK_MINVAR)
		return (2);
	if (tok == TK_ADD || tok == TK_SUB)
		return (4);
	if (tok == TK_MULT || tok == TK_DIV || tok == TK_MOD)
		return (3);
	if (tok == TK_LESSEQ || tok == TK_MOREEQ
			|| tok == TK_LESS || tok == TK_MORE)
		return (5);
	if (tok == TK_EQ || tok == TK_NOTEQ)
		return (6);
	if (tok == TK_OPERAND)
		return (7);
	if (tok == TK_OPEROR)
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
	t_op				*prout;
	unsigned	int		i;

	i = 0;
	lst = NULL;
	while (tks[i].token != 0)
	{
		if (!(new = create_op_link(tks[i].token, tks[i].value, tks[i])))
			ERROR_MEM;
		if (!(lst))
			lst = new;
		else if ((lst->token == TK_NB && new->token == TK_NB)
				|| (check_prio(lst->token) > check_prio(new->token)))
			put_lst_new(&lst, &new);
		else
			put_lst_higher(&lst, &new);
		prout = lst;
		i++;
	}
	return (lst);
}
