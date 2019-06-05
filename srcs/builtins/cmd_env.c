#include "builtins.h"
#include "env.h"
#include "ftsh.h"
#include "errors.h"
#include "execution.h"

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

static	void	exec_env_bin(char *cmd_path, char **argv, char **new_env)
{
	pid_t	pid;
	int		status;

	if (env_access_check(cmd_path))
		return ;
	if ((pid = fork()) == -1)
	{
		ft_dprintf(2, "fork error\n");
		clean_exit(-1);
	}
	else if (pid == 0)
	{
		execve(cmd_path, (char*const*)argv, (char*const*)new_env);
		print_errors(ERR_EXECUTE, ERR_EXECUTE_STR, cmd_path);
		clean_exit(-1);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

int				case_env(char **argv, char ***env, t_vars *vars)
{
	int		i;
	char	**new_env;
	char	*before;
	char	*after;
	char	*cmd_path;
	int		cmd;
	char	**argv_cpy;

	i = 1;
	if (argv[1] && !ft_strcmp(argv[1], "-i"))
	{
		new_env = NULL;
		i++;
	}
	else
		new_env = ft_dup_ntab((const char **)(*env));
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
	else if ((cmd = check_builtins(argv + i)))
	{
		argv_cpy = ft_dup_ntab((const char **)argv + i);
		return (exec_builtins(argv_cpy, vars, cmd));
	}
	else
	{
		if (!(cmd_path = get_cmd_path(argv + i, new_env, 1)))
			return (1);
		exec_env_bin(cmd_path, argv + i, new_env);
	}
	return (0);
}
