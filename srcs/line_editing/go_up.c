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
	get_pos(st_cmd, st_cmd->st_txt->tracker);
}
