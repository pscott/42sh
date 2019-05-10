#include "line_editing.h"

/*
**	Function that scrolls down if need be and write the
**	remainder of the line.
*/

int		move_down(t_st_cmd *st_cmd)
{
	if (st_cmd->start_pos.row + st_cmd->relative_pos.row >= st_cmd->window.ws_row)
	{
		move_cursor(st_cmd->window.ws_col, st_cmd->window.ws_row);
		execute_str(SCROLL_DOWN);
		update_start_pos(st_cmd);
		return (1);
	}
	return (0);
}

/*
 **	Function that moves the cursor to the start of the first st_cmd, without
 **	using start_pos (useful when window size changes)
 */

void	go_back_to_start(t_st_cmd *st_cmd)
{
	int		row;

	while (st_cmd)
	{
		get_pos(st_cmd, st_cmd->st_txt->data_size);
		row = st_cmd->relative_pos.row;
		get_pos(st_cmd, st_cmd->st_txt->tracker);
		while (row)
		{
			execute_str(MOVE_UP);
			row--;
		}
		execute_str(BEGIN_LINE);
		st_cmd = st_cmd->prev;
	}
}

void	write_from_start(t_st_cmd *st_cmd)
{
	size_t tmp;

	while (st_cmd)
	{
		execute_str(CLEAR_BELOW);
		retrieve_pos(&st_cmd->start_pos);
		tmp = st_cmd->st_txt->tracker;
		st_cmd->st_txt->tracker = 0;
		init_relative_pos(st_cmd);
		print_prompt(st_cmd->st_prompt);
		write_st_cmd(st_cmd);
		st_cmd->st_txt->tracker = tmp;
		if ((st_cmd = st_cmd->next))
		{
			get_pos(st_cmd, st_cmd->st_txt->data_size);
			move_down(st_cmd);
			print_line();
		}
	}
}

/*
 **	Function that writes the current line, starting at tracker. If a new line
 **	is printed, moves down and prints every line and st_cmd following the
 **	current line.
 */

int		write_line(t_st_cmd *st_cmd)
{
	t_st_txt	*st_txt;
	t_pos		tmp_pos; //legacy ?
	size_t		i;

	st_txt = st_cmd->st_txt;
	i = 0;
	tmp_pos = st_cmd->relative_pos;
	while ((st_txt->tracker + i) < st_txt->data_size && st_txt->txt[st_txt->tracker + i] != '\n')
	{
		write(STDIN_FILENO, &st_txt->txt[st_txt->tracker + i], 1);
		i++;
		get_pos(st_cmd, st_cmd->st_txt->data_size - 1);
		if ((st_cmd->start_pos.row + st_cmd->relative_pos.row) > st_cmd->window.ws_row
				|| st_cmd->relative_pos.col == st_cmd->window.ws_col - 1)
		{
			move_down(st_cmd); // TODO
			get_pos(st_cmd, st_txt->tracker + i);
			reposition_cursor(st_cmd);
			execute_str(CLEAR_BELOW);
		}
	}
	get_pos(st_cmd, st_cmd->st_txt->tracker);
	if (st_txt->txt[st_txt->tracker + i] == '\n' && st_txt->txt[st_txt->tracker + i + 1])
	{
		i++;
		move_down(st_cmd);
		tmp_pos.col = 1;
		tmp_pos.row++;
		return (i);
	}
	execute_str(ERASE_ENDLINE);
	return (0);
	//	write until \n
	//	if end screen  -> evaluate if scroll
	// if scroll : update_pos of all structs
	// else, write everything, updating_pos of following
}

/*
 **	Function that writes every line in the st_cmd, starting form
 **	tracker
 */

void		write_st_cmd(t_st_cmd *st_cmd)
{
	size_t	step;

	while ((step = write_line(st_cmd)))
	{
		st_cmd->st_txt->tracker += step;
		get_pos(st_cmd, st_cmd->st_txt->tracker);
		reposition_cursor(st_cmd);
	}
}
