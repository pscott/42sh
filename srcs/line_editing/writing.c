#include "line_editing.h"

/*
**	Function that scrolls down if need be and writes the
**	remainder of the line.
*/

int			move_down(t_st_cmd *st_cmd)
{
	if (isatty(STDIN_FILENO) == 0)
		return (0);
	if (st_cmd->start_pos.row + st_cmd->relative_pos.row
			>= st_cmd->window->ws_row)
	{
		move_cursor(st_cmd->window->ws_col, st_cmd->window->ws_row);
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

void		go_back_to_start(t_st_cmd *st_cmd)
{
	int		row;

	if (isatty(STDIN_FILENO) == 0)
		return ;
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

void		write_from_start(t_st_cmd *st_cmd)
{
	size_t tmp;

	if (isatty(STDIN_FILENO) == 0)
		return ;
	st_cmd = get_first_st_cmd(st_cmd);
	while (st_cmd)
	{
		execute_str(CLEAR_BELOW);
		retrieve_pos(&st_cmd->start_pos);
		tmp = st_cmd->st_txt->tracker;
		st_cmd->st_txt->tracker = 0;
		init_relative_pos(st_cmd);
		print_prompt(st_cmd);
		write_st_cmd(st_cmd);
		st_cmd->st_txt->tracker = tmp;
		if ((st_cmd = st_cmd->next))
		{
			get_pos(st_cmd, st_cmd->st_txt->data_size);
			move_down(st_cmd);
			execute_str(PRINT_LINE);
			execute_str(BEGIN_LINE);
		}
	}
}

/*
**	Function that writes the current line, starting at tracker. If a new line
**	is printed, moves down and prints every line and st_cmd following the
**	current line.
*/

int			write_line(t_st_cmd *cmd)
{
	size_t		i;

	if (isatty(STDIN_FILENO) == 0)
		return (0);
	i = -1;
	while ((cmd->st_txt->tracker + ++i) < cmd->st_txt->data_size
		&& cmd->st_txt->txt[cmd->st_txt->tracker + i] != '\n')
	{
		write(STDIN_FILENO, &cmd->st_txt->txt[cmd->st_txt->tracker + i], 1);
		get_pos(cmd, cmd->st_txt->data_size - 1);
		if ((cmd->start_pos.row + cmd->relative_pos.row)
			> cmd->window->ws_row
			|| cmd->relative_pos.col == cmd->window->ws_col - 1)
		{
			move_down(cmd);
			get_pos(cmd, cmd->st_txt->tracker + i);
			reposition_cursor(cmd);
		}
	}
	get_pos(cmd, cmd->st_txt->tracker);
	if (cmd->st_txt->txt[cmd->st_txt->tracker + i] == '\n'
		&& cmd->st_txt->txt[cmd->st_txt->tracker + i + 1])
		return (++i);
	execute_str(CLEAR_BELOW);
	return (0);
}

/*
**	Function that writes every line in the st_cmd, starting form
**	tracker
*/

void		write_st_cmd(t_st_cmd *st_cmd)
{
	size_t	step;

	if (isatty(STDIN_FILENO) == 0)
		return ;
	while ((step = write_line(st_cmd)))
	{
		move_down(st_cmd);
		st_cmd->st_txt->tracker += step;
		get_pos(st_cmd, st_cmd->st_txt->tracker);
		reposition_cursor(st_cmd);
	}
}
