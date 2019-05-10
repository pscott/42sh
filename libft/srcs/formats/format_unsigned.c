/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_unsigned.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:53:23 by pscott            #+#    #+#             */
/*   Updated: 2019/04/04 14:53:24 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	fill_uint_left(int perc_len, t_arg *specs, ULL value)
{
	while (specs->precision_len > specs->data_len)
	{
		*specs->string = '0';
		increm_string(specs, 1);
		specs->precision_len--;
		perc_len--;
	}
	if (!null_data(specs, value))
		ft_uitoa_spec(specs, value);
	ft_special_memset(specs, ' ', perc_len - specs->data_len);
}

static void	fill_uint(int perc_len, t_arg *specs, ULL value)
{
	while (perc_len > max(specs->precision_len, specs->data_len))
	{
		*specs->string = specs->fill;
		increm_string(specs, 1);
		perc_len--;
	}
	ft_special_memset(specs, '0', specs->precision_len - specs->data_len);
	if (!null_data(specs, value))
		ft_uitoa_spec(specs, value);
}

void		format_unsigned(t_arg *specs, ULL value)
{
	int	perc_len;

	value_u(specs, value);
	if (null_data(specs, value && !specs->plus))
		specs->data_len = 0;
	if (specs->precision_len > specs->width_len)
		perc_len = max(specs->data_len, specs->precision_len);
	else
		perc_len = max(specs->data_len, specs->width_len);
	if (specs->plus && specs->data_len)
		specs->data_len++;
	if (specs->left && specs->plus)
		specs->fill = ' ';
	if (specs->left)
		fill_uint_left(perc_len, specs, value);
	else
		fill_uint(perc_len, specs, value);
}
