/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_quote_space_par_meta.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:21:25 by penzo             #+#    #+#             */
/*   Updated: 2019/06/24 11:21:27 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int				ft_is_unslashed_metachar(char *s, int index, int type)
{
	if (s && s[0] && index > 0 && s[index])
	{
		if (type == white_space)
		{
			if (ft_is_white_space(s[index]) && s[index - 1] != '\\')
				return (1);
		}
		else if (type == parenth)
		{
			if (ft_is_parenth(s[index] && s[index - 1] != '\\'))
				return (1);
		}
		else if (type == quote)
		{
			if (ft_is_quote(s[index] && s[index - 1] != '\\'))
				return (1);
		}
	}
	return (0);
}
