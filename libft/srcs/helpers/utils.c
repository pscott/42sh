/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:53:23 by pscott            #+#    #+#             */
/*   Updated: 2019/04/04 14:53:26 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		valid_flags(char **format)
{
	char c;

	c = **format;
	if (c == '-' || c == '+' || c == '#' || c == '0' || c == ' ' \
			|| ft_isdigit(c))
		return (1);
	return (0);
}

int		is_valid_type(char c)
{
	if (c == 'd' || c == 'i' || c == 'o' || c == 'u' || c == 'i' || c == 'x'
			|| c == 'X' || c == 'u' || c == '%' || c == 'p' || c == 'f'
			|| c == 'F' || c == 's' || c == 'c')
		return (1);
	return (0);
}

int		min(int a, int b)
{
	return (a < b ? a : b);
}

int		max(int a, int b)
{
	return (a < b ? b : a);
}

void	set_extra(char c, t_arg *specs)
{
	if (!specs->extra)
	{
		if (c == ' ' && !specs->plus)
			specs->extra = 1;
		else
			specs->extra = 0;
	}
	else if (specs->plus || specs->fill == '0')
		specs->extra = 0;
}
