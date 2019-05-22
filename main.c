#include <stdio.h>
#include <term.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

# define STDIN_FILENO 0
struct termios g_saved_attr;

static int			reset_terminal_settings(void)
{
	if (isatty(STDIN_FILENO) == 0)
		return (1);
//	execute_str(VISIBLE);
	if ((tcsetattr(STDIN_FILENO, TCSANOW, &g_saved_attr) == -1))
		return (0);
	return (1);
}

static int	set_non_canonical_mode(struct termios *tattr)
{
	tattr->c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR
			| ICRNL | IXON);
	tattr->c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG);
	tattr->c_cflag &= ~(CSIZE | PARENB);
	tattr->c_cflag |= CS8;
	tattr->c_cc[VMIN] = 1;
	tattr->c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSAFLUSH, tattr) == -1)
		return (0);
	return (1);
}
int			setup_terminal_settings(void)
{
	char			term_buffer[2048];
	char			*termtype;
	int				res;
	struct termios	tattr;
	int				new_tty;

	if ((new_tty = open(ttyname(STDIN_FILENO), O_WRONLY)) < 0) // need non interactive
		return (0);
	dup2(STDIN_FILENO, new_tty); // protect
	if ((tcgetattr(STDIN_FILENO, &g_saved_attr) == -1))
		return (0);
	if ((termtype = getenv("TERM")) == NULL)
		return (0);
	if ((res = tgetent(term_buffer, termtype)) == 0)
		return (0);
	else if (res == -1)
		return (0);
	if ((tcgetattr(STDIN_FILENO, &tattr) == -1))
		return (0);
	if (set_non_canonical_mode(&tattr) == 0)
		return (0);
	close(new_tty);
	return (1);
}
int	main(void)
{
	setup_terminal_settings();
	printf("salut\nyo");
	reset_terminal_settings();
	return (0);
}
