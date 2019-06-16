#include "env.h"
#include "builtins.h"

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
			vars->env_vars = delete_line_ntab(index,
				(const char**)vars->env_vars);
			ft_dprintf(2, "KSDJHFKSJDHFKSDJFH\n");
		}
	}
	return (0);
}
