/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:53:23 by pscott            #+#    #+#             */
/*   Updated: 2019/04/04 14:53:25 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		get_hlen(short int value)
{
	int len;

	len = 0;
	if (value == -32768)
		return (5);
	if (value < 0)
		value = -value;
	while (value > 0)
	{
		len++;
		value /= 10;
	}
	return (len == 0 ? 1 : len);
}

int		get_hhlen(signed char value)
{
	int len;

	len = 0;
	if (value == -128)
		return (3);
	if (value < 0)
		value = -value;
	while (value > 0)
	{
		len++;
		value /= 10;
	}
	return (len == 0 ? 1 : len);
}

int		get_len(int value)
{
	int len;

	len = 0;
	if (value == -2147483648)
		return (10);
	if (value < 0)
		value = -value;
	while (value > 0)
	{
		len++;
		value /= 10;
	}
	return (len == 0 ? 1 : len);
}

int		get_lllen(LL value)
{
	int len;

	len = 0;
	if ((ULL)value == -9223372036854775808U)
		return (19);
	if (value < 0)
		value = -value;
	while (value > 0)
	{
		len++;
		value /= 10;
	}
	return (len == 0 ? 1 : len);
}

int		get_llen(L value)
{
	int len;

	len = 0;
	if ((ULL)value == -9223372036854775808U)
		return (19);
	if (value < 0)
		value = -value;
	while (value > 0)
	{
		len++;
		value /= 10;
	}
	return (len == 0 ? 1 : len);
}
