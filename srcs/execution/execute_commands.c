#include "builtins.h"
#include "execution.h"
#include "cmd_parsing.h"
#include "hashmap.h"
#include "errors.h"
#include "env.h"
#include "signals.h"

static int			access_and_exec(char *cmd_path, char **argv,
	int have_assign, t_vars *vars)
{
	int				access;

	if ((access = check_access(cmd_path)) == 0)
	{
		execve(cmd_path, (char*const*)argv, (char*const*)vars->env_vars);
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
	if (have_assign)
	{
		ft_memdel_ntab(&vars->env_vars);
		vars->env_vars = get_ntab_cpy(vars->env_save);
		ft_memdel_ntab(&vars->env_save);
	}
	return (access);
}

static int			in_fork_builtin(char **argv, t_vars *vars,
	t_cmd_id cmd_id)
{
	int ret;

	ret = exec_builtins(argv, vars, cmd_id);
	ft_free_ntab(argv);
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

static int			execute_argv(char **argv, int have_assign, t_vars *vars)
{
	t_cmd_id		cmd_id;
	char			*cmd_path;

	if (!argv || !argv[0])
		return (1);
	else if (ft_strchr(argv[0], '/'))
		cmd_path = ft_strdup(argv[0]);
	else if ((cmd_id = check_builtins((const char*)argv[0])) != cmd_error)
		return (in_fork_builtin(argv, vars, cmd_id));
	else if ((cmd_path = check_hashmap(argv[0], vars->hashmap, hash_check)))
	{
		if (!(cmd_path = ft_strdup(cmd_path)))
			clean_exit(1, 1);
	}
	else if ((cmd_path = get_cmd_path(argv[0], vars, 1)))
		;
	else
	{
		ft_strdel(&cmd_path);
		ft_free_ntab(argv);
		return (ERR_CMD);
	}
	return (access_and_exec(cmd_path, argv, have_assign, vars));
}

/*
**	Parses expands and redirections, creates the argv and executes it.
**	Returns 0 if it executed properly ; else returns 1.
**
**	if parse_assignation() find assignations:
**	- copy current env into env_cpy
**	- apply assignation to the cpy
**	- exec
**	- restore old env
**	send 'have assign' to next exec func to restore env
*/

int					parse_and_exec(t_token *token_head, int in,
	int out)
{
	char			**argv;
	int				ret;
	int				have_assign;
	t_vars			*vars;

	redirect(in, STDIN_FILENO, 0);
	redirect(out, STDOUT_FILENO, 0);
	vars = get_vars(NULL);
	argv = NULL;
	if ((ret = parse_expands(token_head, vars)) != 0)
		return (ret);
	if ((ret = parse_redirections(token_head, 0)) > 0)
		return (ret);
	if ((have_assign = parse_assignation(token_head, vars)))
	{
		vars->env_save = get_ntab_cpy(vars->env_vars);
		apply_assignation_to_ntab(&vars->assign_tab, &vars->env_vars);
	}
	if ((ret = get_argv_from_token_lst(token_head, &argv) > 0))
		return (0);
	return (execute_argv(argv, have_assign, vars));
}
