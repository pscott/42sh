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
		ft_dprintf(2, "fork error\n");
		clean_exit(1, FORCE);
	}
	else if (pid == 0)
	{
		reset_terminal_settings();
		execve(cmd_path, (char*const*)argv, (char*const*)new_env);
		print_errors(ERR_EXECUTE, ERR_EXECUTE_STR, cmd_path);
		clean_exit(1, FORCE);
	}
	else
	{
		waitpid(pid, &status, 0);
		setup_terminal_settings();
		signals_setup();
		status = exit_status(status);
	}
	return (status);
}

static int			copy_env_and_execute(char **argv, char **new_env, int i)
{
	int		ret;
	char	*cmd_path;

	ret = 0;
	if (!argv[i])
		ft_print_ntab(new_env);
	else
	{
		if (!(cmd_path = get_cmd_path(argv[i], new_env, 1)))
			return (1);
		ret = exec_env_bin(cmd_path, argv + i, new_env);
		ft_strdel(&cmd_path);
	}
	return (ret);
}

static int			setenv_arguments(char **argv, char ***new_env,
		int i)
{
	char				*before;
	char				*after;

	while (argv[i] && ft_strchr(argv[i], '='))
	{
		if (argv[i][0] == '=')
		{
			ft_dprintf(2, "env: %s: Invalid argument\n", argv[i]);
			return (-1);
		}
		after = ft_strchr(argv[i], '=') + 1;
		if (!(before = ft_strndup(argv[i], (size_t)(after - argv[i]) - 1)))
			clean_exit(1, 1);
		set_env_var(before, after, new_env);
		ft_strdel(&before);
		i++;
	}
	return (i);
}

/*
**	POSIX compliant env builtin.
**	`man env` ;)
*/

int					case_env(char **argv, char ***env)
{
	int					i;
	char				**new_env;
	int					ret;

	ret = check_env_flags(argv, &i);
	if (ret == -1)
		return (1);
	else if (ret == 1)
		new_env = NULL;
	else
	{
		if (!env || !*env || !**env)
			new_env = NULL;
		else if (!(new_env = ft_dup_ntab((const char **)(*env))))
			clean_exit(1, 1);
	}
	if ((i = setenv_arguments(argv, &new_env, i)) >= 0)
		ret = copy_env_and_execute(argv, new_env, i);
	ft_free_ntab(new_env);
	return (ret);
}
