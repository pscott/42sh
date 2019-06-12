/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_errors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschoenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:38:05 by aschoenh          #+#    #+#             */
/*   Updated: 2019/06/12 15:38:09 by aschoenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_parsing.h"

int	bad_fd_error(int fd, int mode)
{
	if (mode != -1)
		ft_dprintf(STDERR_FILENO, SHELL_NAME ": %d: bad file descriptor\n", fd);
	return (1);
}

int	ambi_redir_error(char *str, int mode)
{
	if (mode != -1)
		ft_dprintf(STDERR_FILENO, SHELL_NAME ": %s: ambiguous redirect\n", str);
	return (1);
}

int	no_file_error(char *filename, int mode)
{
	if (mode != -1)
		ft_dprintf(2, SHELL_NAME ": %s: No such file or directory\n", filename);
	return (1);
}

int	open_error(char *filename, int mode)
{
	if (mode != -1)
		ft_dprintf(2, "error opening file : %s\n", filename);
	return (1);
}
