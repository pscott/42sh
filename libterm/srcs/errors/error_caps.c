/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_caps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:21:29 by penzo             #+#    #+#             */
/*   Updated: 2019/06/24 11:21:29 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libterm.h"

int		err_caps(void)
{
	ft_putstr_fd("error: missing terminal capabilities\n", 2);
	return (1);
}
