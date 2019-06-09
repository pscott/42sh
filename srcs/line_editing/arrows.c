#include "input.h"
#include "line_editing.h"

void	move_arrow_right(t_st_cmd *st_cmd)
{
	t_st_txt	*st_txt;

	st_txt = st_cmd->st_txt;
	if (st_txt->tracker < st_txt->data_size)
		reposition_cursor(st_cmd, st_cmd->st_txt->tracker + 1);
	else
		ft_putstr(BELL);
}

void	move_arrow_left(t_st_cmd *st_cmd)
{
	t_st_txt *st_txt;

	st_txt = st_cmd->st_txt;
	if (st_txt->tracker > 0)
		reposition_cursor(st_cmd, st_cmd->st_txt->tracker - 1);
	else
		ft_putstr(BELL);
}

void	go_to_start(t_st_cmd *st_cmd)
{
	reposition_cursor(st_cmd, 0);
}

void	go_to_end(t_st_cmd *st_cmd)
{
	t_pos new_pos;

	calculate_st_pos(st_cmd, st_cmd->st_txt->data_size, &new_pos);
	reposition_cursor(st_cmd, st_cmd->st_txt->data_size);
}
