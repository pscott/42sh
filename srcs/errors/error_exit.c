#include "libft.h"
#include "libterm.h"
#include "errors.h"

void			error_exit(int errno, char *err_str, char *err_file)
{
	//g_sh.error = 1;
	if (err_file)
		ft_printf("%s: %s", err_str, err_file);
	else
		ft_printf("%s", err_str);
	print_line();
	//my_free_list_malloced
	//sleep(1);
	exit(errno);
}
