#include "input.h"
#include "signals.h"
#include "history.h"
#include "line_editing.h"
#include "builtins.h"

/*
**	Checks and calls the appropriated functions for UPARROW,
**	DOWNARROW, LEFTARROW, RIGHTARROW, HOME and END keys.
*/

int		check_for_arrows(t_st_cmd *st_cmd, const char *buf, t_vars *vars)
{
	if (ft_strequ(buf, RIGHTARROW))
		move_arrow_right(st_cmd);
	else if (ft_strequ(buf, LEFTARROW))
		move_arrow_left(st_cmd);
	else if (!vars->select_mode && ft_strequ(buf, UPARROW))
		get_previous_history(st_cmd);
	else if (!vars->select_mode && ft_strequ(buf, DOWNARROW))
		get_next_history(st_cmd);
	else if (ft_strequ(buf, HOME)
		|| ft_strequ(buf, "\x01"))
		go_to_start(st_cmd);
	else if (ft_strequ(buf, END)
		|| ft_strequ(buf, "\x05"))
		go_to_end(st_cmd);
	else if (ft_strequ(buf, ALT_UP))
		go_up(st_cmd);
	else if (ft_strequ(buf, ALT_DOWN))
		go_down(st_cmd);
	else
		return (0);
	return (1);
}

int		check_for_signal(const char *buf)
{
	if (ft_strequ(buf, CTRL_C))
	{
		sigint_handler(SIGINT);
		return (input_stop);
	}
	return (0);
}

/*
**	Checks for charactere deletion (backspace or delete keys)
*/

int		check_for_delete(t_st_cmd *st_cmd, char *buf)
{
	if (ft_strncmp(buf, BACKSPACE, BACKSPACE_LEN + 1) == 0)
	{
		if (st_cmd->st_txt->tracker == 0)
			write(STDIN_FILENO, BELL, 1);
		else
			delete_left(st_cmd);
		return (1);
	}
	else if (ft_strncmp(buf, DEL, DEL_LEN + 1) == 0)
	{
		if (st_cmd->st_txt->tracker >= st_cmd->st_txt->data_size)
			write(STDIN_FILENO, BELL, 1);
		else
			delete_right(st_cmd);
		return (1);
	}
	else
		return (0);
}
