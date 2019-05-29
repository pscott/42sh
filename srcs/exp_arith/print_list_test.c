#include "42sh.h"
#include "exp_arith.h"

static	void	recurs_print_lst(t_op *lst, int i, int right)
{
	int k;

	k = 0;
	if (!lst)
		return ;
	ft_printf("| parent == %c", lst->parent);
	ft_printf("| value == %lld", lst->value);
	ft_printf("| token == %d", lst->token);
	ft_printf(" | level == %d", i);
	if (right == 1)
		ft_printf(" | RIGHT");
	else if (right == 0)
		ft_printf(" | LEFT");
	else
		ft_printf(" | ROOT");
	if (lst->varname)
		ft_printf(" | varname == %s", lst->varname);
	ft_printf("\n");
	recurs_print_lst(lst->left, i + 1, 0);
	recurs_print_lst(lst->right, i + 1, 1);
}

void			print_list(t_op *lst)
{
	while (lst && lst->prev)
		lst = lst->prev;
	recurs_print_lst(lst, 0, -1);
}

void		print_dirty(t_tok **tokens)
{
	int l;

	l = 0;
	printf("DIRTY TOKENS :\n");
	while ((*tokens)[l].token != 0)
	{
		printf("Value = %lld | Token = %d", (*tokens)[l].value, (*tokens)[l].token);
		if ((*tokens)[l].varid != -2)
			printf(" | Varid = %d", (*tokens)[l].varid);
		printf("\n");
		l++;
	}
	printf("---------------------\n");
}

void		print_clean(t_tok **tokens)
{
	int l;

	l = 0;
	printf("CLEAN TOKENS :\n");
	while ((*tokens)[l].token != 0)
	{
		printf("Value = %lld | Token = %d", (*tokens)[l].value, (*tokens)[l].token);
		if ((*tokens)[l].varid != -2)
		{
			printf(" | Varid = %d", (*tokens)[l].varid);
			printf(" | End = %d | Beg = %d", (*tokens)[l].end, (*tokens)[l].beg);
		}
		printf("\n");
		l++;
	}
	printf("---------------------\n");
}
