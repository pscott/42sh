/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_caps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschoenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:38:21 by aschoenh          #+#    #+#             */
/*   Updated: 2019/06/12 15:38:21 by aschoenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libterm.h"

int		err_caps(void)
{
	ft_putstr_fd("error: missing terminal capabilities\n", 2);
	return (1);
}
