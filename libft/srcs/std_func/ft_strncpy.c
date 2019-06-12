/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschoenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:38:15 by aschoenh          #+#    #+#             */
/*   Updated: 2019/06/12 15:38:17 by aschoenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	if (!dst)
		return (NULL);
	if (!src)
		return (dst);
	while (src[i] && len - i)
	{
		dst[i] = src[i];
		i++;
	}
	while (len - i)
	{
		dst[i] = 0;
		i++;
	}
	return (dst);
}
