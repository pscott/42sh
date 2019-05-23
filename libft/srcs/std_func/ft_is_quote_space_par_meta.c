/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_quote_space_par_meta.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschoenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 19:20:30 by aschoenh          #+#    #+#             */
/*   Updated: 2019/05/23 14:54:43 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

unsigned int	ft_is_white_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r')//test \r: useless
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
