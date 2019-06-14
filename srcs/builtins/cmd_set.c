#include "ftsh.h"
#include "builtins.h"

int		case_set(char **argv, t_vars *vars)
{
	if (ft_ntab_len((const char**)argv) > 1)
	{
		ft_dprintf(2, "%s: set usage: set\n", SHELL_NAME);
		return (1);
	}
	if (vars->shell_vars) 
	{
		ft_print_ntab(vars->shell_vars);
		return (0);
	}
	return (1);
}
