#include "builtins.h"
#include "execution.h"
#include "lexer.h"
#include "cmd_parsing.h"
#include "hashmap.h"
#include "env.h"

/*
**	Returns a freshly allocated `fake` argv, because redirections have not
**	been applied.
*/

static char		**fake_argv(t_token *token_head, t_vars *vars)
{
	t_token					*cpy;
	char					**argv;

	argv = NULL;
	vars->verbose = 0;
	cpy = copy_tokens(token_head);
	parse_expands(cpy, vars);
	parse_redirections(cpy, -1);
	parse_assignation(cpy, vars);
	get_argv_from_token_lst(cpy, &argv);
	free_token_list(cpy);
	vars->verbose = 1;
	return (argv);
}

static int		exec_or_hash(char *cmd, t_token *token_head, t_vars *vars)
{
	int			ret;
	t_cmd_id	cmd_id;
	char		*cmd_path;

	if (ft_strchr(cmd, '/'))
		ret = -1;
	else if ((cmd_id = check_builtins((const char*)cmd)) != cmd_error)
		ret = exec_no_pipe_builtin(token_head, vars, cmd_id);
	else if ((cmd_path = check_hashmap(cmd, vars->hashmap, hash_exec)))
		ret = -1;
	else
	{
		if ((cmd_path = get_cmd_path(cmd, vars, 0)))
		{
			add_to_hashmap(cmd, cmd_path, &vars->hashmap);
			check_hashmap(cmd, vars->hashmap, hash_exec);
			ft_strdel(&cmd_path);
		}
		ret = -1;
	}
	return (ret);
}

/*
**	Creates a temporary argv and checks if argv[0] is a builtin.
**	If argv[0] contains a '/'.
**	If argv[0] is a builtin.
**	If argv[0] is in hashmap, adds a hit tag to it, but does not execute.
**	If argv[0] is not in hashmap, add it to hashmap and add a hit to it but
**	does not execute it.
**	If argv[0] is a builtin:
**			- if it got executed, returns 0.
**			- if there was an error returns error number
**	Else (argv[0] is NOT a builtin) returns -1.
**	If execution should stop, returns -2
**
**	If fake_argv() found no real argv:
**	apply the assignation table to shell_vars (and env if 'exported')
*/

int				check_no_pipe_builtin(t_token *token_head, t_vars *vars)
{
	char					**argv;
	int						ret;

	if (!(argv = fake_argv(token_head, vars)) || !argv[0])
	{
		if (parse_expands(token_head, vars))
			return (-2);
		save_reset_stdfd(1);
		parse_redirections(token_head, 0);
		save_reset_stdfd(0);
		parse_assignation(token_head, vars);
		apply_assignation(&vars->assign_tab, vars);
		return (0);
	}
	ret = exec_or_hash(argv[0], token_head, vars);
	ft_free_ntab(argv);
	return (ret);
}
