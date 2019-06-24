/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data_len.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:21:26 by penzo             #+#    #+#             */
/*   Updated: 2019/06/24 11:21:27 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	set_data_len(t_arg *specs, LL value)
{
	if (specs->type == 'x')
		value_x(specs, value);
	else if (specs->type == 'X')
		value_xx(specs, value);
	else if (specs->type == 'o')
		value_o(specs, value);
}
