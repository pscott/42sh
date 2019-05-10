/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:53:23 by pscott            #+#    #+#             */
/*   Updated: 2019/04/04 14:53:24 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		fill_string(t_arg *specs, L value)
{
	int		data_l;
	int		perc_len;

	data_l = value ? specs->data_len : 1;
	if (!value && specs->precision && !specs->precision_len)
		data_l = 0;
	perc_len = max(specs->width_len, data_l);
	if (specs->fill == '0')
	{
		ft_strncat_move("0x", 2, specs);
		perc_len -= 2;
	}
	while ((data_l != 0 || specs->width)
			&& perc_len > max(specs->precision_len, data_l)
			+ (specs->fill != '0' && value != '0')
			* ox_len(specs))
	{
		*specs->string = specs->fill;
		perc_len--;
		increm_string(specs, 1);
	}
	if (specs->fill != '0')
		ft_strncat_move("0x", 2, specs);
	ft_special_memset(specs, '0', specs->precision_len - data_l);
	ft_strncat_move(specs->conv_val, data_l, specs);
}

static void		fill_string_left(t_arg *specs, L value)
{
	int		data_l;
	int		perc_len;

	data_l = value ? specs->data_len : 1;
	if (!value && specs->precision && !specs->precision_len)
		data_l = 0;
	perc_len = max(specs->width_len, data_l);
	ft_strncat_move("0x", 2, specs);
	while (specs->precision_len > data_l)
	{
		*specs->string = '0';
		specs->precision_len--;
		increm_string(specs, 1);
		perc_len--;
	}
	ft_strncat_move(specs->conv_val, data_l, specs);
	while ((data_l != 0 || specs->width)
			&& perc_len > max(specs->precision_len, data_l) +
			(specs->fill != '0' && value != '0')
			* ox_len(specs))
	{
		*specs->string = ' ';
		perc_len--;
		increm_string(specs, 1);
	}
}

void			format_p(t_arg *specs, L value)
{
	specs->conv_val = convert_p(value, 16, BASE_16_LOW);
	specs->data_len = ft_strlen(specs->conv_val);
	if (specs->left && specs->plus)
		specs->fill = ' ';
	if (specs->left)
	{
		specs->fill = ' ';
		fill_string_left(specs, value);
	}
	else
		fill_string(specs, value);
}
