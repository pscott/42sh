#include "builtins.h"
#include "errors.h"

t_bool	exec_builtins(char **argv, t_vars *vars, int cmd_id)
{
	(void)vars;
	reset_terminal_settings(); //change
	/*if (cmd_id == CMD_EXIT)
		return (case_exit(argv));*/
	if (cmd_id == CMD_ENV)
	{
		ft_print_ntab(vars->env_vars); // pls
		return (0);
	}
	else if (cmd_id == CMD_CD)
	  	return (case_cd(argv, &vars->env_vars));
	else if (cmd_id == CMD_HASH)
		return (case_hash(argv, vars));
	/*if (cmd_id == CMD_SETENV) // will need vars
  	return (case_setenv(argv));
	if (cmd_id == CMD_UNSETENV)
		return (case_unsetenv(argv));
	if (cmd_id == CMD_ECHO)
		return (case_echo(argv));*/
	return (0);
}

t_bool	check_builtins(char **argv)
{
/*	if (ft_strcmp(argv[0], "exit") == 0)
		return (CMD_EXIT);*/
	if (ft_strncmp(argv[0], "env", 4) == 0)
		return (CMD_ENV);
	if (ft_strncmp(argv[0], "cd", 3) == 0)
		return (CMD_CD);
	if (ft_strncmp(argv[0], "hash", 5) == 0)
		return (CMD_HASH);
/*	if (ft_strncmp(argv[0], "setenv") == 0)
		return (CMD_SETENV);
	if (ft_strncmp(argv[0], "unsetenv") == 0)
		return (CMD_UNSETENV);
	if (ft_strncmp(argv[0], "echo") == 0)
		return (CMD_ECHO);*/
	return (0);
}
