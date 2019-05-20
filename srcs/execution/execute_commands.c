#include "42sh.h"
#include "builtins.h"
#include "execution.h"
#include "libterm.h"
#include "cmd_parsing.h"
#include "errors.h"

static t_bool		execute_argv(char **argv, t_vars *vars)
{
	int		cmd;
	char	*cmd_path;
	int		access;

	
	if (!argv)
		return (0);
	else if (ft_strchr(argv[0], '/'))
		cmd_path = ft_strdup(argv[0]);
	else if ((cmd = check_builtins(argv)))
		return (exec_builtins(argv, vars, cmd));
	else if ((cmd_path = check_hashmap(argv[0], vars->hashmap, hash_check)))
		;
	else if ((cmd_path = get_cmd_path(argv, vars->env_vars)))
		;
	else
	{
		print_errors(ERR_CMD, ERR_CMD_STR, argv[0]);
		return (0);
	}
	if ((access = check_access(cmd_path)) == 0 && reset_terminal_settings())
	{
		execve(cmd_path, (char * const*)argv, (char* const*)vars->env_vars);
		clean_exit(1);
		return (1);
	}
	else
	{
		if (access == ERR_NOEXIST)
			print_errors(ERR_NOEXIST, ERR_NOEXIST_STR, cmd_path);
		else if (access == ERR_PERM)
			print_errors(ERR_PERM, ERR_PERM_STR, cmd_path);
	}
	ft_strdel(&cmd_path);
	return (0);
}

t_bool		parse_and_exec(t_token *token_head, int in, int out, t_vars *vars)
{
	char		**argv;

	redirect(in, STDIN_FILENO);
	redirect(out, STDOUT_FILENO);
	parse_expands(token_head, vars);
	parse_redirections(token_head);
	argv = get_argv_from_token_lst(token_head);
	return (execute_argv(argv, vars));
}
