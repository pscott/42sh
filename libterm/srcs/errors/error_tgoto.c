#include "libterm.h"

int		err_tgoto(char *cap)
{
	ft_dprintf(2, "error: failed to use tgoto with \"%s\" cap.\n", cap);
	return (1);
}
