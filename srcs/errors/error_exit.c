#include "libft.h"
#include "libterm.h"
#include "errors.h"

/*
**	Prints the error_str, and err_file if provided. Exits with errno value.
*/

void		error_exit(int errno, const char *err_str, const char *err_file)
{
	if (err_file)
		ft_dprintf(2, "%s: %s\n", err_str, err_file);
	else
		ft_dprintf(2, "%s\n", err_str);
	exit(errno);
}
