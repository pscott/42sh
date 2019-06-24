/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:21:14 by penzo             #+#    #+#             */
/*   Updated: 2019/06/24 11:21:18 by penzo            ###   ########.fr       */
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
	while (argv[i] && argv[i][0] == '-' && ft_strcmp(argv[i], "--"))
	{
		k = 1;
		while (argv[i][k])
		{
			if (argv[i][k] == 'i')
				mode = 1;
			else if (argv[i][k] != '-')
				return (print_usage_env(argv[i][k]));
			k++;
		}
		i++;
	}
	if (!ft_strcmp(argv[i], "--"))
		i++;
	*pos = i;
	return (mode);
}
