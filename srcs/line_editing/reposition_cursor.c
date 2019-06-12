/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reposition_cursor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschoenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:38:02 by aschoenh          #+#    #+#             */
/*   Updated: 2019/06/12 15:38:07 by aschoenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

static void	move_vertically(int y)
{
	while (y > 0)
	{
		execute_str(MOVE_UP);
		y--;
	}
	while (y < 0)
	{
		execute_str(MOVE_DOWN);
		y++;
	}
}

static void	move_horizontally(int x)
{
	while (x > 0)
	{
		execute_str(MOVE_LEFT);
		x--;
	}
	while (x < 0)
	{
		execute_str(MOVE_RIGHT);
		x++;
	}
}

/*
**	Moves the cursor to the new_pos position, starting from the old_pos
**	position.
*/

void		merge_pos(t_pos *new_pos, t_pos *old_pos)
{
	int		x;
	int		y;

	if ((y = old_pos->row - new_pos->row) < 0)
		old_pos->col = 0;
	x = old_pos->col - new_pos->col;
	move_vertically(y);
	move_horizontally(x);
	old_pos->col = new_pos->col;
	old_pos->row = new_pos->row;
}

/*
**	Fill the new_pos param with the theoretical position of the cursor if it
**	were on new_tracker.
*/

static void	calculate_st_pos(t_st_cmd *st_cmd, size_t new_tracker,
	t_pos *new_pos)
{
	size_t	i;
	char	to_write;

	i = 0;
	if (!isatty(STDIN_FILENO) || !st_cmd->window->ws_col)
		return ;
	while (i < new_tracker)
	{
		to_write = st_cmd->st_txt->txt[i];
		increment_pos(to_write, new_pos, st_cmd->window);
		i++;
	}
}

/*
**	Moves the cursor to the place it should be if it were on new_tracker,
**	and sets tracker to new_tracker
*/

void		reposition_cursor(t_st_cmd *st_cmd, size_t new_tracker)
{
	t_pos	new_pos;

	if (!isatty(STDIN_FILENO))
		return ;
	init_relative_pos(&new_pos, st_cmd->window, st_cmd->st_prompt->size);
	calculate_st_pos(st_cmd, new_tracker, &new_pos);
	merge_pos(&new_pos, &st_cmd->cursor_pos);
	st_cmd->st_txt->tracker = new_tracker;
}
