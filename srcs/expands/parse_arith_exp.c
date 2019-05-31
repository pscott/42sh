#include "cmd_parsing.h"
#include "exp_arith.h"

static	size_t	get_ll_len(long long nb)
{
	size_t	len;

	len = (nb < 0) ? 1 : 0;
	while (nb)
	{
		len++;
		nb = nb / 10;
	}
	return (len);
}

static char	*lltoa(long long nb)
{
	char		*str;
	int			len;

	len = get_ll_len(nb);
	if (!(str = ft_strnew(len)))
		ERROR_MEM;
	if (nb < 0)
	{
		str[0] = '-';
		nb = nb * -1;
	}
	while (nb)
	{
		str[len-- - 1] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (str);
}

/*
** aa$((2 + 3))aa
**   ^2        ^12
** len should be 5
*/
static char	*dup_for_arith_exp(char *str, size_t i, size_t index)
{
	char	*new_str;

	if (!(new_str = ft_strndup(str + index + 3, i - (index + 3))))
		ERROR_MEM;
	return (new_str);
}

static char	expand_lowest_arith_exp(char **str, t_vars *vars)
{
	size_t	i;
	size_t	index[2];
	long long	arith_result;
	char		*arith_str;

	i = 0;
	arith_result = 0;
	while ((*str)[i])
	{
		if (!(ft_strncmp("$((", *str + i, 3)))
			index[0] = i;
		if (!(ft_strncmp("))", *str + i, 2)))
		{
			index[1] = i + 2;
			arith_str = dup_for_arith_exp(*str, i, index[0]);
			if (expansion_arith(arith_str, &vars->shell_vars, &arith_result))
				return (-1);
			ft_strdel(&arith_str);
			substitute_slice(str, index, lltoa(arith_result));
			return (1);
		}
		i++;
	}
	return (0);
}

t_bool		parse_arith_exp(t_token *token, t_vars *vars)
{
	size_t		i;
	char		escaped;
	char		arith_expand_ret;//TODO

	i = 0;
	escaped = 0;
	while (token->content[i])
	{
		if (!escaped && !ft_strncmp("$((", &token->content[i], 3)
				&& is_matched(token->content + i, "$((", "))"))
		{
			while ((arith_expand_ret = expand_lowest_arith_exp(&token->content, vars)))//no need to move *i as it will be relplaced by numbers only
			{
				if (arith_expand_ret == -1)
					return (0);//bad sub
				ft_printf("TOP: |%s|\n", token->content);//debug
			}
		}
		else if (token->content[i] == '\\')
			escaped = (escaped) ? 0 : 1;
		else
			escaped = 0;
		i++;
	}//no need to check if empty for arith_exp
	return (1);
}
