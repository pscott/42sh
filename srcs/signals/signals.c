#include "reader.h"
#include <signal.h>

/*
** Handler function for terminating (aka dangerous) signals
*/

static void	sig_handler(int signo)
{
	//t_arg_list *lst;

	//lst = lst_addr(NULL);
	execute_str(CLEAR_BELOW);
	reset_terminal_settings();
	//free_list(lst);
	ft_dprintf(STDERR, "Interrupted by signal: %d\n", signo);
	exit(signo);
}

void	sigint_handler(int signo)
{
	t_st_cmd	*st_cmd;

	(void)signo;
	st_cmd = get_st_cmd(NULL); //only modifies local copy ?
	go_to_end(st_cmd);
	reposition_cursor(st_cmd);
	print_line();
/*	st_cmd->st_txt = init_st_txt(NULL);
	st_cmd->st_prompt = init_st_prompt(NULL);
	//free (st_cmd->st_prompt);
	//free(st_cmd->st_txt);
	init_relative_pos(st_cmd);
	//execute_str(CLEAR_BELOW); not clear below but go to end of str and clear below
	print_prompt(st_cmd->st_prompt);*/
}

static void	sigcont_handler(int signo)
{
//	t_print_info	*info;
//	t_arg_list		*lst;

//	info = info_addr(NULL);
//	lst = lst_addr(NULL);
	if (setup_terminal_settings() == 0)
	{
		reset_terminal_settings();
		exit(1);
	}
	execute_str(INVISIBLE);
	execute_str(BEGIN_LINE);
	//get_print_info(lst, info);
	//print_list(lst, info);
	signal_setup();
	(void)signo;
}

static void	sigwinch_handler(int signo)
{
	t_st_cmd	*st_cmd;

//	signal(SIGWINCH, SIG_IGN);
	st_cmd = get_st_cmd(NULL);
	update_window_struct(&st_cmd->window);
	go_back_to_start(st_cmd);
	st_cmd = get_first_st_cmd(st_cmd);
	write_from_start(st_cmd);
	get_pos(st_cmd, st_cmd->st_txt->tracker);
	reposition_cursor(st_cmd);
	(void)signo;
	signal(SIGWINCH, sigwinch_handler);
}

void		sigtstp_handler(int signo)
{
	(void)signo;
	execute_str(CLEAR_BELOW);
	reset_terminal_settings();
	signal(SIGTSTP, SIG_DFL);
	ioctl(STDIN, TIOCSTI, "\x1a");
}

/*
** Setting up signal functions.
** KILL and STOP are not handled, and WILL leave you with a messy terminal
** Terminating (aka dangerous) signals reset the terminal, and then exit.
** All non-terminating signals are left untouched, except WINCH and CONT
** INT signal does NOT exit the program.
*/

void		reset_dfl(void)
{
	signal(SIGWINCH, SIG_DFL);
	signal(SIGCONT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGHUP, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGILL, SIG_DFL);
	signal(SIGTRAP, SIG_DFL);
	signal(SIGABRT, SIG_DFL);
	signal(SIGEMT, SIG_DFL);
	signal(SIGFPE, SIG_DFL);
	signal(SIGBUS, SIG_DFL);
	signal(SIGSEGV, SIG_DFL);
	signal(SIGSYS, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
	signal(SIGALRM, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGXCPU, SIG_DFL);
	signal(SIGXFSZ, SIG_DFL);
	signal(SIGVTALRM, SIG_DFL);
	signal(SIGPROF, SIG_DFL);
/*	signal(SIGUSR1, SIG_DFL);
	signal(SIGUSR2, SIG_DFL);*/
}

void		reset_ign(void)
{
	signal(SIGWINCH, SIG_IGN);
	signal(SIGCONT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGHUP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGILL, SIG_IGN);
	signal(SIGTRAP, SIG_IGN);
	signal(SIGABRT, SIG_IGN);
	signal(SIGEMT, SIG_IGN);
	signal(SIGFPE, SIG_IGN);
	signal(SIGBUS, SIG_IGN);
	signal(SIGSEGV, SIG_IGN);
	signal(SIGSYS, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
	signal(SIGALRM, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGXCPU, SIG_IGN);
	signal(SIGXFSZ, SIG_IGN);
	signal(SIGVTALRM, SIG_IGN);
	signal(SIGPROF, SIG_IGN);
/*	signal(SIGUSR1, SIG_IGN);
	signal(SIGUSR2, SIG_IGN);*/
}


void		signal_setup(void)
{
	signal(SIGWINCH, sigwinch_handler);
	signal(SIGCONT, sigcont_handler);
	signal(SIGTSTP, sigtstp_handler);
	signal(SIGINT, sigint_handler);
	signal(SIGHUP, sig_handler);
	signal(SIGQUIT, sig_handler);
	signal(SIGILL, sig_handler);
	signal(SIGTRAP, sig_handler);
	signal(SIGABRT, sig_handler);
	signal(SIGEMT, sig_handler);
	signal(SIGFPE, sig_handler);
	signal(SIGBUS, sig_handler);
	signal(SIGSEGV, sig_handler);
	signal(SIGSYS, sig_handler);
	signal(SIGPIPE, sig_handler);
	signal(SIGALRM, sig_handler);
	signal(SIGTERM, sig_handler);
	signal(SIGTTOU, sig_handler);
	signal(SIGTTIN, sig_handler);
	signal(SIGXCPU, sig_handler);
	signal(SIGXFSZ, sig_handler);
	signal(SIGVTALRM, sig_handler);
	signal(SIGPROF, sig_handler);
/*	signal(SIGUSR1, sig_handler);
	signal(SIGUSR2, sig_handler);*/
}
