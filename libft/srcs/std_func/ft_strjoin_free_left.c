/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free_left.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:21:25 by penzo             #+#    #+#             */
/*   Updated: 2019/06/24 11:21:27 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Joins two strings and frees the one given by the first parameter.
*/

char			*ft_strjoin_free_left(char *s1, const char *s2)
{
	char			*res;
	unsigned int	s1_len;

	if (!s2 && !s1)
		return (NULL);
	if (!s1 && (!s2[0]))
		return (ft_strdup(s2));
	if (!s2 && (!s1[0]))
	{
		res = ft_strdup(s1);
		ft_strdel(&s1);
		return (res);
	}
	s1_len = ft_strlen(s1);
	if (!(res = ft_strnew(s1_len + ft_strlen(s2))))
		return (NULL);
	ft_strcpy(res, s1);
	ft_strcat(&res[s1_len], s2);
	ft_strdel(&s1);
	return (res);
}
