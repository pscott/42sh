#include "ftsh.h"
#include "line_editing.h"

static void	paste_endline(t_st_cmd *st_cmd, t_vars *vars)
{
	if (!vars->copy)
		ft_putstr(BELL);
	else
		insert_txt(st_cmd, vars->copy);
}

static void	delete_endline(t_st_cmd *st_cmd)
{
	t_st_txt *line;

	line = st_cmd->st_txt;
	ft_bzero(line->txt + line->tracker,
		sizeof((*line->txt) * (line->data_size - line->tracker)));
	if (line->data_size > line->tracker)
		line->data_size -= line->data_size - line->tracker;
	else
		line->data_size = 0;
	execute_str(CLEAR_BELOW);
}

static void	copy_endline(t_st_cmd *st_cmd, t_vars *vars)
{
	ft_strdel(&vars->copy);
	if (!st_cmd->st_txt->txt[st_cmd->st_txt->tracker])
		ft_putstr(BELL);
	else if (!(vars->copy =
			ft_strdup(st_cmd->st_txt->txt
				+ st_cmd->st_txt->tracker)))
		clean_exit(1, 1);
}

static int tmp(t_st_cmd *st_cmd, char *buf, t_vars *vars)
{
	if (ft_strequ(buf, ALT_X))
	{
		copy_endline(st_cmd, vars);
		delete_endline(st_cmd);
		return (1);
	}
	else if (ft_strequ(buf, ALT_C))
	{
		copy_endline(st_cmd, vars);
		return (1);
	}
	else if (ft_strequ(buf, ALT_V))
	{
		paste_endline(st_cmd, vars);
		return (1);
	}
	return (0);
}

/*
**	Checks for copy, paste and cut characters.
*/

int			check_for_select_mode(t_st_cmd *st_cmd, char *buf, t_vars *vars)
{
	if (ft_strequ(buf, F1_KEY))
	{
		vars->select_mode = !vars->select_mode;
		if (vars->select_mode == 0)
		{
			reposition_cursor(st_cmd, 0);
			write_st_cmd(st_cmd);
			reposition_cursor(st_cmd, vars->select_end);
		}
		vars->select_start = st_cmd->st_txt->tracker;
		vars->select_end = st_cmd->st_txt->tracker;
		return (1);
	}
	else if (vars->select_mode)
	{
		selector(st_cmd, buf, vars);
		return (1);
	}
	return (0);
}
