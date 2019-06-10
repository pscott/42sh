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

/*
**	Checks for copy, paste and cut characters.
*/

int			check_for_copy_paste(t_st_cmd *st_cmd, char *buf, t_vars *vars)
{
	if (ft_strncmp(buf, ALT_X, ALT_X_LEN + 1) == 0)
	{
		copy_endline(st_cmd, vars);
		delete_endline(st_cmd);
		return (1);
	}
	else if (ft_strncmp(buf, ALT_C, ALT_C_LEN + 1) == 0)
	{
		copy_endline(st_cmd, vars);
		return (1);
	}
	else if (ft_strncmp(buf, ALT_V, ALT_V_LEN + 1) == 0)
	{
		paste_endline(st_cmd, vars);
		return (1);
	}
	return (0);
}
