#include "42sh.h"
#include "builtins.h"
#include "execution.h"
#include "cmd_parsing.h"

/*
**	Utility function for execute_no_pipe_builtin
**	Changes token types as if parse_redirections was called, but does not
**	actually perform redirections.
*/

static void		fake_redir_parser(t_token *token_head)
{
	t_token					*current;
	t_token					*prev;
	t_token					*next;

	current = token_head;
	if (!current)
		return ;
	prev = NULL;
	while (is_simple_cmd_token(current))
	{
		if (current->type == tk_redirection)
		{
			next = current->next;
			while (next->type == tk_eat)
				next = next->next;
			current->type = tk_eat;
			next->type = tk_eat;
		}
		current = current->next;
	}
}

/*
**	Utility function for execute_no_pipe_builtin
*/

static void		execute_exit(int exitno)
{
	print_exit();
	clean_exit(exitno);
}

/*
**	Parses expands, redirections, and executes builtin on the real token_list.
**	Returns 0.
*/

static int		no_pipe_builtin(t_token *token_head, t_vars *vars, int cmd_id)
{
	char					**argv;
	int						ret;

	parse_expands(token_head, vars);
	if (parse_redirections(token_head) == 0)
		return (0);
	argv = get_argv_from_token_lst(token_head);
	reset_terminal_settings();
	ret = exec_builtins(argv, vars, cmd_id);
	if (cmd_id == cmd_exit)
	{
		if (ret == 1)
			execute_exit(vars->cmd_value);
	}
	setup_terminal_settings();
	return (0);
}

/*
**	Returns a freshly allocated `fake` argv, because redirections have not
**	been applied.
*/

static char		**fake_argv(t_token *token_head, t_vars *vars)
{
	t_token					*cpy;
	char					**argv;

	cpy = copy_tokens(token_head);
	parse_expands(cpy, vars);
	fake_redir_parser(cpy);
	argv = get_argv_from_token_lst(cpy);
	free_token_list(cpy);
	return (argv);
}

/*
**	Creates a temporary argv and checks if argv[0] is a builtin.
**	If argv[0] contains a '/'.
**	If argv[0] is a builtin.
**	If argv[0] is in hashmap, adds a hit tag to it, but does not execute.
**	If argv[0] is not in hashmap, add it to hashmap and add a hit to it but
**	does not execute it.
**	Returns 0 if argv[0] is a builtin and got executed, else returns 1.
*/

t_bool			execute_no_pipe_builtin(t_token *token_head, t_vars *vars)
{
	char					**argv;
	unsigned int			cmd_id;
	unsigned int			ret;
	char					*cmd_path;

	if (!(argv = fake_argv(token_head, vars)))
		return (1);
	if (ft_strchr(argv[0], '/'))
		ret = 1;
	else if ((cmd_id = check_builtins(argv)))
		ret = no_pipe_builtin(token_head, vars, cmd_id);
	else if ((cmd_path = check_hashmap(argv[0], vars->hashmap, hash_exec)))
		ret = 1;
	else
	{
		if ((cmd_path = get_cmd_path(argv, vars->env_vars, 0)))
		{
			add_to_hashmap(argv[0], cmd_path, &vars->hashmap);
			check_hashmap(argv[0], vars->hashmap, hash_exec);
			ft_strdel(&cmd_path);
		}
		ret = 1;
	}
	ft_free_ntab(argv);
	return (ret);
}
