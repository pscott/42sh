#include "libft.h"
#include "libterm.h"
#include "errors.h"

int		print_errors(int errno, const char *err_str, const char *err_file)
{
	if (err_file)
		ft_dprintf(STDERR_FILENO, "%s: %s\n", err_str, err_file);
	else
		ft_dprintf(STDERR_FILENO, "%s\n", err_str);
	return (errno);
}
