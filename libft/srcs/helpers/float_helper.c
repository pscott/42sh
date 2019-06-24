/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:21:26 by penzo             #+#    #+#             */
/*   Updated: 2019/06/24 11:21:27 by penzo            ###   ########.fr       */
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
