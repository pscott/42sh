#ifndef SIGNALS_H
#define SIGNALS_H
# include "42sh.h"
# include <signal.h>
# include <sys/ioctl.h>

void	sig_handler(int signo);
void	sigint_handler(int signo);
void	sigcont_handler(int signo);
void	sigwinch_handler(int signo);
void	sigtstp_handler(int signo);
void	signal_setup(void);
void	reset_ign(void);
void	reset_dfl(void);

#endif
