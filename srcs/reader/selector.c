#include "line_editing.h"
#include "input.h"

void	selector(t_st_cmd *st_cmd, char *buf, t_vars *vars)
{
	if (check_for_arrows(st_cmd, buf, vars) || check_for_words(st_cmd, buf))
	{
		vars->select_end = st_cmd->st_txt->tracker;
		reposition_cursor(st_cmd, 0);
		write_st_cmd(st_cmd);
		reposition_cursor(st_cmd, vars->select_end);
	}
}
