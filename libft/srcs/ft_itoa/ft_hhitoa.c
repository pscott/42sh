/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hhitoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:53:23 by pscott            #+#    #+#             */
/*   Updated: 2019/04/04 14:53:25 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		hh_min(t_arg *specs)
{
	char			*str;

	str = "128";
	realloc_if_necessary(specs, 3);
	while (*str)
	{
		*(specs->string) = *str;
		specs->string++;
		str++;
	}
}

void			ft_hhitoa(t_arg *specs, signed char n)
{
	int		len;
	int		tmp;

	if (n == -128)
		return (hh_min(specs));
	len = get_hhlen(n);
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
