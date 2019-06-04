#include "input.h"
#include "signals.h"
#include "history.h"
#include "line_editing.h"
#include "builtins.h"

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

int		check_for_tab(t_st_cmd *st_cmd, const char *buf, t_vars *vars)
{
	char	*tmp;
	char	*old_txt;
	int		len_tmp;

	len_tmp = 0;
	if (ft_strncmp(buf, "\t", 2) == 0 && isatty(STDIN_FILENO))
	{
		old_txt = st_cmd->st_txt->txt;
		if ((tmp = auto_completion(st_cmd->st_txt->txt, st_cmd->st_txt->tracker, vars))) // alex: tracker ou tracker + 1 ?
		{
			len_tmp = ft_strlen(tmp);		
			if (!(st_cmd->st_txt->txt = ft_strjoin(tmp, st_cmd->st_txt->txt + st_cmd->st_txt->tracker)))
				ERROR_MEM;
			st_cmd->st_txt->data_size = ft_strlen(st_cmd->st_txt->txt);
			st_cmd->st_txt->malloc_size = st_cmd->st_txt->data_size + 1;
			ft_strdel(&old_txt);
		}
		ft_strdel(&tmp);
		move_cursor(st_cmd->start_pos.col, st_cmd->start_pos.row);
		retrieve_pos(&st_cmd->start_pos);
		print_prompt(st_cmd);
		st_cmd->st_txt->tracker = 0;
		write_st_cmd(st_cmd);
		st_cmd->st_txt->tracker = len_tmp;
		get_pos(st_cmd, st_cmd->st_txt->tracker);
		return (1);
	}
	else
		return (0);
}

int		check_for_signal(const char *buf)
{
	if (ft_strncmp(buf, CTRL_Z, CTRL_Z_LEN + 1) == 0)
	{
		sigtstp_handler(SIGTSTP);
		return (input_continue);
	}
	else if (ft_strncmp(buf, CTRL_C, CTRL_C_LEN + 1) == 0)
	{
		sigint_handler(SIGINT);
		return (input_stop);
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
