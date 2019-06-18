#include "builtins.h"
#include "env.h"
#include "errors.h"
#include "execution.h"
#include "signals.h"

/*
**	Function that checks for access rights and returns the corresponding
**	error values.
*/

static	int			env_access_check(char *cmd_path)
{
	int access;

	if ((access = check_access(cmd_path)) != 0)
	{
		if (access == ERR_NOEXIST)
			print_errors(ERR_NOEXIST, ERR_NOEXIST_STR, cmd_path);
		else if (access == ERR_PERM)
			print_errors(ERR_PERM, ERR_PERM_STR, cmd_path);
		return (1);
	}
	return (0);
}

/*
**	Function that tries to execute the argv given as a parameter.
**	Returns the exit status of the command or the error number if the command
**	was not successfully executed.
*/

static int			exec_env_bin(char *cmd_path, char **argv, char **new_env)
{
	pid_t	pid;
	int		status;

	if ((status = env_access_check(cmd_path)) > 0)
		return (status);
	if ((pid = fork()) == -1)
	{
		write(2, "fork error\n", 11);
		clean_exit(1, 0);
	}
	else if (pid == 0)
	{
		reset_terminal_settings();
		execve(cmd_path, (char*const*)argv, (char*const*)new_env);
		print_errors(ERR_EXECUTE, ERR_EXECUTE_STR, cmd_path);
		clean_exit(1, 0);
	}
	else
	{
		setup_terminal_settings();
		signals_setup();
		waitpid(pid, &status, 0);
		status = exit_status(status);
	}
	return (status);
}

int					exec_bin(char **argv)
{
	int		ret;
	char	*cmd_path;
	int		i;
	t_vars	*vars;

	vars = get_vars(NULL);
	if (!vars)
		return (1);
	ret = 0;
	i = 0;
	if (!(cmd_path = get_cmd_path(argv[i], vars->env_vars, 1)))
		return (1);
	ret = exec_env_bin(cmd_path, argv, vars->env_vars);
	ft_strdel(&cmd_path);
	return (ret);
}
