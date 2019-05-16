/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:54:40 by pscott            #+#    #+#             */
/*   Updated: 2019/05/16 19:15:33 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libterm.h"

void	term_putstr_endline(char *str, int fd)
{
	ft_putstr_fd(str, fd);
	print_line(0);
}

int		print_line(int fd)
{
	if (isatty(STDIN_FILENO) == 0)
		write(fd, "\n", 1);
	else
	{
		write(0, "\r", 1);
		execute_str(PRINT_LINE);
	}
	return (1);
}
