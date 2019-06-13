#include "line_editing.h"

void	selector(t_st_cmd *st_cmd, char *buf, t_vars *vars)
{
	int		to_add;

	if (ft_strequ(buf, RIGHTARROW))
	{
		if (st_cmd->st_txt->tracker + vars->select_size < st_cmd->st_txt->data_size)
			vars->select_size++;
		else
			ft_putstr(BELL);
	}
	else if (ft_strequ(buf, LEFTARROW))
	{
		if (vars->select_size > 0)
			vars->select_size--;
		else
			ft_putstr(BELL);
	}
	else if (ft_strequ(buf, UPARROW))
	{
		to_add = ft_min(st_cmd->window->ws_col, (int) (st_cmd->st_txt->data_size - vars->select_size));
		if (to_add)
			vars->select_size += to_add;
		else
			ft_putstr(BELL);
	}
	else if (ft_strequ(buf, DOWNARROW))
	{
		to_add = ft_min(vars->select_size, st_cmd->window->ws_col);
		if (to_add)
			vars->select_size += to_add;
		else
			ft_putstr(BELL);
	}
}
