#include "42sh.h"
#include "exp_arith.h"

static	int		ft_isop(char c, char d, int *i)
{
	if (c == '$' && ft_isalnum(d))
	{
		*i += 1;
		return (1);
	}
	if ((c == '<' || c == '>' || c == '!' || c == '=')
			&& d == '=')
	{
		*i += 1;
		return (1);
	}
	if (c == '&' && d == '&')
	{
		*i += 1;
		return (1);
	}
	if (c == '|' && d == '|')
	{
		*i += 1;
		return (1);
	}
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '<'
			|| c == '>')
		return (1);
	return (0);
}

/*
**	Check unauthorized characters, and bad syntaxs of comparisons
*/

int				check_chars(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && !ft_isop(str[i], str[i + 1], &i)
				&& !ft_is_white_space(str[i]))
			return (1);
		i++;
	}
	return (0);
}
