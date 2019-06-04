#include "builtins.h"
#include "errors.h"

/*
**	Executes the builtin corresponding to the cmd_id parameter (see cmd enums).
**	Returns 1 if it executed something.
**	Returns 0 if there was an error.
**	Updates vars->cmd_value with the corresponding builtin execution value.
**	Use check_builtins before calling exec_builtins
*/

static t_bool	exec_builtins_2(char **argv, t_vars *vars, int cmd_id)
{
	int			ret;

	if (cmd_id == cmd_hash)
	{
		vars->cmd_value = case_hash(argv, vars);
		ret = 1;
	}
	else if (cmd_id == cmd_setenv)
	{
		vars->cmd_value = case_setenv(argv, vars);
		ret = 1;
	}
	else if (cmd_id == cmd_unsetenv)
	{
		vars->cmd_value = case_unsetenv(argv, vars);
		ret = 1;
	}
	else if (cmd_id == cmd_echo)
	{
		vars->cmd_value = case_echo(argv);
		ret = 1;
	}
	else
		ret = 0;
	return (ret);
}

/*
**	TO DO : env is not supposed to do that, to fix
*/
t_bool			exec_builtins(char **argv, t_vars *vars, int cmd_id)
{
	int			ret;

	if (cmd_id == cmd_exit)
		ret = case_exit(argv, &vars->cmd_value);
	else if (cmd_id == cmd_env)
	{
		ft_print_ntab(vars->env_vars);
		ret = 1;
	}
	else if (cmd_id == cmd_cd)
	{
		vars->cmd_value = case_cd(argv, &vars->env_vars);
		ret = 1;
	}
	else if (cmd_id == cmd_type)
	{
		vars->cmd_value = case_type(argv, vars);
		ret = 1;
	}
	else
		ret = exec_builtins_2(argv, vars, cmd_id);
	ft_free_ntab(argv);
	return (ret);
}

/*
**	Checks if argv[0] is a builtin or not. Returns the corresponding enum
**	command value in case of success ; returns 0 on failure.
*/

int			check_builtins(char **argv)
{
	if (ft_strcmp(argv[0], "exit") == 0)
		return (cmd_exit);
	if (ft_strcmp(argv[0], "env") == 0)
		return (cmd_env);
	if (ft_strcmp(argv[0], "cd") == 0)
		return (cmd_cd);
	if (ft_strcmp(argv[0], "hash") == 0)
		return (cmd_hash);
	if (ft_strcmp(argv[0], "type") == 0)
		return (cmd_type);
	if (ft_strcmp(argv[0], "setenv") == 0)
		return (cmd_setenv);
	if (ft_strcmp(argv[0], "unsetenv") == 0)
		return (cmd_unsetenv);
	if (ft_strcmp(argv[0], "echo") == 0)
		return (cmd_echo);
	return (0);
}
