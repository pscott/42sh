#include "ft_printf.h"
#include "libterm.h"

void	restore_init_cursor(void)
{
	execute_str(VISIBLE);
	write(TERM_FD, FG_DFL, 3);
	execute_str(NO_HIGHLIGHT);
}
