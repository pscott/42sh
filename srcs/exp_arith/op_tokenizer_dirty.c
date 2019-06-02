#include "ftsh.h"
#include "env.h"
#include "exp_arith.h"

int		init_toks_dirty(t_tok **tokens, char *str)
{
	size_t i;

	i = 0;
	if (!(*tokens = (t_tok*)malloc(sizeof(t_tok) * (ft_strlen(str) + 1))))
		ERROR_MEM;
	while (i <= ft_strlen(str))
	{
		(*tokens)[i].token = 0;
		(*tokens)[i].value = 0;
		(*tokens)[i].varid = -2;
		(*tokens)[i].varname = NULL;
		i++;
	}
	return (0);
}

void	d_number(t_tok **tokens, size_t *i, int *k, char **str)
{
	(*tokens)[*k].token = TK_NB;
	(*tokens)[*k].value = ft_atoll(*str);
	clean_done_token(*str + *i, get_nb_len(*str + *i));
}

int		d_variable(t_tok **tks, t_integ *it, char **str, char ***vars)
{
	char		*tmp;
	char		*ptr;

	(*tks)[it->k].value = 1;
	(*tks)[it->k].token = TK_NB;
	if ((*str)[it->i] == '$')
	{
		(*tks)[it->k].value = 0;
		if (!(tmp = ft_strndup(*str + it->i + 1, is_var(*str + it->i + 1))))
			ERROR_MEM;
		if ((ptr = get_envline_value(tmp, *vars)))
			(*tks)[it->k].value = ft_atoll(ptr);
	}
	else
	{
		if (!(tmp = ft_strndup(*str + it->i, is_var(*str + it->i))))
			ERROR_MEM;
		(*tks)[it->k].varid = get_envline_index(tmp, *vars);
		(*tks)[it->k].varname = tmp;
	}
	clean_done_token(*str + it->i, is_var(*str + it->i));
	return (0);
}

void	d_operator(t_tok **t, size_t *i, int *k, char **s)
{
	int ret;

	if (*i != 0)
	{
		if (*k > 1)
			ret = get_op_token(*s + *i, (*t)[*k - 1].varid, (*t)[*k - 2].token);
		else if (*k > 0)
			ret = get_op_token(*s + 1, (*t)[*k - 1].varid, 0);
		else
			ret = get_op_token(*s + *i, (*t)[*k].varid, 0);
	}
	else
		ret = get_op_token(*s + *i, -2, 0);
	(*t)[*k].token = ret;
	(*t)[*k].value = 0;
	if (ret < TK_ADD)
		clean_done_token(*s + *i, 2);
	else
		clean_done_token(*s + *i, is_oper(*s + *i));
}
