/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:53:24 by pscott            #+#    #+#             */
/*   Updated: 2019/04/04 14:53:26 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_itoa_spec(t_arg *specs, LL value)
{
	if (specs->l == 2)
		ft_llitoa(specs, (LL)value);
	else if (specs->l == 1)
		ft_litoa(specs, (L)value);
	else if (specs->h == 2)
		ft_hhitoa(specs, (signed char)value);
	else if (specs->h == 1)
		ft_hitoa(specs, (short int)value);
	else
		ft_nitoa(specs, (int)value);
}

int		print_perc(t_arg *specs, char c)
{
	specs->type = 'c';
	if (!specs->fill)
		specs->fill = ' ';
	format_char(specs, c);
	return (1);
}

int		handle_perc(char **format, t_arg *specs, va_list arg)
{
	increm_format(format, 1);
	reset_specs(specs);
	if (get_flags(specs, format, arg) == 2)
	{
		specs->type = '2';
		if (**format)
			(*format)++;
		return (3);
	}
	if (is_valid_type(specs->type))
		return (1);
	return (0);
}

int		parse_struct(t_arg *specs, va_list arg)
{
	if (!specs->fill || (specs->precision && specs->type != 'c'
				&& specs->type != 's'))
		specs->fill = ' ';
	if (specs->type == 'c')
		format_char(specs, va_arg(arg, int));
	else if (specs->type == 'u')
		format_unsigned(specs, va_arg(arg, ULL));
	else if (specs->type == 'd' || specs->type == 'i')
		format_int(specs, va_arg(arg, LL));
	else if (specs->type == 's')
		format_string(specs, va_arg(arg, char*));
	else if (specs->type == 'o' || specs->type == 'x' || specs->type == 'X')
		format_conv(specs, va_arg(arg, LL));
	else if (specs->type == 'p')
		format_p(specs, va_arg(arg, L));
	else if (specs->type == 'f')
		format_float(specs, arg);
	return (1);
}
