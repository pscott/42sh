#include "42sh.h"
#include "exp_arith.h"

int		init_tokens_clean(t_token *d, t_token **c)
{
	int k;

	k = 0;
	if (!(*c = (t_token*)malloc(sizeof(t_token) * (get_tok_len(d) + 1))))
		ERROR_MEM;
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

void	c_iter(t_token *d, t_token **c, int *i, int *k)
{
	if (*k != 0)
	{
		if (d[*i].token == TK_VARMIN)
			(*c)[*k - 1].end = -1;
		if (d[*i].token == TK_VARPLUS)
			(*c)[*k - 1].end = 1;
	}
	if (d[*i].token == TK_PLUSVAR)
		(*c)[*k].beg = 1;
	if (d[*i].token == TK_MINVAR)
		(*c)[*k].beg = -1;
}

int		check_put_oper(int prev, t_token *dirty, int i)
{
	if (prev == 'n' || (check_next_tok(dirty, i) != TK_NB
				&& check_next_tok(dirty, i) != TK_PLUSVAR
				&& check_next_tok(dirty, i) != TK_MINVAR))
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

void	insert_clean_token(t_token *d, t_token **c, t_integ *v)
{
	(*c)[v->k++].token = d[v->i].token;
	v->prev = d[v->i].token;
}