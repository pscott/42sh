/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd_options.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:21:14 by penzo             #+#    #+#             */
/*   Updated: 2019/06/24 11:21:18 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*
**	Get right option for cd
*/

static	int		get_arg_final_option(char *str, char *opt)
{
	int		i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'L' && str[i] != 'P')
		{
			*opt = str[i];
			return (1);
		}
		else if (str[i] == 'L' || str[i] == 'P')
			*opt = str[i];
		i++;
	}
	return (0);
}

/*
**	Print cd usage when invalid option
*/

static	int		print_cd_usage_options(char opt)
{
	ft_dprintf(2, SHELL_NAME ": cd: -%c: invalid option\n", opt);
	ft_dprintf(2, "cd: usage: cd [-L | -P] [directory | -]\n");
	return (-1);
}

/*
**	Parse cmd options
*/

int				get_cd_options(char **argv, int *pos)
{
	int		i;
	int		k;
	char	opt;

	i = 1;
	k = 0;
	opt = 0;
	*pos = 1;
	while (argv[i])
	{
		if (argv[i][0] != '-' || (argv[i][0] == '-' && argv[i][1] == '\0'))
			break ;
		(*pos)++;
		if (!ft_strcmp(argv[i], "--"))
			break ;
		if (get_arg_final_option(argv[i], &opt))
			return (print_cd_usage_options(opt));
		i++;
	}
	return (opt);
}

/*
**	Cut the last part of the path
*/

char			*cut_path_string(char *str, int slash)
{
	char	*new;
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	while (str[i])
		i++;
	i--;
	while (i >= 0)
	{
		if (str[i] == '/')
			nb++;
		if (nb == slash)
			break ;
		i--;
	}
	if (i < 1)
		i = 1;
	if (!(new = ft_strndup(str, i)))
		clean_exit(1, 1);
	ft_strdel(&str);
	return (new);
}
