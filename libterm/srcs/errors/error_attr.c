/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_attr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:54:40 by pscott            #+#    #+#             */
/*   Updated: 2019/04/04 14:54:40 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		err_setattr(void)
{
	ft_putstr_fd("error: failed to set attributes\n", 2);
	return (0);
}

int		err_resetattr(void)
{
	ft_putstr_fd("error: failed to reset attributes\n", 2);
	return (0);
}

int		err_getattr(void)
{
	ft_putstr_fd("error: failed to get attributes\n", 2);
	return (0);
}
