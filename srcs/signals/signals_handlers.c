#include "input.h"
#include "line_editing.h"
#include "signals.h"

/*
** Handler function for terminating (aka dangerous) signals
*/

 void		sig_handler(int signo)
{
	execute_str(CLEAR_BELOW);
	reset_terminal_settings();
	ft_dprintf(STDERR, "Interrupted by signal: %d\n", signo);
	exit(signo);
}

void			sigint_handler(int signo)
{
	t_st_cmd	*st_cmd;
	t_vars		*vars;

	(void)signo;
	st_cmd = get_st_cmd(NULL); //only modifies local copy ?
	*st_cmd->st_txt->txt = '\x03';
	go_to_end(st_cmd);
	reposition_cursor(st_cmd);
	vars = get_vars(NULL);
	vars->cmd_value = 1;
	write(0, "\n", 1);
	execute_str(CLEAR_BELOW);
}

void		sigcont_handler(int signo)
{
	if (setup_terminal_settings() == 0)
	{
		reset_terminal_settings();
		exit(1);
	}
	execute_str(INVISIBLE);
	execute_str(BEGIN_LINE);
	signal_setup();
	(void)signo;
}

void		sigwinch_handler(int signo)
{
	t_st_cmd	*st_cmd;

	(void)signo;
//	signal(SIGWINCH, SIG_IGN);  in case two occur at the same time
	st_cmd = get_st_cmd(NULL);
	update_window_struct(st_cmd->window);
	go_back_to_start(st_cmd);
	st_cmd = get_first_st_cmd(st_cmd);
	write_from_start(st_cmd);
	get_pos(st_cmd, st_cmd->st_txt->tracker);
	reposition_cursor(st_cmd);
	signal(SIGWINCH, sigwinch_handler);
}

void			sigtstp_handler(int signo)
{
	(void)signo;
	execute_str(CLEAR_BELOW);
	reset_terminal_settings();
	signal(SIGTSTP, SIG_DFL);
	ioctl(STDIN, TIOCSTI, "\x1a"); // non-interactive ?
}
