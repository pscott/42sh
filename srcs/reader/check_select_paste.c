/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_select_paste.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:21:14 by penzo             #+#    #+#             */
/*   Updated: 2019/06/24 11:21:18 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

static void		paste_selection(t_st_cmd *st_cmd, t_vars *vars)
{
	if (!vars->copy || vars->select_mode)
		ft_putstr(BELL);
	else
		insert_txt(st_cmd, vars->copy);
}

int				check_select_paste(t_st_cmd *st_cmd, char *buf, t_vars *vars)
{
	if (ft_strequ(buf, ALT_V))
	{
		paste_selection(st_cmd, vars);
		return (1);
	}
	else if (vars->select_mode)
	{
		selector(st_cmd, buf, vars);
		return (1);
	}
	else
		return (0);
}
