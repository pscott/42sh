/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_getstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:54:40 by pscott            #+#    #+#             */
/*   Updated: 2019/04/04 14:54:40 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libterm.h"

int		err_no_str(char *cap)
{
	ft_putstr_fd("error: no str corresponding to \"", 2);
	ft_putstr_fd(cap ? cap : "(null)", 2);
	ft_putstr_fd("\" cap.", 2);
	print_line();
	return (0);
}
