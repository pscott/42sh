/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:21:14 by penzo             #+#    #+#             */
/*   Updated: 2019/06/24 11:21:18 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftsh.h"
#include <sys/stat.h>

int		case_echo(char **argv)
{
	int			i;
	struct stat	buf;

	i = 1;
	if (fstat(STDOUT_FILENO, &buf) == -1)
	{
		ft_dprintf(2, SHELL_NAME ": echo: write error: Bad file descriptor\n");
		return (1);
	}
	while (argv[i])
	{
		ft_dprintf(STDOUT_FILENO, "%s", argv[i]);
		i++;
		if (argv[i])
			ft_putchar(' ');
	}
	ft_putchar('\n');
	return (0);
}
