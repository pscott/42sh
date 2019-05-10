#include "tosh.h"
#include "reader.h"

void	get_pos(t_st_cmd *st_cmd, size_t tracker)
{
	size_t i;

	i = 0;
	init_relative_pos(st_cmd);
	if (tracker > st_cmd->st_txt->data_size)
		return ;
	while (i < tracker)
	{
		if (st_cmd->st_txt->txt[i] == '\n'
			|| st_cmd->relative_pos.col == (st_cmd->window.ws_col - 1))
		{
			st_cmd->relative_pos.col = 0;
			st_cmd->relative_pos.row++;
		}
		else
			st_cmd->relative_pos.col++;
		i++;
	}
}

void	move_arrow_right(t_st_cmd *st_cmd)
{
	t_st_txt	*st_txt;

	st_txt = st_cmd->st_txt;
	if (st_txt->tracker < st_txt->data_size)
	{
		st_txt->tracker++;
		get_pos(st_cmd, st_cmd->st_txt->tracker);
	}
	else
		ft_putstr(BELL);
}

void	move_arrow_left(t_st_cmd *st_cmd)
{
	t_st_txt *st_txt;

	st_txt = st_cmd->st_txt;
	if (st_txt->tracker > 0)
	{
		st_txt->tracker--;
		get_pos(st_cmd, st_cmd->st_txt->tracker);
	}
	else
		ft_putstr(BELL);
}

void	go_to_start(t_st_cmd *st_cmd)
{
	init_relative_pos(st_cmd);
	st_cmd->st_txt->tracker = 0;
}

void	go_to_end(t_st_cmd *st_cmd)
{
	t_st_txt	*st_txt;

	st_cmd = get_last_st_cmd(st_cmd);
	st_txt = st_cmd->st_txt;
	st_txt->tracker = st_txt->data_size;
	get_pos(st_cmd, st_cmd->st_txt->tracker);
}
