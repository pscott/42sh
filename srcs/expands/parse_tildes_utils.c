/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tildes_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:21:14 by penzo             #+#    #+#             */
/*   Updated: 2019/06/24 11:21:18 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	is_valid_tilde(const char *str, t_token *prev_token)
{
	if (!prev_token && (!ft_strncmp("~/", str, 2) || !ft_strncmp("~", str, 2)))
		return (1);
	if (prev_token && prev_token->type == tk_eat
		&& (!ft_strncmp("~/", str, 2) || !ft_strncmp("~", str, 2)))
		return (1);
	if (!prev_token && (!ft_strncmp("~", str, 1)))
		return (2);
	if (prev_token && prev_token->type == tk_eat
		&& (!ft_strncmp("~", str, 1)))
		return (2);
	return (0);
}

int	is_slashed(const char *str)
{
	char	*ptr;

	if ((ptr = ft_strchr(str, '/')))
	{
		while (ptr && *ptr)
		{
			if (*ptr == '/')
				ptr++;
			else if (*ptr != '\0')
				return (1);
			else if (*ptr == '\0')
				return (0);
		}
	}
	return (0);
}
