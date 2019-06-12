/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschoenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:38:17 by aschoenh          #+#    #+#             */
/*   Updated: 2019/06/12 15:38:19 by aschoenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		set_i(t_arg *specs)
{
	int i;

	if (specs->precision)
		if (specs->precision_len)
		{
			i = specs->precision_len;
			ft_special_memset(specs, '.', 1);
		}
		else
			i = 0;
	else
	{
		i = 6;
		ft_special_memset(specs, '.', 1);
	}
	return (i);
}
