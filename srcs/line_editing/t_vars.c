#include "ftsh.h"
#include "env.h"
#include "hashmap.h"

void	free_vars(t_vars *vars)
{
	if (!vars)
		return ;
	ft_free_ntab(vars->env_vars);
	ft_strdel(&vars->copy);
	ft_free_ntab(vars->shell_vars);
	delete_hashmap(vars->hashmap);
}

t_vars	*get_vars(t_vars *new_vars)
{
	static t_vars *vars = NULL;

	if (new_vars)
		vars = new_vars;
	return (vars);
}

/*
**	Utility function to initalize the shell variables, the environement, and
**	the last exit status.
*/

int		init_vars(t_vars *vars, int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	vars->hashmap = init_hashmap(INIT_HASH_SIZE);
	vars->cmd_value = 0;
	vars->shell_vars = NULL;
	vars->verbose = 1;
	vars->copy = NULL;
	get_vars(vars);
	if (!(vars->env_vars = init_env((const char **)env)))
		return (1);
	return (0);
}
