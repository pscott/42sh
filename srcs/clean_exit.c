/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschoenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:38:06 by aschoenh          #+#    #+#             */
/*   Updated: 2019/06/12 15:38:10 by aschoenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftsh.h"
#include "history.h"
#include "input.h"

/*
** Utility function to reset the terminal settings and exit
*/

void	clean_exit(int exitno, int malloc_error)
{
	t_st_cmd	*st_cmd;
	t_vars		*vars;

	if (!malloc_error)
	{
		st_cmd = get_st_cmd(NULL);
		vars = get_vars(NULL);
		write_to_history(st_cmd, (const char **)vars->env_vars);
		free_all_st_cmds(&st_cmd);
		free_vars(vars);
	}
	else
		write(2, "\nexiting: malloc error\n", 23);
	reset_terminal_settings();
	exit(exitno);
}
