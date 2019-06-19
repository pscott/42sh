#include "line_editing.h"

static void		paste_selection(t_st_cmd *st_cmd, t_vars *vars)
{
	if (!vars->copy || vars->select_mode)
		write(STDIN_FILENO, BELL, 1);
	else
		insert_txt(st_cmd, vars->copy);
}

int		check_select_paste(t_st_cmd *st_cmd, char *buf, t_vars *vars)
{
	if (ft_strequ(buf, ALT_V))
	{
		paste_selection(st_cmd, vars);
		return (1);
	}
	else if (vars->select_mode)
	{
		selector(st_cmd, buf, vars);
		return (1);
	}
	else
		return (0);
}
