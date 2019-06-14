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
	restore_init_cursor();
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
	if (!(st_cmd = get_st_cmd(NULL)))
		return ;
	st_cmd = get_last_st_cmd(st_cmd);
	if (st_cmd->st_txt->txt)
		*st_cmd->st_txt->txt = '\x03';
	if ((vars = get_vars(NULL)))
		vars->cmd_value = 1;
	if (isatty(TERM_FD))
		write(TERM_FD, "^C", 2);
	reset_copy_vars(vars);
	st_cmd->st_txt->tracker = st_cmd->st_txt->data_size;
	reposition_cursor(st_cmd, st_cmd->st_txt->tracker);
	restore_init_cursor();
	execute_str(MOVE_DOWN);
}

/*
**	SIGWINCH
**	Simply writes back the st_cmd on screen
*/

void			sigwinch_handler(int signo)
{
	t_st_cmd		*current_cmd;

	(void)signo;
	signal(SIGWINCH, SIG_IGN);
	if (!(current_cmd = get_st_cmd(NULL)))
		return ;
	current_cmd = get_last_st_cmd(current_cmd);
	update_window_struct(current_cmd->window);
	write_from_start(current_cmd);
	reposition_cursor(current_cmd, current_cmd->st_txt->tracker);
	signal(SIGWINCH, sigwinch_handler);
}

/*
**	SIGCONT
**	Setups terminal settings, and writes back the st cmd.
*/

void			sigcont_handler(int signo)
{
	t_st_cmd	*st_cmd;

	(void)signo;
	setup_terminal_settings();
	if (!(st_cmd = get_st_cmd(NULL)))
		return ;
	sigwinch_handler(signo);
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
