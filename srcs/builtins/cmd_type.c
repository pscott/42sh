/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschoenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:38:04 by aschoenh          #+#    #+#             */
/*   Updated: 2019/06/12 15:38:07 by aschoenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "execution.h"
#include "hashmap.h"

static void			print_error(const char *arg)
{
	ft_dprintf(2, SHELL_NAME);
	ft_dprintf(2, ": type: %s: not found\n", arg);
}

static void			print_hash_case(char *arg, char *path)
{
	ft_dprintf(STDOUT_FILENO, "%s is hashed (%s)\n", arg, path);
}

static void			print_path_case(char *arg, char **path)
{
	ft_dprintf(STDOUT_FILENO, "%s is %s\n", arg, *path);
	ft_strdel(path);
}

/*
**	Returns 0 if it succesfully executed. Else returns 1.
*/

int					case_type(char **argv, t_vars *vars)
{
	unsigned int	i;
	char			*path;
	int				ret;

	if (!argv[1])
		return (0);
	ret = 0;
	i = 0;
	while (argv[++i])
	{
		if (check_builtins(&argv[i]))
			ft_dprintf(STDOUT_FILENO, "%s is a shell builtin\n", argv[i]);
		else if ((path = check_hashmap(argv[i], vars->hashmap, hash_check)))
			print_hash_case(argv[i], path);
		else if ((path = get_cmd_path(argv[i], vars->env_vars, 0)))
			print_path_case(argv[i], &path);
		else
		{
			print_error(argv[i]);
			ret = 1;
		}
	}
	return (ret);
}
