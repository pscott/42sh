#include "ftsh.h"
#include "exp_arith.h"

int		init_toks_clean(t_tok *d, t_tok **c)
{
	int k;

	k = 0;
	if (!(*c = (t_tok*)malloc(sizeof(t_tok) * (get_tok_len(d) + 1))))
		clean_exit(1, 1);
	while (k <= get_tok_len(d))
	{
		(*c)[k].token = 0;
		(*c)[k].value = 0;
		(*c)[k].varid = -2;
		(*c)[k].varname = NULL;
		(*c)[k].beg = 0;
		(*c)[k].end = 0;
		k++;
	}
	return (0);
}

void	c_iter(t_tok *d, t_tok **c, int *i, int *k)
{
	if (*k != 0)
	{
		if (d[*i].token == tk_varmin)
			(*c)[*k - 1].end = -1;
		if (d[*i].token == tk_varplus)
			(*c)[*k - 1].end = 1;
	}
	if (d[*i].token == tk_plusvar)
		(*c)[*k].beg = 1;
	if (d[*i].token == tk_minvar)
		(*c)[*k].beg = -1;
}

int		check_put_oper(int prev, t_tok *dirty, int i)
{
	if (prev == 'n' || (check_next_tok(dirty, i) != tk_nb
				&& check_next_tok(dirty, i) != tk_plusvar
				&& check_next_tok(dirty, i) != tk_minvar))
		return (1);
	return (0);
}

void	invert_value(int *i)
{
	if (*i == -1)
		*i = 1;
	else
		*i = -1;
}

void	insert_clean_token(t_tok *d, t_tok **c, t_integ *v)
{
	(*c)[v->k++].token = d[v->i].token;
	v->prev = d[v->i].token;
}
