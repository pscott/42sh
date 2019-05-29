#include "42sh.h"
#include "exp_arith.h"

/*
**	Second tokenization : removing variable iterations, and '+' and '-' which
**	are not operators but sign marks, and building a clean token array
*/

static	int		format_toks(t_tok *di, t_tok **cl)
{
	t_integ	v;

	v.prev = 0;
	v.moins = 1;
	v.i = 0;
	v.k = 0;
	init_toks_clean(di, cl);
	while (di[v.i].token != 0)
	{
		if (di[v.i].token == TK_NB)
			c_number(di, cl, &v);
		else if (di[v.i].token <= TK_MINVAR && di[v.i].token >= TK_VARPLUS)
			c_iter(di, cl, &v.i, &v.k);
		else
			c_operator(di, cl, &v);
		v.i++;
	}
	return (0);
}

/*
**	First tokenization : almost raw interpretation of the text and operators,
**	but the iterators and the variables are identified, and building a
**	dirty token array
*/

int				op_tokenizer(char *str, t_tok **tokens, char ***vars)
{
	size_t		i;
	int			k;
	t_tok		*clean;

	k = 0;
	i = 0;
	init_toks_dirty(tokens, str);
	while (!ft_str_isempty(str))
	{
		while (ft_is_white_space(str[i]))
			i++;
		if (get_nb_len(str + i))
			d_number(tokens, &i, &k, &str);
		else if (is_var(str + i))
			d_variable(tokens, &i, &k, &str, vars);
		else
			d_operator(tokens, &i, &k, &str);
		k++;
	}
	format_toks(*tokens, &clean);
	free_tokens(*tokens, 0);
	*tokens = clean;
	return (0);
}
