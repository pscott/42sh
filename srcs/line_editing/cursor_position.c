#include "ftsh.h"
#include "line_editing.h"

void	increment_pos(char to_write, t_pos *new_pos, struct winsize *window)
{
	if (to_write == '\n' || to_write == '\r'
			|| new_pos->col == window->ws_col)
		{
			new_pos->col = 0;
			new_pos->row += 1;
		}
	else
		new_pos->col++;
}

/*
**	Moves the cursor to the new_pos position, starting from the old_pos
**	position.
*/

static void	merge_pos(t_pos *new_pos, t_pos *old_pos)
{
	int		x;
	int		y;

	x = old_pos->col - new_pos->col;
	y = old_pos->row - new_pos->row;
	execute_str(INVISIBLE);
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
	execute_str(VISIBLE);
	old_pos->col = new_pos->col;
	old_pos->row = new_pos->row;
}

static void	calculate_st_pos(t_st_cmd *st_cmd, size_t new_tracker, t_pos *new_pos)
{
	size_t	i;
	char	to_write;
	
	i = 0;
	if (!isatty(STDIN_FILENO) || !st_cmd->window->ws_col)
		return ;
	new_pos->col = st_cmd->st_prompt->size % st_cmd->window->ws_col;
	new_pos->row = st_cmd->st_prompt->size / st_cmd->window->ws_col;
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
	calculate_st_pos(st_cmd, new_tracker, &new_pos);
	/*ft_dprintf(2, "NEW_POS: {col: %d, row: %d}\nOLD_POS: {col: %d, row: %d}\n", new_pos.col, new_pos.row, st_cmd->cursor_pos.col, st_cmd->cursor_pos.row);
	sleep(1);*/
	merge_pos(&new_pos, &st_cmd->cursor_pos);
	st_cmd->st_txt->tracker = new_tracker;
}

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
		execute_str(MOVE_UP);
	}
	go_to_prompt_start(st_cmd);
	return (st_cmd);
}


