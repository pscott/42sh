/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschoenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:38:21 by aschoenh          #+#    #+#             */
/*   Updated: 2019/06/12 15:38:21 by aschoenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libterm.h"

int		put_special_fd(int c)
{
	return (write(TERM_FD, &c, 1));
}

int		execute_str(char *cap)
{
	char	buf[50];
	char	*cap_str;
	char	*ap;

	if (isatty(TERM_FD) == 0)
		return (0);
	ap = buf;
	if (cap && (cap_str = tgetstr(cap, &ap)))
	{
		tputs(buf, 1, put_special_fd);
		return (1);
	}
	else
		return (err_tgoto(cap));
}
