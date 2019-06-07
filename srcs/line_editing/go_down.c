#include "line_editing.h"

void	go_down(t_st_cmd *st_cmd)
{
	if (!isatty(STDIN_FILENO))
		return ;
	if (st_cmd->st_txt->tracker == st_cmd->st_txt->data_size)
		ft_putstr(BELL);
	else if (st_cmd->st_txt->tracker + st_cmd->window->ws_col
			>= st_cmd->st_txt->data_size)
		st_cmd->st_txt->tracker = st_cmd->st_txt->data_size;
	else
		st_cmd->st_txt->tracker += st_cmd->window->ws_col;
	get_pos(st_cmd, st_cmd->st_txt->tracker);
}
