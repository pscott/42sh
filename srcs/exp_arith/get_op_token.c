#include "ftsh.h"
#include "exp_arith.h"

/*
**	Other operators : comparisons, mod, div and mult
*/

static	int		get_op_token_2(char *str)
{
	if (!ft_strncmp(str, "||", 2))
		return (tk_operor);
	if (!ft_strncmp(str, "&&", 2))
		return (tk_operand);
	if (!ft_strncmp(str, "!=", 2))
		return (tk_noteq);
	if (!ft_strncmp(str, "==", 2))
		return (tk_eq);
	if (!ft_strncmp(str, ">=", 2))
		return (tk_moreeq);
	if (!ft_strncmp(str, "<=", 2))
		return (tk_lesseq);
	if (!ft_strncmp(str, ">", 1))
		return (tk_more);
	if (!ft_strncmp(str, "<", 1))
		return (tk_less);
	if (!ft_strncmp(str, "%", 1))
		return (tk_mod);
	if (!ft_strncmp(str, "/", 1))
		return (tk_div);
	if (!ft_strncmp(str, "*", 1))
		return (tk_mult);
	return (0);
}

static	char	pass_spaces(char *str)
{
	int i;

	i = 0;
	while (ft_is_white_space(str[i]))
		i++;
	return (str[i]);
}

/*
**	Identifying '+' and '-' symbols as iterators or operators, depending
**	of the presence of a variable near these tokens
*/

int				get_op_token(char *str, int varid, int prev_prev_tk)
{
	int ret;

	if ((ret = get_op_token_2(str)))
		return (ret);
	if (!ft_strncmp(str, "++", 2) && varid != -2 && (prev_prev_tk == 0
			|| prev_prev_tk > tk_minvar || prev_prev_tk == tk_nb))
		return (tk_varplus);
	if (!ft_strncmp(str, "++", 2) && ft_isalpha(pass_spaces(str + 2)))
		return (tk_plusvar);
	if (!ft_strncmp(str, "--", 2) && varid != -2 && (prev_prev_tk == 0
			|| prev_prev_tk > tk_minvar || prev_prev_tk == tk_nb))
		return (tk_varmin);
	if (!ft_strncmp(str, "--", 2) && ft_isalpha(pass_spaces(str + 2)))
		return (tk_minvar);
	if (!ft_strncmp(str, "-", 1))
		return (tk_sub);
	if (!ft_strncmp(str, "+", 1))
		return (tk_add);
	return (0);
}
