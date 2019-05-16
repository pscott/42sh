#include "libft.h"
#include "libterm.h"
#include "errors.h"

int				print_errors(int errno, char *err_str, char *err_file)
{
	if (err_file)
		ft_dprintf(STDERR_FILENO, "%s: %s", err_str, err_file);
	else
		ft_dprintf(STDERR_FILENO, "%s", err_str);
	print_line(2);
	return (errno);
}
