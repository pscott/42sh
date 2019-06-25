#include "libft.h"

unsigned int	ft_is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

unsigned int	ft_is_white_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r')
		return (1);
	return (0);
}

unsigned int	ft_is_parenth(char c)
{
	if (c == '[' || c == ']' || c == '(' || c == ')')
		return (1);
	return (0);
}

unsigned int	ft_is_metachar(char c)
{
	if (ft_is_white_space(c) || ft_is_quote(c)
			|| c == '\\' || c == ';' || c == '&'
			|| c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int				ft_is_unslashed_metachar(char *s, int i, int type)
{
	if (s && s[0] && s[i])
	{
		if (type == white_space && ft_is_white_space(s[i])
				&& (i == 0 || s[i - 1] != '\\'))
			return (1);
		else if (type == parenth && ft_is_parenth(s[i]
					&& (!i || s[i - 1] != '\\')))
			return (1);
		else if (type == quote)
		{
			if (ft_is_quote(s[i] && (!i || s[i - 1] != '\\')))
				return (1);
		}
		else if (type == separator)
		{
			if ((s[i] == '&' || s[i] == ';' || s[i] == '|') && (i == 0
						|| s[i - 1] != '\\'))
			{
				return (1);
			}
		}
	}
	return (0);
}
