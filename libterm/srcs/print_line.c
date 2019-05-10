/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:54:40 by pscott            #+#    #+#             */
/*   Updated: 2019/05/08 13:22:34 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libterm.h"

void	term_putstr_endline(char *str, int fd)
{
	ft_putstr_fd(str, fd);
	print_line();
}

int		print_line(void)
{
	write(STDIN_FILENO, "\r", 1);
	return (execute_str(PRINT_LINE));
}
