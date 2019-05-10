#include "builtins.h"
#include "ast.h"

int		exec_builtins(char **argv, int cmd_id)
{
	/*if (cmd_id == CMD_EXIT)
		return (case_exit(argv));*/
	if (cmd_id == CMD_ENV)
	{
		ft_print_ntab(g_env);
		return (0);
	}
	if (cmd_id == CMD_CD)
	  	return (case_cd(argv));
	/*if (cmd_id == CMD_SETENV)
  	return (case_setenv(argv));
	if (cmd_id == CMD_UNSETENV)
		return (case_unsetenv(argv));
	if (cmd_id == CMD_ECHO)
		return (case_echo(argv));*/
	return (0);
}

int		check_builtins(char **argv)
{
/*	if (ft_strcmp(argv[0], "exit") == 0)
		return (CMD_EXIT);*/
	if (ft_strcmp(argv[0], "env") == 0)
		return (CMD_ENV);
	if (ft_strcmp(argv[0], "cd") == 0)
		return (CMD_CD);
/*	if (ft_strcmp(argv[0], "setenv") == 0)
		return (CMD_SETENV);
	if (ft_strcmp(argv[0], "unsetenv") == 0)
		return (CMD_UNSETENV);
	if (ft_strcmp(argv[0], "echo") == 0)
		return (CMD_ECHO);*/
	return (0);
}
