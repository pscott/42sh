#ifndef SIGNALS_H
# define SIGNALS_H

# include "ftsh.h"
# include <signal.h>
# include <sys/ioctl.h>

void	sig_handler(int signo);
void	sigint_handler(int signo);
void	sigcont_handler(int signo);
void	sigwinch_handler(int signo);
void	sigtstp_handler(int signo);
void	signals_setup(void);

#endif
