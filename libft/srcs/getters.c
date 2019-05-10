/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:53:24 by pscott            #+#    #+#             */
/*   Updated: 2019/04/04 14:53:26 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	check_if_flags(t_arg *specs, char c, char **format, va_list arg)
{
	if (c == '-')
		specs->left++;
	else if (c == '+')
		specs->plus++;
	else if (c == '#')
		specs->hash++;
	else if (c == '0')
		specs->fill = '0';
	else if (c == '*')
		wildcard(specs, arg, 0);
	else if (c == ' ')
	{
		set_extra(c, specs);
		if (specs->fill != '0')
			specs->fill = ' ';
	}
	else if (ft_isdigit(c) && c != '0')
	{
		if ((specs->width_len = ft_atoi_move(format)))
		{
			specs->width = 1;
			(*format)--;
		}
	}
	increm_format(format, 1);
}

int		get_flags(t_arg *specs, char **format, va_list arg)
{
	while (isprint_special(**format))
	{
		if (**format == '.')
		{
			while (**format == '.')
				increm_format(format, 1);
			specs->precision = 1;
			if (**format == '*')
			{
				wildcard(specs, arg, 1);
				(*format)++;
			}
			else
				specs->precision_len = ft_atoi_move(format);
		}
		if (is_type(format, specs))
			return (specs->type = **format);
		if (is_spec_upper(**format))
			return (specs->type = '%');
		check_if_flags(specs, **format, format, arg);
	}
	return (0);
}

void	get_lh(char **format, t_arg *specs)
{
	while (**format == 'h' || **format == 'l' || **format == 'L')
	{
		if (**format == 'h')
			specs->h++;
		else if (**format == 'l')
			specs->l++;
		else if (**format == 'L')
			specs->dbl++;
		increm_format(format, 1);
	}
	if (specs->h > 2)
		specs->h = 2;
	if (specs->l > 2)
		specs->l = 2;
}

int		is_spec_upper(char c)
{
	if (c >= 'A' && c <= 'Z' && c != 'X' && c != 'F')
		return (1);
	return (0);
}

int		is_type(char **format, t_arg *specs)
{
	get_lh(format, specs);
	if (is_valid_type(**format))
	{
		return (1);
	}
	return (0);
}
