#include "builtins.h"
#include "reader.h" // for clean_exit
#include "ast.h" // for get_cmd_path

static t_bool		execute_argv(char **argv)
{
	int		cmd;
	char	*cmd_path;

	if (!argv)
		return (0);
	if ((cmd = check_builtins(argv)))
		return (exec_builtins(argv, cmd));
	if ((cmd_path = get_cmd_path(argv)) && reset_terminal_settings())
		execve(cmd_path, (char * const*)argv, (char* const*)g_env);
	clean_exit(1);
	return (1);
}

t_bool		execute_in_fork(t_token *token_head, int in, int out, char **env)
{
	char		**argv;

	redirect(in, STDIN_FILENO);
	redirect(out, STDOUT_FILENO);
	parse_expands(token_head, env);
	parse_redirections(token_head);
	argv = get_argv_from_token_lst(token_head);
	return (execute_argv(argv));
}

t_bool		execute_builtin_no_fork(t_token *token_head, char **env)
{
	int		cmd;
	char	**argv;

	parse_expands(token_head, env);
	parse_redirections(token_head);
	argv = get_argv_from_token_lst(token_head);
	if ((cmd = check_builtins(argv)))
	{
		reset_terminal_settings();
		return (exec_builtins(argv, cmd));
	}
	else
		return (1);
}
