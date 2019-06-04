/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_settings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:54:40 by pscott            #+#    #+#             */
/*   Updated: 2019/06/04 13:06:27 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libterm.h"

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

/*
**	Setups up the terminal settings : checking for all used capacities,
**	saving the current terminal attributes in g_saved_attr.
**	Returns 0 on success
**	Else returns error number.
*/

int			setup_terminal_settings(void)
{
	char			term_buffer[2048];
	char			*termtype;
	int				res;
	struct termios	tattr;
	int				new_tty;

	if ((new_tty = open(ttyname(STDIN_FILENO), O_WRONLY)) < 0)
		return (-1);
	if ((dup2(STDIN_FILENO, new_tty) < 0))
		return (1);
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
	close(new_tty);
	return (0);
}
