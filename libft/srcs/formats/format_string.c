/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:53:23 by pscott            #+#    #+#             */
/*   Updated: 2019/04/04 18:28:50 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	fill_string(t_arg *specs, char *value)
{
	int		data_l;
	int		perc_len;
	char	fill;

	data_l = specs->precision
		? min(specs->precision_len, specs->data_len) : specs->data_len;
	if (*value == 0)
		data_l = 0;
	perc_len = max(specs->width_len, data_l);
	fill = specs->fill;
	ft_special_memset(specs, fill, perc_len - data_l);
	ft_strncat_move(value, data_l, specs);
}

static void	fill_string_left(t_arg *specs, char *value)
{
	int		data_l;
	int		perc_len;

	data_l = specs->precision
		? min(specs->precision_len, specs->data_len) : specs->data_len;
	if (*value == 0)
		data_l = 0;
	perc_len = max(specs->width_len, data_l);
	ft_strncat_move(value, data_l, specs);
	ft_special_memset(specs, ' ', perc_len - data_l);
}

void		format_string(t_arg *specs, char *value)
{
	char *nil;

	nil = "(null)";
	specs->data_len = ft_strlen(value);
	if (value == NULL)
	{
		value = nil;
		specs->data_len = 6;
	}
	if (specs->l == 1)
	{
		specs->origin = NULL;
		ft_special_memset(specs, 0, 1);
		return ;
	}
	if (specs->left && specs->plus)
		specs->fill = ' ';
	if (specs->left)
		fill_string_left(specs, value);
	else
		fill_string(specs, value);
}
