/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_settings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:54:40 by pscott            #+#    #+#             */
/*   Updated: 2019/06/06 19:14:25 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libterm.h"

static int	open_and_dup_tty(int need_dup)
{
	int new_tty;

	if (need_dup)
	{
		if ((new_tty = open(ttyname(STDIN_FILENO), O_WRONLY)) < 0)
			return (-1);
		if ((dup2(STDIN_FILENO, new_tty) < 0))
			return (1);
		close(new_tty);
	}
	return (0);
}

int			reset_terminal_settings(void)
{
	if (isatty(STDIN_FILENO) == 0)
		return (1);
	if ((tcsetattr(STDIN_FILENO, TCSANOW, &g_saved_attr) == -1))
		return (err_resetattr());
	return (1);
}

static int	set_non_canonical_mode(struct termios *tattr)
{
	tattr->c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR
			| ICRNL | IXON);
	tattr->c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);
	tattr->c_cflag &= ~(CSIZE | PARENB);
	tattr->c_cflag |= CS8;
	tattr->c_cc[VMIN] = 1;
	tattr->c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSAFLUSH, tattr) == -1)
		return (err_setattr());
	return (1);
}

/*
**	Setups up the terminal settings : checking for all used capacities,
**	saving the current terminal attributes in g_saved_attr.
**	Returns 0 on success
**	Else returns error number.
*/

int			setup_terminal_settings(int need_dup)
{
	char			term_buffer[2048];
	char			*termtype;
	int				res;
	struct termios	tattr;
	int				new_tty;

	if ((res = open_and_dup_tty(need_dup)))
		return (res);
	if ((tcgetattr(STDIN_FILENO, &g_saved_attr) == -1))
		return (err_getattr());
	if ((termtype = getenv("TERM")) == NULL)
		return (err_no_env());
	if ((res = tgetent(term_buffer, termtype)) == 0)
		return (err_noentry());
	else if (res == -1)
		return (err_no_database());
	if ((tcgetattr(STDIN_FILENO, &tattr) == -1))
		return (err_getattr());
	if (check_caps() == 0)
		return (err_caps());
	if (set_non_canonical_mode(&tattr) == 0)
		return (1);
	return (0);
}
