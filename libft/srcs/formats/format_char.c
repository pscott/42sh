/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:53:23 by pscott            #+#    #+#             */
/*   Updated: 2019/04/04 14:53:24 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	fill_char(int perc_len, t_arg *specs, char *value)
{
	int		data_l;
	char	fill;

	data_l = specs->data_len;
	fill = specs->fill;
	ft_special_memset(specs, fill, perc_len - data_l);
	ft_strncat_move(value, 1, specs);
}

void	fill_char_left(int perc_len, t_arg *specs, char *value)
{
	int		data_l;

	data_l = specs->data_len;
	ft_strncat_move(value, 1, specs);
	ft_special_memset(specs, ' ', perc_len - data_l);
}

void	format_char(t_arg *specs, char value)
{
	int perc_len;

	specs->data_len = 1;
	perc_len = specs->width_len > specs->data_len
		? specs->width_len : specs->data_len;
	if (specs->left && specs->plus)
		specs->fill = ' ';
	if (specs->left)
		fill_char_left(perc_len, specs, &value);
	else
		fill_char(perc_len, specs, &value);
}
