#ifndef SIGNALS_H
#define SIGNALS_H

# include "42sh.h"
# include <signal.h>
# include <sys/ioctl.h>

void	sigint_handler(int signo);
void	signal_setup(void);
void	reset_ign(void);
void	reset_dfl(void);

#endif
