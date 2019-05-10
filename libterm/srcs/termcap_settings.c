/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_settings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:54:40 by pscott            #+#    #+#             */
/*   Updated: 2019/05/10 13:19:50 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libterm.h"

int			reset_terminal_settings(void)
{
	if (isatty(g_tty) == 0)
		return (1);
	execute_str(VISIBLE);
	if ((tcsetattr(g_tty, TCSANOW, &g_saved_attr) == -1))
		return (err_resetattr());
	close(g_tty);
	return (1);
}

static int	set_non_canonical_mode(struct termios *tattr)
{
	tattr->c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR
			| ICRNL | IXON);
	tattr->c_oflag &= ~OPOST;
	tattr->c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);
	tattr->c_cflag &= ~(CSIZE | PARENB);
	tattr->c_cflag |= CS8;
	tattr->c_cc[VMIN] = 1;
	tattr->c_cc[VTIME] = 0;
	if (tcsetattr(g_tty, TCSAFLUSH, tattr) == -1)
		return (err_setattr());
	return (1);
}

static char	**create_cap_array(void)
{
	char	**res;

	if (!(res = (char**)malloc(sizeof(*res) * (NUM_CAPS + 1))))
		return (NULL);
	res[NUM_CAPS] = NULL;
	if (!(res[0] = ft_strdup(BEGIN_LINE))
			|| !(res[1] = ft_strdup(LEFT_CORNER))
			|| !(res[2] = ft_strdup(MOVE_CURSOR))
			|| !(res[3] = ft_strdup(CLEAR))
			|| !(res[4] = ft_strdup(SAVE_CURSOR))
			|| !(res[5] = ft_strdup(CLEAR_BELOW))
			|| !(res[6] = ft_strdup(RESTORE_CURSOR))
			|| !(res[7] = ft_strdup(INVISIBLE))
			|| !(res[8] = ft_strdup(VISIBLE))
			|| !(res[9] = ft_strdup(PRINT_LINE))
			|| !(res[10] = ft_strdup(ERASE_ENDLINE))
			|| !(res[11] = ft_strdup(HIGHLIGHT))
			|| !(res[12] = ft_strdup(NO_HIGHLIGHT))
			|| !(res[13] = ft_strdup(UNDERLINE))
			|| !(res[14] = ft_strdup(NO_UNDERLINE))
			|| !(res[15] = ft_strdup(SCROLL_DOWN))
			|| !(res[16] = ft_strdup(MOVE_UP)))
	{
		ft_free_ntab(res);
		return (NULL);
	}
	return (res);
}

static int	check_caps(void)
{
	char	**caps;
	int		i;

	if (!(caps = create_cap_array()))
	{
		ft_putstr_fd("error: failed to allocate memory\n", 2);
		exit(1);
	}
	i = 0;
	while (i < NUM_CAPS)
	{
		if (tgetstr(caps[i], NULL) == NULL)
		{
			ft_free_ntab(caps);
			return (0);
		}
		i++;
	}
	ft_free_ntab(caps);
	return (1);
}

int			setup_terminal_settings(void)
{
	char			term_buffer[2048];
	char			*termtype;
	int				res;
	struct termios	tattr;

	if ((g_tty = open(ttyname(STDIN_FILENO), O_WRONLY)) < 0) // need non interactive
		return (err_not_terminal() - 1);
	if (isatty(g_tty) == 0)
		return (err_not_terminal() - 1);
	if ((tcgetattr(g_tty, &g_saved_attr) == -1))
		return (err_getattr() - 1);
	if ((termtype = getenv("TERM")) == NULL)
		return (err_no_env() - 1);
	if ((res = tgetent(term_buffer, termtype)) == 0)
		return (err_noentry() - 1);
	else if (res == -1)
		return (err_no_database() - 1);
	if ((tcgetattr(g_tty, &tattr) == -1))
		return (err_getattr() - 1);
	if (check_caps() == 0)
		return (err_caps() - 1);
	if (set_non_canonical_mode(&tattr) == 0)
		return (0);
/*	dup2(STDIN_FILENO, new_fd); // protect
	close(new_fd);*/
	return (1);
}
