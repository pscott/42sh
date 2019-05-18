#include "42sh.h"

/*
** Utility function to reset the terminal settings and exit
*/

void	clean_exit(int exitno)
{
	reset_terminal_settings();
	exit(exitno);
}
