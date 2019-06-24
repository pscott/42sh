/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:21:26 by penzo             #+#    #+#             */
/*   Updated: 2019/06/24 11:21:27 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_atoi_move(char **str)
{
	int		finalnb;

	finalnb = 0;
	while (ft_isdigit(**str))
	{
		finalnb = finalnb * 10 + **str - '0';
		(*str)++;
	}
	return (finalnb);
}
