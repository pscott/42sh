#include "builtins.h"
#include "env.h"
#include "ftsh.h"
#include "errors.h"
#include "execution.h"
#include "signals.h"

static	int		env_access_check(char *cmd_path)
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

static int		exec_env_bin(char *cmd_path, char **argv, char **new_env)
{
	pid_t	pid;
	int		status;
	int		ret;

	if ((ret = env_access_check(cmd_path)) > 0)
		return (ret);
	if ((pid = fork()) == -1)
	{
		ft_dprintf(2, "fork error\n");
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
		ret = WIFSIGNALED(status) ? WTERMSIG(status) : WEXITSTATUS(status);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) != SIGINT && WTERMSIG(status) != SIGPIPE)
				ft_dprintf(2, "process terminated, received signal : %d\n",
						WTERMSIG(status));
		}
	}
	return (ret);
}

int				case_env(char **argv, char ***env)
{
	int		i;
	char	**new_env;
	char	*before;
	char	*after;
	char	*cmd_path;
	int		ret;

	i = 1;
	ret = 0;
	if (argv[1] && !ft_strcmp(argv[1], "-i"))
	{
		new_env = NULL;
		i++;
	}
	else
		new_env = ft_dup_ntab((const char **)(*env)); // protect
	while (argv[i] && ft_strchr(argv[i], '='))
	{
		if (argv[i][0] == '=')
		{
			ft_dprintf(2, "env: %s: Invalid argument\n", argv[i]);
			return (1);
		}
		after = ft_strchr(argv[i], '=') + 1;
		if (!(before = ft_strndup(argv[i], after - argv[i] - 1)))
			ERROR_MEM;
		set_env_var(before, after, &new_env);
		i++;
	}
	if (!argv[i])
		ft_print_ntab(new_env);
	else
	{
		if (!(cmd_path = get_cmd_path(argv + i, new_env, 1)))
			return (1);
		ret = exec_env_bin(cmd_path, argv + i, new_env);
	}
	return (ret);
}
