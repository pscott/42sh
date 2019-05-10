/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_float.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:53:23 by pscott            #+#    #+#             */
/*   Updated: 2019/04/04 14:53:25 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	set_float_len(t_arg *specs, double f)
{
	int len;
	int	declen;

	len = get_llen((long long)f);
	if (specs->precision)
		declen = specs->precision_len ? specs->precision_len : -1;
	else
		declen = 6;
	return (len + declen + 1 + (f < 0));
}

static int	set_ld_len(t_arg *specs, long double f)
{
	int len;
	int	declen;

	len = get_llen((long long)f);
	if (specs->precision)
		declen = specs->precision_len ? specs->precision_len : -1;
	else
		declen = 6;
	return (len + declen + 1 + (f < 0));
}

static void	float_to_string(t_arg *specs, double f)
{
	double	dec;
	int		i;
	int		data_l;
	int		perc_len;

	data_l = set_float_len(specs, f);
	perc_len = max(specs->width_len, data_l);
	ft_special_memset(specs, specs->fill, perc_len - data_l);
	if (f < 0)
	{
		ft_special_memset(specs, '-', 1);
		f = -f;
	}
	ft_litoa(specs, (L)f);
	i = set_i(specs);
	dec = f - (int)f;
	while (i > 0)
	{
		dec *= 10;
		ft_special_memset(specs, dec + '0', 1);
		dec -= (int)dec;
		i--;
	}
}

static void	ld_to_string(t_arg *specs, long double f)
{
	long double	dec;
	int			i;
	int			data_l;
	int			perc_len;

	data_l = set_ld_len(specs, f);
	perc_len = max(specs->width_len, data_l);
	ft_special_memset(specs, specs->fill, perc_len - data_l);
	if (f < 0)
	{
		ft_special_memset(specs, '-', 1);
		f = -f;
	}
	ft_litoa(specs, (L)f);
	i = set_i(specs);
	dec = f - (int)f;
	while (i > 0)
	{
		dec *= 10;
		ft_special_memset(specs, dec + '0', 1);
		dec -= (int)dec;
		i--;
	}
}

void		format_float(t_arg *specs, va_list arg)
{
	if (specs->dbl)
		ld_to_string(specs, va_arg(arg, long double));
	else
		float_to_string(specs, va_arg(arg, double));
}
