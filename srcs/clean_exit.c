#include "42sh.h"

/*
** Utility function to reset the terminal settings and exit
*/

void	clean_exit(int exitno)
{
	save_reset_stdfd(0);
	reset_terminal_settings();
	exit(exitno);
}
