/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_litoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:53:23 by pscott            #+#    #+#             */
/*   Updated: 2019/04/04 14:53:25 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		l_min(t_arg *specs)
{
	char			*str;

	str = "9223372036854775808";
	realloc_if_necessary(specs, 19);
	while (*str)
	{
		*(specs->string) = *str;
		specs->string++;
		str++;
	}
}

void			ft_litoa(t_arg *specs, L n)
{
	int		len;
	int		tmp;

	if ((ULL)n == 9223372036854775808U)
		return (l_min(specs));
	len = get_llen(n);
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
