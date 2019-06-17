#include "builtins.h"
#include "execution.h"
#include "cmd_parsing.h"
#include "hashmap.h"
#include "errors.h"

static int			access_and_exec(char *cmd_path, char **argv,
	const char **env)
{
	int				access;

	if ((access = check_access(cmd_path)) == 0)
	{
		execve(cmd_path, (char*const*)argv, (char*const*)env);
		print_errors(ERR_EXECUTE, ERR_EXECUTE_STR, cmd_path);
	}
	else
	{
		if (access == ERR_NOEXIST)
			print_errors(ERR_NOEXIST, ERR_NOEXIST_STR, cmd_path);
		else if (access == ERR_PERM)
			print_errors(ERR_PERM, ERR_PERM_STR, cmd_path);
	}
	ft_strdel(&cmd_path);
	ft_free_ntab(argv);
	return (access);
}

static int			in_fork_builtin(char **argv, t_vars *vars,
	t_cmd_id cmd_id)
{
	int ret;

	ret = exec_builtins(argv, vars, cmd_id);
	if (cmd_id == cmd_exit && ret == 1)
		clean_exit(vars->cmd_value, 0);
	return (ret);
}

/*
**	Execute the argv, first checking if the cmd contains a '/', or if it is
**	a builtin, if it is in the hashmap, or in the PATH. If it is not found, an
**	error message is printed.
**	Returns 0 if something was executed ; else, returns the corresponding error
**	number.
*/

static int			execute_argv(char **argv, t_vars *vars)
{
	t_cmd_id		cmd_id;
	char			*cmd_path;

	if (!argv || !argv[0])
		return (1);
	else if (ft_strchr(argv[0], '/'))
		cmd_path = ft_strdup(argv[0]);
	else if ((cmd_id = check_builtins(argv)))
		return (in_fork_builtin(argv, vars, cmd_id));
	else if ((cmd_path = check_hashmap(argv[0], vars->hashmap, hash_check)))
	{
		if (!(cmd_path = ft_strdup(cmd_path)))
			clean_exit(1, 1);
	}
	else if ((cmd_path = get_cmd_path(argv[0], vars->env_vars, 1)))
		;
	else
	{
		ft_strdel(&cmd_path);
		ft_free_ntab(argv);
		return (ERR_CMD);
	}
	return (access_and_exec(cmd_path, argv, (const char**)vars->env_vars));
}

/*
**	Parses expands and redirections, creates the argv and executes it.
**	Returns 0 if it executed properly ; else returns 1.
*/

int					parse_and_exec(t_token *token_head, int in,
	int out, t_vars *vars)
{
	char			**argv;
	int				ret;

	redirect(in, STDIN_FILENO, 0);
	redirect(out, STDOUT_FILENO, 0);
	argv = NULL;
	if ((ret = parse_expands(token_head, vars)) != 0)
		return (ret);
	if ((ret = parse_redirections(token_head, 0)) > 0)
		return (ret);
	//TODO parse_assign() here
	parse_assignation(token_head, vars);
	if ((ret = get_argv_from_token_lst(token_head, &argv) > 0))
		return (0);
	ft_printf("*******\n");
	ft_print_ntab(argv);//debug
	ft_printf("*******\n");
	return (execute_argv(argv, vars));
}
