/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   values.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:53:23 by pscott            #+#    #+#             */
/*   Updated: 2019/04/04 14:53:26 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	value_d(t_arg *specs, LL value)
{
	if (specs->l == 2)
		specs->data_len = get_lllen((LL)value);
	else if (specs->l == 1)
		specs->data_len = get_llen((L)value);
	else if (specs->h == 2)
		specs->data_len = get_len((signed char)value);
	else if (specs->h == 1)
		specs->data_len = get_len((short int)value);
	else
		specs->data_len = get_len((int)value);
}

void	value_x(t_arg *specs, LL value)
{
	if (specs->l == 2)
		specs->conv_val = convert((ULL)value, 16, BASE_16_LOW);
	else if (specs->l == 1)
		specs->conv_val = convert((UL)value, 16, BASE_16_LOW);
	else if (specs->h == 2)
		specs->conv_val = convert((unsigned char)value, 16, BASE_16_LOW);
	else if (specs->h == 1)
		specs->conv_val = convert((short unsigned int)value, 16, BASE_16_LOW);
	else
		specs->conv_val = convert((unsigned int)value, 16, BASE_16_LOW);
	specs->data_len = ft_strlen(specs->conv_val);
}

void	value_xx(t_arg *specs, LL value)
{
	if (specs->l == 2)
		specs->conv_val = convert((ULL)value, 16, BASE_16_UP);
	else if (specs->l == 1)
		specs->conv_val = convert((UL)value, 16, BASE_16_UP);
	else if (specs->h == 2)
		specs->conv_val = convert((unsigned char)value, 16, BASE_16_UP);
	else if (specs->h == 1)
		specs->conv_val = convert((short unsigned int)value, 16, BASE_16_UP);
	else
		specs->conv_val = convert((unsigned int)value, 16, BASE_16_UP);
	specs->data_len = ft_strlen(specs->conv_val);
}

void	value_o(t_arg *specs, LL value)
{
	if (specs->l == 2)
		specs->conv_val = convert((ULL)value, 8, BASE_8);
	else if (specs->l == 1)
		specs->conv_val = convert((UL)value, 8, BASE_8);
	else if (specs->h == 2)
		specs->conv_val = convert((unsigned char)value, 8, BASE_8);
	else if (specs->h == 1)
		specs->conv_val = convert((short unsigned int)value, 8, BASE_8);
	else
		specs->conv_val = convert((unsigned int)value, 8, BASE_8);
	specs->data_len = ft_strlen(specs->conv_val);
}

void	value_u(t_arg *specs, ULL value)
{
	if (specs->l == 2)
		specs->data_len = get_ulllen((ULL)value);
	else if (specs->l == 1)
		specs->data_len = get_ullen((UL)value);
	else if (specs->h == 2)
		specs->data_len = get_ulen((unsigned char)value);
	else if (specs->h == 1)
		specs->data_len = get_ulen((unsigned short int)value);
	else
		specs->data_len = get_ulen((unsigned int)value);
}
