/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:53:23 by pscott            #+#    #+#             */
/*   Updated: 2019/04/04 14:53:25 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		i_min(t_arg *specs)
{
	char			*str;

	str = "2147483648";
	realloc_if_necessary(specs, 10);
	while (*str)
	{
		*(specs->string) = *str;
		specs->string++;
		str++;
	}
}

void			ft_nitoa(t_arg *specs, int n)
{
	int		len;
	int		tmp;

	if (n == -2147483648)
		return (i_min(specs));
	len = get_len(n);
	tmp = len;
	realloc_if_necessary(specs, len);
	if (n < 0)
		n = -n;
	while (n > 9)
	{
		specs->string[len - 1] = n % 10 + '0';
		n = n / 10;
		len--;
	}
	specs->string[0] = n + '0';
	specs->string += tmp;
}
