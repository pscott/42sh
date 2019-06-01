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

static char	*lltoa_and_free(long long nb, char **to_free)
{
	char		*str;
	int			len;

	ft_strdel(to_free);
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

static char	*dup_for_arith_exp(char *str, size_t i, size_t index)
{
	char	*new_str;

	if (!(new_str = ft_strndup(str + index + 3, i - (index + 3))))
		ERROR_MEM;
	return (new_str);
}

static char	expand_lowest_arith_exp(char **str, t_vars *vars)
{
	size_t		i;
	size_t		index[2];
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
			index[1] = i + 1;
			arith_str = dup_for_arith_exp(*str, i, index[0]);
			if (expansion_arith(arith_str, &vars->shell_vars, &arith_result))
				return (-1);
			arith_str = lltoa_and_free(arith_result, &arith_str);
			substitute_slice(str, index, arith_str);
			ft_strdel(&arith_str);
			return (1);
		}
		i++;
	}
	return (0);
}

t_bool		parse_arith_exp(char **str, t_vars *vars)
{
	size_t		i;
	char		escaped;
	char		arith_expand_ret;

	i = 0;
	escaped = 0;
	while ((*str)[i])
	{
		if (!escaped && !ft_strncmp("$((", (*str) + i, 3)
				&& is_matched((*str) + i, "$((", "))"))
		{
			while ((arith_expand_ret = expand_lowest_arith_exp(str, vars)))
				if (arith_expand_ret == -1)
					return (0);//bad sub
		}
		else if ((*str)[i] == '\\')
			escaped = (escaped) ? 0 : 1;
		else
			escaped = 0;
		i++;
	}//no need to check if empty for arith_exp
	return (1);
}
