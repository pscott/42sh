#include "libterm.h"

static int	open_and_dup_tty(void)
{
	int		new_tty;
	int		ret;
	char	*name;

	name = ttyname(STDIN_FILENO);
	if (name)
	{
		ret = 0;
		if ((new_tty = open(name, O_WRONLY)) < 0)
			return (1);
		if ((dup2(new_tty, TERM_FD) < 0))
			ret = 1;
		close(new_tty);
		return (ret);
	}
	return (-1);
}

int			reset_terminal_settings(void)
{
	ft_dprintf(2, "resetting\n");
	if (isatty(STDIN_FILENO) == 0)
		return (1);
	close(TERM_FD);
	if ((tcsetattr(STDIN_FILENO, TCSADRAIN, &g_saved_attr) == -1))
		return (err_resetattr());
	return (1);
}

static int	set_non_canonical_mode(struct termios *tattr)
{
	struct termios	term;

	g_isatty = 1;
	ft_memcpy(&term, tattr, sizeof(term));
	term.c_lflag &= ~(ICANON | ECHO | ECHONL | ISIG);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSADRAIN, &term) == -1)
		return (err_setattr());
	tcgetattr(STDIN_FILENO, &g_42sh_attr);
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
	int				new_tty;

	if ((res = open_and_dup_tty()))
		return (res);
	if ((!g_isatty) && (tcgetattr(STDIN_FILENO, &g_saved_attr) == -1))
		return (err_getattr());
	if ((termtype = getenv("TERM")) == NULL)
		return (err_no_env());
	if ((res = tgetent(term_buffer, termtype)) == 0)
		return (err_noentry());
	else if (res == -1)
		return (err_no_database());
	if (check_caps() == 0)
		return (err_caps());
	if (set_non_canonical_mode(&g_saved_attr) == 0)
		return (1);
	return (0);
}
