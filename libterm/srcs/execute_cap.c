/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:54:40 by pscott            #+#    #+#             */
/*   Updated: 2019/06/07 15:00:45 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libterm.h"

int		put_fd_ten(int c)
{
	return (write(10, &c, 1));
}

int		execute_str(char *cap)
{
	char	buf[50];
	char	*cap_str;
	char	*ap;

	if (isatty(STDIN_FILENO) == 0)
		return (0);
	ap = buf;
	if (cap && (cap_str = tgetstr(cap, &ap)))
	{
		tputs(buf, 1, put_fd_ten);
		return (1);
	}
	else
		return (err_tgoto(cap));
}
