/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:53:23 by pscott            #+#    #+#             */
/*   Updated: 2019/04/04 14:53:24 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char			sign_len(t_arg *specs, LL value)
{
	if (value < 0)
		return ('-');
	if (specs->plus)
		return ('+');
	return (0);
}

static void			fill_int_left(int perc_len, t_arg *specs, LL value)
{
	value = choose_value(specs, value);
	if (sign_len(specs, value))
	{
		*specs->string = value < 0 ? '-' : '+';
		increm_string(specs, 1);
		perc_len--;
	}
	while (specs->precision_len > specs->data_len)
	{
		*specs->string = '0';
		increm_string(specs, 1);
		specs->precision_len--;
		perc_len--;
	}
	if (!null_data(specs, (ULL)value))
		ft_itoa_spec(specs, value);
	ft_special_memset(specs, ' ', perc_len - specs->data_len);
}

static void			fill_int(int perc_len, t_arg *specs, LL value)
{
	char sign_put;

	value = choose_value(specs, value);
	sign_put = sign_len(specs, value);
	if (specs->fill == '0')
	{
		if (sign_put)
		{
			*specs->string = sign_put;
			sign_put = 0;
			increm_string(specs, 1);
		}
	}
	ft_special_memset(specs, specs->fill, perc_len - max(specs->precision_len
				, specs->data_len) - (sign_len(specs, value) > 0));
	if (sign_put)
		ft_special_memset(specs, sign_put, 1);
	ft_special_memset(specs, '0', specs->precision_len - specs->data_len);
	if (!null_data(specs, value))
		ft_itoa_spec(specs, value);
}

void				format_int(t_arg *specs, LL value)
{
	int		perc_len;

	value_d(specs, value);
	if (null_data(specs, (ULL)value) && !specs->plus)
		specs->data_len = 0;
	if (specs->precision_len > specs->width_len)
		specs->fill = '0';
	perc_len = max(specs->data_len, specs->width_len);
	if (specs->extra && (choose_value(specs, value) >= 0) && !specs->plus)
	{
		*specs->string = ' ';
		increm_string(specs, 1);
		perc_len--;
	}
	if (specs->left && specs->plus)
		specs->fill = ' ';
	if (specs->left)
		fill_int_left(perc_len, specs, value);
	else
		fill_int(perc_len, specs, value);
}
