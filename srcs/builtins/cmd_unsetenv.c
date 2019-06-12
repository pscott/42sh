/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unsetenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschoenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:38:04 by aschoenh          #+#    #+#             */
/*   Updated: 2019/06/12 15:38:07 by aschoenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"

/*
**	Unsetenv accepts 1 argument or more, but not 0
*/

int			check_usage_unsetenv(char **argv)
{
	int		i;

	i = 0;
	while (argv[i])
		i++;
	if (i < 2)
	{
		ft_putstr_fd("usage: unsetenv [env name]", 2);
		ft_putchar_fd('\n', 2);
		return (1);
	}
	return (0);
}

/*
**	Unsetenv builtin : remove a variable from the env array
*/

int			case_unsetenv(char **argv, t_vars *vars)
{
	int		i;

	i = 1;
	if (check_usage_unsetenv(argv))
		return (1);
	while (argv[i])
	{
		unset_env_var(argv[i], &vars->env_vars);
		i++;
	}
	return (0);
}
