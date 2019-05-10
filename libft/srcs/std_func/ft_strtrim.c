/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:53:19 by pscott            #+#    #+#             */
/*   Updated: 2019/04/04 14:53:24 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t		right_trim(char const *s)
{
	size_t	i;
	size_t	origin_len;

	if ((origin_len = ft_strlen(s)))
	{
		i = 0;
		while (s[origin_len - i - 1] == '\t' || s[origin_len - i - 1] == ' '
				|| s[origin_len - i - 1] == '\n')
			i++;
		return (origin_len - i);
	}
	return (0);
}

char				*ft_strtrim(char const *s)
{
	char		*res;
	size_t		i;
	size_t		len;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] == '\t' || s[i] == ' ' || s[i] == '\n')
		i++;
	len = right_trim(&s[i]);
	if (!(res = ft_strnew(len)))
		return (NULL);
	ft_strncpy(res, &s[i], len);
	return (res);
}
