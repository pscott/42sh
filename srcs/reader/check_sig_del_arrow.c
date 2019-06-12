/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sig_del_arrow.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschoenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:38:02 by aschoenh          #+#    #+#             */
/*   Updated: 2019/06/12 15:38:07 by aschoenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "signals.h"
#include "history.h"
#include "line_editing.h"
#include "builtins.h"

/*
**	Checks and calls the appropriated functions for UPARROW,
**	DOWNARROW, LEFTARROW, RIGHTARROW, HOME and END keys.
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
	else if (ft_strncmp(buf, HOME, HOME_LEN + 1) == 0
		|| ft_strncmp(buf, "\x01", 2) == 0)
		go_to_start(st_cmd);
	else if (ft_strncmp(buf, END, END_LEN + 1) == 0
		|| ft_strncmp(buf, "\x05", 2) == 0)
		go_to_end(st_cmd);
	else if (ft_strncmp(buf, ALT_UP, ALT_UP_LEN + 1) == 0)
		go_up(st_cmd);
	else if (ft_strncmp(buf, ALT_DOWN, ALT_DOWN_LEN + 1) == 0)
		go_down(st_cmd);
	else
		return (0);
	return (1);
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
