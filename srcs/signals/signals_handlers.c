#include "input.h"
#include "line_editing.h"
#include "signals.h"
#include "history.h"

/*
** Handler function for terminating (aka dangerous) signals
*/

void			sig_handler(int signo)
{
	execute_str(CLEAR_BELOW);
	reset_terminal_settings();
	ft_dprintf(STDERR_FILENO, "Interrupted by signal: %d\n", signo);
	exit(signo);
}

/*
**	SIGINT
**	Puts a \x03 at the beginning of txt.
**	Sets the last cmd_value to 1 (error)
**	Prints a newline on terminal
*/

void			sigint_handler(int signo)
{
	t_st_cmd	*st_cmd;
	t_vars		*vars;

	(void)signo;
	st_cmd = get_st_cmd(NULL);
	*st_cmd->st_txt->txt = '\x03';
	vars = get_vars(NULL);
	vars->cmd_value = 1;
	if (isatty(TERM_FD))
		write(TERM_FD, "^C", 2);
	execute_str(PRINT_LINE);
	execute_str(BEGIN_LINE);
	execute_str(CLEAR_BELOW);
}

/*
**	SIGWINCH
**	Simply writes back the st_cmd on screen
*/

void			sigwinch_handler(int signo)
{
	t_st_cmd		*first_cmd;
	t_st_cmd		*current_cmd;

	(void)signo;
	first_cmd = get_st_cmd(NULL);
	current_cmd = get_last_st_cmd(first_cmd);
	update_window_struct(current_cmd->window);
	go_back_to_start(current_cmd);
	write_from_start(first_cmd);
	get_pos(current_cmd, current_cmd->st_txt->tracker);
	reposition_cursor(current_cmd);
	signal(SIGWINCH, sigwinch_handler);
}

/*
**	SIGCONT
**	Setups terminal settings, and writes back the st cmd.
*/

void			sigcont_handler(int signo)
{
	t_st_cmd	*st_cmd;
	int			ret;

	(void)signo;
	if ((ret = setup_terminal_settings()) > 0)
		clean_exit(ret, 0);
	st_cmd = get_st_cmd(NULL);
	st_cmd = get_first_st_cmd(st_cmd);
	write_from_start(st_cmd);
	get_pos(st_cmd, st_cmd->st_txt->tracker);
	reposition_cursor(st_cmd);
}

/*
**	SIGTSTP
**	Clears the screen and resets terminal settings. Then resets the default
**	behavior for signal and simulates the signal with ioctl
*/

void			sigtstp_handler(int signo)
{
	(void)signo;
	execute_str(CLEAR_BELOW);
	reset_terminal_settings();
	signal(SIGTSTP, SIG_DFL);
	ioctl(STDIN_FILENO, TIOCSTI, "\x1a");
}
