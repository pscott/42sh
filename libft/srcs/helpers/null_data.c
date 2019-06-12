/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   null_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschoenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:38:17 by aschoenh          #+#    #+#             */
/*   Updated: 2019/06/12 15:38:19 by aschoenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		null_data(t_arg *specs, ULL value)
{
	if (specs->precision && specs->precision_len == 0 && value == 0)
		return (1);
	return (0);
}
