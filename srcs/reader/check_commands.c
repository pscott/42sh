#include "reader.h"

/*
**	Checks and calls the appropriated functions for UP, DOWN, LEFT, RIGHT, HOME
**	and END keys.
*/

int		check_for_arrows(t_st_cmd *st_cmd, const char *buf)
{
	if (ft_strncmp(buf, RIGHTARROW, ARROW_LEN + 1) == 0)
		move_arrow_right(st_cmd);
	else if (ft_strncmp(buf, LEFTARROW, ARROW_LEN + 1) == 0)
		move_arrow_left(st_cmd);
	else if (ft_strncmp(buf, UPARROW, ARROW_LEN + 1) == 0)
		get_previous_history(st_cmd);
	else if (ft_strncmp(buf, DOWNARROW, ARROW_LEN + 1) == 0)
		get_next_history(st_cmd);
	else if (ft_strncmp(buf, HOME, HOME_LEN + 1) == 0)
		go_to_start(st_cmd);
	else if (ft_strncmp(buf, END, END_LEN + 1) == 0)
		go_to_end(st_cmd);
	else
		return (0);
	return (1);
}

int		check_for_quit(const char *buf)
{
	if (ft_strncmp(buf, CTRL_D, 2) == 0)
		return (1);
	else
		return (0);
}

int		check_for_signal(const char *buf)
{
	if (ft_strncmp(buf, CTRL_Z, CTRL_Z_LEN) == 0)
	{
		ft_dprintf(2, "SHOULD BE BACKGROUND");
		print_line();
		return (1);
	}
	else if (ft_strncmp(buf, CTRL_C, CTRL_C_LEN) == 0)
	{
		//ioctl(STDIN_FILENO, TIOCSTI, CTRL_C);
		sigint_handler(SIGINT);
		return (1);
	}
	return (0);
}

int		check_for_enter(const char *buf)
{
	if (ft_strncmp(buf, "\r", 2) == 0 || ft_strncmp(buf, "\n", 2) == 0)
		return (1);
	else
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
			ft_putstr(BELL);
		else
			delete_left(st_cmd);
		return (1);
	}
	else if (ft_strncmp(buf, DEL, DEL_LEN + 1) == 0)
	{
		if (st_cmd->st_txt->tracker >= st_cmd->st_txt->data_size)
			ft_putstr(BELL);
		else
			delete_right(st_cmd);
		return (1);
	}
	else
		return (0);
}
