/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_up.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschoenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:38:03 by aschoenh          #+#    #+#             */
/*   Updated: 2019/06/12 15:38:07 by aschoenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

void		go_up(t_st_cmd *st_cmd)
{
	if (!isatty(TERM_FD))
		return ;
	if (st_cmd->st_txt->tracker == 0)
		ft_putstr(BELL);
	else if (st_cmd->st_txt->tracker < st_cmd->window->ws_col)
		st_cmd->st_txt->tracker = 0;
	else
		st_cmd->st_txt->tracker -= st_cmd->window->ws_col;
}
