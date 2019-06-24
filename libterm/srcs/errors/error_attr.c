/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_attr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:21:29 by penzo             #+#    #+#             */
/*   Updated: 2019/06/24 11:21:29 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		err_setattr(void)
{
	ft_putstr_fd("error: failed to set attributes\n", 2);
	return (1);
}

int		err_resetattr(void)
{
	ft_putstr_fd("error: failed to reset attributes\n", 2);
	return (1);
}

int		err_getattr(void)
{
	ft_putstr_fd("error: failed to get attributes\n", 2);
	return (1);
}
