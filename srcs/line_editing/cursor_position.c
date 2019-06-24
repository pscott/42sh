/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:21:14 by penzo             #+#    #+#             */
/*   Updated: 2019/06/24 11:21:18 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

void		increment_pos(char to_write, t_pos *new_pos, struct winsize *window)
{
	if (to_write == '\n' || to_write == '\r'
			|| new_pos->col == (window->ws_col - 1))
	{
		new_pos->col = 0;
		new_pos->row += 1;
	}
	else
		new_pos->col++;
}

/*
**	Moves the cursor to the place it should be if it were on new_tracker,
**	and sets tracker to new_tracker
*/

void		go_to_prompt_start(t_st_cmd *st_cmd)
{
	t_pos	prompt_pos;

	if (!isatty(STDIN_FILENO))
		return ;
	prompt_pos.row = 0;
	prompt_pos.col = 0;
	merge_pos(&prompt_pos, &st_cmd->cursor_pos);
}

t_st_cmd	*go_back_to_start(t_st_cmd *st_cmd)
{
	if (!isatty(STDIN_FILENO))
		return (st_cmd);
	while (st_cmd->prev)
	{
		go_to_prompt_start(st_cmd);
		st_cmd = st_cmd->prev;
	}
	go_to_prompt_start(st_cmd);
	return (st_cmd);
}
