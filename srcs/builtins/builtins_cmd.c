#include "builtins.h"
#include "errors.h"

t_bool	exec_builtins(char **argv, t_vars *vars, int cmd_id)
{
	if (cmd_id == cmd_exit)
		return (case_exit(argv));
	else if (cmd_id == cmd_env)
	{
		ft_print_ntab(vars->env_vars); // pls
		return (0);
	}
	else if (cmd_id == cmd_cd)
	  	return (case_cd(argv, &vars->env_vars));
	else if (cmd_id == cmd_type)
	  	return (case_type(argv, vars));
	else if (cmd_id == cmd_hash)
		return (case_hash(argv, vars));
	/*if (cmd_id == cmd_setenv) // will need vars
  	return (case_setenv(argv));
	if (cmd_id == cmd_unsetenv)
		return (case_unsetenv(argv));
	if (cmd_id == cmd_echo)
		return (case_echo(argv));*/
	return (0);
}

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
