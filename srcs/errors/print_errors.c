#include "libft.h"
#include "libterm.h"
#include "errors.h"

int				print_errors(int errno, char *err_str, char *err_file)
{
//	g_sh.error = 1; //
	if (err_file)
		ft_printf("%s: %s", err_str, err_file);
	else
		ft_printf("%s", err_str);
	print_line();
	return (errno);
}
