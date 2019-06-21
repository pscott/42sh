#include "env.h"
#include "builtins.h"

/*
** unset
** remove every given arg from both env && shell_vars
** always return 0
*/

int		case_unset(char **argv, t_vars *vars)
{
	int		i;
	int		index;

	i = 0;
	while (argv[++i])
	{
		if ((index = get_envline_index(argv[i], vars->shell_vars)) >= 0)
		{
			vars->shell_vars = delete_line_ntab(index,
				(const char**)vars->shell_vars);
		}
		if ((index = get_envline_index(argv[i], vars->env_vars)) >= 0)
		{
			vars->env_vars = delete_line_ntab(index,
				(const char**)vars->env_vars);
		}
	}
	return (0);
}
