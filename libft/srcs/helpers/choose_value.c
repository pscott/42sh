/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschoenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:38:17 by aschoenh          #+#    #+#             */
/*   Updated: 2019/06/12 15:38:19 by aschoenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

LL	choose_value(t_arg *specs, LL value)
{
	if (specs->l == 1)
		value = (L)value;
	else if (specs->h == 2)
		value = (signed char)value;
	else if (specs->h == 1)
		value = (short int)value;
	else if (specs->l == 0 && specs->h == 0)
		value = (int)value;
	return (value);
}
