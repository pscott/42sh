/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:54:40 by pscott            #+#    #+#             */
/*   Updated: 2019/05/08 13:49:33 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libterm.h"

int		execute_str(char *cap)
{
	char	buf[50];
	char	*cap_str;
	char	*ap;

	ap = buf;
	if (cap && (cap_str = tgetstr(cap, &ap)))
	{
		tputs(buf, 1, ft_putchar);
		return (1);
	}
	else
		return (err_no_str(cap));
}
