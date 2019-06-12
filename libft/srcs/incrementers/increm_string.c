/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   increm_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschoenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:38:17 by aschoenh          #+#    #+#             */
/*   Updated: 2019/06/12 15:38:19 by aschoenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	increm_string(t_arg *specs, int len)
{
	if (specs->string - specs->origin + len >= specs->mall_len - 1)
		realloc_if_necessary(specs, len);
	specs->string += len;
}
