/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_op_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschoenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:38:05 by aschoenh          #+#    #+#             */
/*   Updated: 2019/06/12 15:38:09 by aschoenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftsh.h"
#include "exp_arith.h"

/*
**	Other operators : comparisons, mod, div and mult
*/

static	int		get_op_token_2(char *str)
{
	if (!ft_strncmp(str, "||", 2))
		return (TK_OPEROR);
	if (!ft_strncmp(str, "&&", 2))
		return (TK_OPERAND);
	if (!ft_strncmp(str, "!=", 2))
		return (TK_NOTEQ);
	if (!ft_strncmp(str, "==", 2))
		return (TK_EQ);
	if (!ft_strncmp(str, ">=", 2))
		return (TK_MOREEQ);
	if (!ft_strncmp(str, "<=", 2))
		return (TK_LESSEQ);
	if (!ft_strncmp(str, ">", 1))
		return (TK_MORE);
	if (!ft_strncmp(str, "<", 1))
		return (TK_LESS);
	if (!ft_strncmp(str, "%", 1))
		return (TK_MOD);
	if (!ft_strncmp(str, "/", 1))
		return (TK_DIV);
	if (!ft_strncmp(str, "*", 1))
		return (TK_MULT);
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
			|| prev_prev_tk > TK_MINVAR || prev_prev_tk == TK_NB))
		return (TK_VARPLUS);
	if (!ft_strncmp(str, "++", 2) && ft_isalpha(pass_spaces(str + 2)))
		return (TK_PLUSVAR);
	if (!ft_strncmp(str, "--", 2) && varid != -2 && (prev_prev_tk == 0
			|| prev_prev_tk > TK_MINVAR || prev_prev_tk == TK_NB))
		return (TK_VARMIN);
	if (!ft_strncmp(str, "--", 2) && ft_isalpha(pass_spaces(str + 2)))
		return (TK_MINVAR);
	if (!ft_strncmp(str, "-", 1))
		return (TK_SUB);
	if (!ft_strncmp(str, "+", 1))
		return (TK_ADD);
	return (0);
}
