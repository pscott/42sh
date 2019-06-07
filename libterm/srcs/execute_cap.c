/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:54:40 by pscott            #+#    #+#             */
/*   Updated: 2019/06/07 16:14:19 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libterm.h"

int		put_special_fd(int c)
{
	return (write(13, &c, 1));
}

int		execute_str(char *cap)
{
	char	buf[50];
	char	*cap_str;
	char	*ap;

	if (isatty(OUTPUT_FD) == 0)
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
