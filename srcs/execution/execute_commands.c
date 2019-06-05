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

/*
**	Execute the argv, first checking if the cmd contains a '/', or if it is
**	a builtin, if it is in the hashmap, or in the PATH. If it is not found, an
**	error message is printed.
**	Returns 0 if something was executed ; else, returns the corresponding error
**	number.
*/

static int			execute_argv(char **argv, t_vars *vars)
{
	int				cmd;
	char			*cmd_path;

	if (!argv)
		return (1);
	else if (ft_strchr(argv[0], '/'))
		cmd_path = ft_strdup(argv[0]);
	else if ((cmd = check_builtins(argv)))
		return (exec_builtins(argv, vars, cmd));
	else if ((cmd_path = check_hashmap(argv[0], vars->hashmap, hash_check)))
	{
		if (!(cmd_path = ft_strdup(cmd_path)))
			ERROR_MEM;
	}
	else if ((cmd_path = get_cmd_path(argv, vars->env_vars, 1)))
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
	if ((ret = parse_expands(token_head, vars)) > 0)//TODO check order
		return (ret);
	reset_terminal_settings();
	if ((ret = parse_redirections(token_head, 0)) > 0)
		return (ret);
	if ((ret = get_argv_from_token_lst(token_head, &argv) > 0))
		return (0);
	return (execute_argv(argv, vars));
}
