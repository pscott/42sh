/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:53:23 by pscott            #+#    #+#             */
/*   Updated: 2019/04/04 14:53:24 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*ox_helper(t_arg *specs)
{
	char *one;

	if (specs->type == 'x')
		one = "0x";
	else if (specs->type == 'X')
		one = "0X";
	else if (specs->type == 'o')
	{
		one = "0";
		if (specs->precision_len)
			specs->precision_len--;
	}
	else
		one = "";
	return (one);
}

void			check_conv_value(t_arg *specs, char *value)
{
	if ((*value == '0')
			&& (((specs->type == 'X' || specs->type == 'x')
					&& specs->precision && specs->precision_len == 0)
				|| (specs->type == 'o'
					&& (!specs->hash
						&& specs->precision
						&& specs->precision_len == 0))))
		specs->data_len = 0;
}

int				ox_len(t_arg *specs)
{
	if (specs->type == 'X' || specs->type == 'x' || specs->type == 'p')
		return (2);
	else if (specs->type == 'o')
		return (1);
	else
		return (0);
}

void			put_ox(t_arg *specs, char *value, int *perc_len, int modif)
{
	int l;

	if (specs->hash && value[0] != '0')
	{
		l = ox_len(specs);
		if (modif == 0 && specs->fill == '0')
		{
			*perc_len -= l;
			ft_strncat_move(ox_helper(specs), l, specs);
		}
		else if (modif == 1 && specs->fill != '0')
			ft_strncat_move(ox_helper(specs), l, specs);
		else if (modif == 2)
		{
			if (specs->fill == '0')
				*perc_len -= l;
			ft_strncat_move(ox_helper(specs), l, specs);
		}
	}
}
