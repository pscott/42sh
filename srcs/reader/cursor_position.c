#include "tosh.h"
#include "reader.h"
#include "history.h"

void		update_start_pos(t_st_cmd *st_cmd) // might be useless
{
	st_cmd = get_first_st_cmd(st_cmd);
	while (st_cmd)
	{
		st_cmd->start_pos.row--;
		st_cmd = st_cmd->next;
	}
}

/*
**	Function that places the cursor on screen according to the current input
*/

void		reposition_cursor(t_st_cmd *st_cmd)
{
	move_cursor(st_cmd->start_pos.col + st_cmd->relative_pos.col,
			st_cmd->start_pos.row + st_cmd->relative_pos.row);
}
