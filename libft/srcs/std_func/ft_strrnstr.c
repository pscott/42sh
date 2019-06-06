/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrnstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:53:19 by pscott            #+#    #+#             */
/*   Updated: 2019/06/06 18:50:55 by aschoenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (*needle == 0)
		return (NULL);
	i = len;
	/*
	ft_printf("\n\n1:|%s|, 2:|%s|, len:|%d|\n\n", haystack, needle, len);
	sleep(3);
	*/
	if (i > ft_strlen(haystack) - 1)
		i = ft_strlen(haystack) - 1;
	while (haystack[i])
	{
		j = 0;
		while (haystack[i] == needle[j] && needle[j])
		{
			i++;
			j++;
		}
		if (needle[j] == 0)
		{
			return ((char *)&haystack[i - j]);
		}
		if (i - j > 0)
			i = i - j - 1;
		else
			return (NULL);
	}
	return (NULL);
}
