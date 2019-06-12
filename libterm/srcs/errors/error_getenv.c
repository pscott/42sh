/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_getenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschoenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:38:21 by aschoenh          #+#    #+#             */
/*   Updated: 2019/06/12 15:38:21 by aschoenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		err_no_env(void)
{
	ft_putstr_fd("error: no TERM variable found in environment.\n", 2);
	return (1);
}
