#include "line_editing.h"

/*
**	Writes the char located at tracker, updating cursor_pos.
*/

void	write_char(t_st_cmd *st_cmd)
{
	char	to_write;
	int		selected;
	t_vars	*vars;

	vars = get_vars(NULL);
	to_write = st_cmd->st_txt->txt[st_cmd->st_txt->tracker];
	selected = vars->select_mode
		&& ((st_cmd->st_txt->tracker >= vars->select_end
			&& st_cmd->st_txt->tracker <= vars->select_start)
		|| (st_cmd->st_txt->tracker >= vars->select_start
			&& st_cmd->st_txt->tracker <= vars->select_end));
	if (selected)
		execute_str(HIGHLIGHT);
	write(TERM_FD, &to_write, 1);
	if (selected)
		execute_str(NO_HIGHLIGHT);
	if (st_cmd->cursor_pos.col == st_cmd->window->ws_col - 1)
		execute_str(MOVE_DOWN);
	increment_pos(to_write, &st_cmd->cursor_pos, st_cmd->window);
	st_cmd->st_txt->tracker++;
}

/*
**	Writes the st_cmd starting from TRACKER position.
**	Moves the tracker and updates the cursor_position.
*/

void	write_st_cmd(t_st_cmd *st_cmd)
{
	if (!isatty(STDIN_FILENO))
		return ;
	execute_str(INVISIBLE);
	while (st_cmd->st_txt->tracker != st_cmd->st_txt->data_size)
		write_char(st_cmd);
	execute_str(VISIBLE);
}

/*
** Writes back every st_cmd starting from the first one.
** Starts by going back on screen to the beginning of the first st_cmd
** then writes everything.
*/

void	write_from_start(t_st_cmd *st_cmd)
{
	size_t		tmp;
	t_st_cmd	*prev;

	if (!isatty(STDIN_FILENO))
		return ;
	tmp = st_cmd->st_txt->tracker;
	prev = NULL;
	st_cmd = go_back_to_start(st_cmd);
	execute_str(CLEAR_BELOW);
	while (st_cmd)
	{
		st_cmd->st_txt->tracker = 0;
		print_prompt(st_cmd);
		write_st_cmd(st_cmd);
		prev = st_cmd;
		st_cmd = st_cmd->next;
	}
	if (prev && prev->st_txt)
		prev->st_txt->tracker = tmp;
}
