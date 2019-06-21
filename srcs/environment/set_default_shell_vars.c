#include "ftsh.h"
#include "env.h"

void	set_default_shell_vars(t_vars *vars)
{
	char	*str;

	if ((get_varline_from_vartab("PATH", vars->shell_vars) == NULL))
	{
		add_variables("PATH", PATH_DEFAULT_VALUE, &vars->shell_vars);
		add_variables("PATH", PATH_DEFAULT_VALUE, &vars->env_vars);
	}
	if (get_varline_from_vartab("PWD", vars->shell_vars) == NULL)
	{
		if (!(str = getcwd(NULL, 0)))
			ft_dprintf(STDERR_FILENO, "%s: getcwd() failed.\n", SHELL_NAME);
		else
		{
			add_variables("PWD", str, &vars->shell_vars);
			add_variables("PWD", str, &vars->env_vars);
		}
	}
	if (get_varline_from_vartab("TERM", vars->shell_vars) == NULL)
	{
		add_variables("TERM", TERM_DEFAULT_VALUE, &vars->shell_vars);
		add_variables("TERM", TERM_DEFAULT_VALUE, &vars->env_vars);
	}
}
