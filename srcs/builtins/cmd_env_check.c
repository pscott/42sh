/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschoenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:38:04 by aschoenh          #+#    #+#             */
/*   Updated: 2019/06/12 15:38:08 by aschoenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftsh.h"

static	int		print_usage_env(char c)
{
	ft_dprintf(2, "env: illegal option -- %c\n", c);
	ft_dprintf(2, "usage: env [-i] [name=value ...]");
	ft_dprintf(2, " [utility [argument ...]]\n");
	return (-1);
}

int				check_env_flags(char **argv, int *pos)
{
	int		i;
	int		k;
	int		mode;

	i = 1;
	mode = 0;
	while (argv[i] && argv[i][0] == '-')
	{
		k = 1;
		while (argv[i][k])
		{
			if (argv[i][k] == 'i')
				mode = 1;
			else
				return (print_usage_env(argv[i][k]));
			k++;
		}
		i++;
	}
	*pos = i;
	return (mode);
}
