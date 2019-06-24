/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_down.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:21:14 by penzo             #+#    #+#             */
/*   Updated: 2019/06/24 11:21:18 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

void	go_down(t_st_cmd *st_cmd)
{
	t_pos	old;

	if (!isatty(TERM_FD))
		return ;
	if (st_cmd->st_txt->tracker >= st_cmd->st_txt->data_size)
	{
		st_cmd->st_txt->tracker = st_cmd->st_txt->data_size;
		write(STDIN_FILENO, BELL, 1);
	}
	old.row = st_cmd->cursor_pos.row;
	old.col = st_cmd->cursor_pos.col;
	while (st_cmd->cursor_pos.row != (old.row + 1)
		|| st_cmd->cursor_pos.col != old.col)
	{
		if (st_cmd->st_txt->tracker >= st_cmd->st_txt->data_size)
		{
			st_cmd->st_txt->tracker = st_cmd->st_txt->data_size;
			break ;
		}
		if (st_cmd->cursor_pos.row == (old.row + 1))
			if (st_cmd->st_txt->txt[st_cmd->st_txt->tracker + 1] == '\n')
				break ;
		reposition_cursor(st_cmd, st_cmd->st_txt->tracker + 1);
	}
}
