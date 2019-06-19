#include "input.h"
#include "line_editing.h"

void	move_arrow_right(t_st_cmd *st_cmd)
{
	t_st_txt	*st_txt;

	st_txt = st_cmd->st_txt;
	if (st_txt->tracker < st_txt->data_size)
		st_cmd->st_txt->tracker++;
	else
		write(STDIN_FILENO, BELL, 1);
}

void	move_arrow_left(t_st_cmd *st_cmd)
{
	t_st_txt *st_txt;

	st_txt = st_cmd->st_txt;
	if (st_txt->tracker > 0)
		st_cmd->st_txt->tracker--;
	else
		write(STDIN_FILENO, BELL, 1);
}

void	go_to_start(t_st_cmd *st_cmd)
{
	st_cmd->st_txt->tracker = 0;
}

void	go_to_end(t_st_cmd *st_cmd)
{
	st_cmd->st_txt->tracker = st_cmd->st_txt->data_size;
}
