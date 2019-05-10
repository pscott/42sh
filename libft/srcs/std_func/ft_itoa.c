/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:53:19 by pscott            #+#    #+#             */
/*   Updated: 2019/04/04 14:53:24 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_my_len(int n)
{
	int len;

	len = 0;
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n > 9)
	{
		n = n / 10;
		len++;
	}
	return (len + 1);
}

static void	fill_itoa(int n, char *src, int len)
{
	while (n > 9)
	{
		src[len - 1] = n % 10 + '0';
		len--;
		n = n / 10;
	}
	src[0] = n + '0';
}

static char	*min_int(char *res)
{
	char	*num;
	int		i;

	num = "-2147483648";
	i = 0;
	while (i < 11)
	{
		res[i] = num[i];
		i++;
	}
	return (res);
}

char		*ft_itoa(int n)
{
	char	*res;
	int		len;

	len = get_my_len(n);
	if (!(res = ft_strnew(len)))
		return (NULL);
	if (n == -2147483648)
		return (min_int(res));
	if (n < 0)
	{
		res[0] = '-';
		fill_itoa(-n, &res[1], len - 1);
	}
	else
		fill_itoa(n, res, len);
	return (res);
}
