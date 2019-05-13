#include "libft.h"
#include "libterm.h"
#include "errors.h"

int				print_errors(int errno, char *err_str, char *err_file)
{
//	g_sh.error = 1; //
	if (err_file)
		ft_dprintf(STDERR_FILENO, "%s: %s", err_str, err_file);
	else
		ft_dprintf(STDERR_FILENO, "%s", err_str);
	print_line();
	return (errno);
}
