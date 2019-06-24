/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:21:14 by penzo             #+#    #+#             */
/*   Updated: 2019/06/24 11:21:18 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"
#include "input.h"

int		selector(t_st_cmd *st_cmd, char *buf, t_vars *vars)
{
	if (check_for_arrows(st_cmd, buf, vars) || check_for_words(st_cmd, buf))
	{
		vars->select_end = st_cmd->st_txt->tracker;
		reposition_cursor(st_cmd, 0);
		write_st_cmd(st_cmd);
		reposition_cursor(st_cmd, vars->select_end);
		return (1);
	}
	return (0);
}
