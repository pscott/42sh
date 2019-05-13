/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_quote_space_par_meta.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschoenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 19:20:30 by aschoenh          #+#    #+#             */
/*   Updated: 2019/05/10 19:21:55 by aschoenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	is_quotes(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

unsigned int	is_white_spaces(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r')//test \r
		return (1);
	return (0);
}

unsigned int	is_parenth(char c)
{
	if (c == '[' || c == ']' || c == '(' || c == ')')
		return (1);
	return (0);
}

unsigned int	is_metachar(char c)
{
	if (is_white_spaces(c) || is_parenth(c) || is_quotes(c) || c  == '*'
			|| c == '?' || c == '\\' || c == ';' || c == '&'
			|| c == '|' || c == '^' || c == '<' || c == '>')
		return (1);
	return (0);
}
