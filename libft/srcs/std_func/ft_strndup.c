/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschoenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:38:16 by aschoenh          #+#    #+#             */
/*   Updated: 2019/06/12 15:38:18 by aschoenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_strndup(const char *s1, size_t n)
{
	char	*res;
	size_t	len;

	if (!s1)
		return (NULL);
	len = ft_strnlen(s1, n) < n ? ft_strnlen(s1, n) : n;
	if (!(res = ft_strnew(len)))
		return (NULL);
	ft_strncpy(res, s1, len);
	res[len] = 0;
	return (res);
}
