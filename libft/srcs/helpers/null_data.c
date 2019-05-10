/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   null_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:53:23 by pscott            #+#    #+#             */
/*   Updated: 2019/04/04 14:53:26 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		null_data(t_arg *specs, ULL value)
{
	if (specs->precision && specs->precision_len == 0 && value == 0)
		return (1);
	return (0);
}
