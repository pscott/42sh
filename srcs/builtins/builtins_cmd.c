#include "builtins.h"
#include "errors.h"

/*
**	Executes the builtin corresponding to the cmd_id parameter (see cmd enums).
**	Returns 1 if it executed something
**	Returns 0 if there was an error.
**	Updates vars->cmd_value with the corresponding builtin execution value.
**	Use check_builtins before calling exec_builtins
*/

t_bool	exec_builtins(char **argv, t_vars *vars, int cmd_id)
{
	int		ret;

	if (cmd_id == cmd_exit)
		ret = case_exit(argv, &vars->cmd_value);
	else if (cmd_id == cmd_env)
	{
		ft_print_ntab(vars->env_vars); // pls
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
	else if (cmd_id == cmd_hash)
	{
		vars->cmd_value = case_hash(argv, vars);
		ret = 1;
	}
	else
		ret = 0;
	/*if (cmd_id == cmd_setenv) // will need vars
  	return (case_setenv(argv));
	if (cmd_id == cmd_unsetenv)
		return (case_unsetenv(argv));
	if (cmd_id == cmd_echo)
		return (case_echo(argv));*/
	return (ret);
}

/*
**	Checks if argv[0] is a builtin or not. Returns the corresponding enum
**	command value in case of success ; returns 0 on failure.
*/

t_bool	check_builtins(char **argv)
{
	if (ft_strncmp(argv[0], "exit", 5) == 0)
		return (cmd_exit);
	if (ft_strncmp(argv[0], "env", 4) == 0)
		return (cmd_env);
	if (ft_strncmp(argv[0], "cd", 3) == 0)
		return (cmd_cd);
	if (ft_strncmp(argv[0], "hash", 5) == 0)
		return (cmd_hash);
	if (ft_strncmp(argv[0], "type", 5) == 0)
		return (cmd_type);
/*	if (ft_strcmp(argv[0], "setenv") == 0)
		return (cmd_setenv);
	if (ft_strncmp(argv[0], "unsetenv") == 0)
		return (cmd_unsetenv);
	if (ft_strncmp(argv[0], "echo") == 0)
		return (cmd_echo);*/
	return (0);
}
