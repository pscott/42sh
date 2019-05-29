#include "42sh.h"
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

int		d_variable(t_tok **tokens, size_t *i, int *k, char **str, char ***vars)
{
	char		*tmp;
	char		*ptr;
	long long	ret;

	(*tokens)[*k].value = 1;
	(*tokens)[*k].token = TK_NB;
	if ((*str)[*i] == '$')
	{
		(*tokens)[*k].value = 0;
		if (!(tmp = ft_strndup(*str + *i + 1, is_var(*str + *i + 1))))
			ERROR_MEM;
		if ((ptr = get_envline_value(tmp, *vars)))
			(*tokens)[*k].value = ft_atoll(ptr);
	}
	else
	{
		if (!(tmp = ft_strndup(*str + *i, is_var(*str + *i))))
			ERROR_MEM;
		(*tokens)[*k].varid = get_envline_index(tmp, *vars);
		(*tokens)[*k].varname = tmp;
	}
	clean_done_token(*str + *i, is_var(*str + *i));
	return (0);
}

void	d_operator(t_tok **tk, size_t *i, int *k, char **str)
{
	int ret;

	if (*i != 0)
	{
		if (*k > 1)
			ret = get_op_token(*str + *i, (*tk)[*k - 1].varid, (*tk)[*k - 2].token);
		else if (*k > 0)
			ret = get_op_token(*str + *i, (*tk)[*k - 1].varid, 0);
		else
			ret = get_op_token(*str + *i, (*tk)[*k].varid, 0);
	}
	else
		ret = get_op_token(*str + *i, -2, 0);
	(*tk)[*k].token = ret;
	(*tk)[*k].value = 0;
	if (ret < TK_ADD)
		clean_done_token(*str + *i, 2);
	else
		clean_done_token(*str + *i, is_oper(*str + *i));
}
