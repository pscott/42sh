#include "42sh.h"
#include "builtins.h"
#include "execution.h"
#include "libterm.h"
#include "cmd_parsing.h"

static t_bool		execute_argv(char **argv, t_vars *vars)
{
	int		cmd;
	char	*cmd_path;

	if (!argv)
		return (0);
	if ((cmd = check_builtins(argv)))
		return (exec_builtins(argv, vars, cmd));
	if ((cmd_path = get_cmd_path(argv, vars->env_vars)) && reset_terminal_settings())
		execve(cmd_path, (char * const*)argv, (char* const*)vars->env_vars);
	clean_exit(1);
	return (1);
}

t_bool		execute_in_fork(t_token *token_head, int in, int out, t_vars *vars)
{
	char		**argv;

	redirect(in, STDIN_FILENO);
	redirect(out, STDOUT_FILENO);
	parse_expands(token_head, vars->env_vars);
	parse_redirections(token_head);
	argv = get_argv_from_token_lst(token_head);
	return (execute_argv(argv, vars));
}

t_bool		execute_builtin_no_fork(t_token *token_head, t_vars *vars)
{
	int		cmd;
	char	**argv;

	parse_expands(token_head, vars->env_vars);
	parse_redirections(token_head);
	argv = get_argv_from_token_lst(token_head);
	if ((cmd = check_builtins(argv)))
	{
		reset_terminal_settings();
		return (exec_builtins(argv, vars, cmd));
	}
	else
		return (1);
}
