#include "input.h"
#include "line_editing.h"
#include "signals.h"

/*
** Setting up signal functions.
** KILL and STOP are not handled, and WILL leave you with a messy terminal
** Terminating (aka dangerous) signals reset the terminal, and then exit.
** All non-terminating signals are left untouched, except WINCH and CONT
** INT signal does NOT exit the program.
*/

void		signals_setup(void)
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
	signal(SIGALRM, sig_handler);
	signal(SIGTERM, sig_handler);
	signal(SIGTTOU, sig_handler);
	signal(SIGTTIN, sig_handler);
	signal(SIGXCPU, sig_handler);
	signal(SIGXFSZ, sig_handler);
	signal(SIGVTALRM, sig_handler);
	signal(SIGUSR1, sig_handler);
	signal(SIGUSR2, sig_handler);
	signal(SIGPROF, sig_handler);
}
