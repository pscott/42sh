#include "42sh.h"
#include "exp_arith.h"

void	put_lst_right(t_op *lst, t_op *new)
{
	if (!lst || !new)
		return ;
	new->parent = 'r';
	lst->right = new;
	new->prev = lst;
}

void	put_lst_left(t_op *lst, t_op *new)
{
	if (!lst || !new)
		return ;
	new->parent = 'l';
	lst->left = new;
	new->prev = lst;
}

/*
**	If the priority of the new token is higher than the current token in the
**	ast, it's necessary to put it back (higher in the tree)
*/

void	put_lst_back(t_op *lst, t_op *new)
{
	t_op *tmp;

	if (!lst || !new)
		return ;
	tmp = lst->prev;
	if (!tmp)
	{
		new->left = lst;
		lst->prev = new;
		lst->parent = 'l';
	}
	else
	{
		lst->prev = new;
		new->left = lst;
		new->prev = tmp;
		if (lst->parent == 'l')
			tmp->left = new;
		else
			tmp->right = new;
	}
}
